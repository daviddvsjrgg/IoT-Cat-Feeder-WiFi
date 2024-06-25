#include <HX711.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>
#include "RTClib.h"

#define FIREBASE_HOST "Credentials"
#define FIREBASE_AUTH "Credentials"
#define WIFI_SSID "Credentials"
#define WIFI_PASSWORD "Credentials"

RTC_DS3231 rtc;
HX711 scale;
Servo myServo;

// Calibration factor
const int calibration_factor = 10000;

void setup() {
  // Serial Monitor
  Serial.begin(9600);

  // LoadCell Setup
  scale.begin(D1, D2);
  scale.set_scale(calibration_factor);

  // RTC DS3231 Setup
  Wire.begin(D3, D4);  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

   // Servo Setup
  myServo.attach(D5);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  Serial.println("Connected to WiFi");

  // Connect Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  // LoadCell
  // if (scale.is_ready()) {
  //   int weight = scale.get_units();
    
  //   Serial.print("Weight: ");
  //   Serial.print(weight);
  //   Serial.println(" g");
  // } else {
  //   Serial.println("HX711 not found.");
  // }

  // RTC DS3231
  DateTime now = rtc.now();
  String timeFirebase = Firebase.getString("data/sensor/time");
  String rtcTime = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  // Format the time
  char formattedTime[9];
  sprintf(formattedTime, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  
  // Define the input text
  String inputText = Firebase.getString("data/sensor/schedule");
  // Declare an array to store the time values
  String timeArray[10]; // Assuming there are 24 time values in the input

  // Convert inputText to char array (c_str()) for strtok()
  char inputCharArray[inputText.length() + 1];
  inputText.toCharArray(inputCharArray, sizeof(inputCharArray));

  // Tokenize the input text using strtok
  char *token = strtok(inputCharArray, ",");
  int i = 0;

  // Loop through all tokens and store them in the array
  while (token != NULL && i < 10) {
      // Store the token in the array
      timeArray[i++] = String(token);
      
      // Get the next token
      token = strtok(NULL, ",");
  }

  String currentTimeString = String(formattedTime);
  Serial.println("Time: " + currentTimeString);

  for (int i = 0; i < sizeof(timeArray) / sizeof(timeArray[0]); i++) {
    if (currentTimeString == timeArray[i]) {
      String uniqueID = String(now.year()) + ":" + String(now.month()) + ":" + String(now.day()) + ":" + rtcTime;
      Serial.println("Match Found!");
      Firebase.setString("data/riwayat/name/" + uniqueID, "Memberi makan otomatis: " + timeArray[i]);
      Firebase.setInt("data/sensor/servo", 180);
      break;
    }
  }

  // Servo
  int servoValue = Firebase.getInt("data/sensor/servo");
  if(servoValue == 180) {
    myServo.write(servoValue); 
    delay(600);
    Firebase.setInt("data/sensor/servo", 0);
    myServo.write(servoValue);
  } else {
    myServo.write(0);
  }

  delay(500);

  // Update LoadCell
  if (scale.is_ready()) {
    int weight = scale.get_units();
    Firebase.setInt("data/sensor/loadCell", weight);
  } else {
    int weight = scale.get_units();
    Firebase.setInt("data/sensor/loadCell", weight);
  }
  

}

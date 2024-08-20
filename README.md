# Automatic Feeding System with Wi-Fi, Firebase, Load Cell, Servo, and RTC Integration

This project is an automatic feeding system controlled by an ESP8266. It uses a load cell to measure the weight of food, a servo to dispense food, and an RTC module for real-time scheduling. The system is connected to a Firebase database to control feeding schedules and record feeding history.

## Components

- **ESP8266 (NodeMCU)**
- **HX711** - Load Cell Amplifier
- **RTC DS3231** - Real-Time Clock
- **Servo Motor** - For controlling the feeder
- **Firebase** - Cloud storage and database
- **Wi-Fi** - For connecting to Firebase

## Features

- **Automated Feeding**: The servo motor dispenses food according to a schedule stored in Firebase.
- **Real-Time Clock (RTC)**: Keeps track of the current time and ensures feeding occurs at the correct time.
- **Load Cell**: Measures the amount of food dispensed and sends the data to Firebase.
- **Firebase Integration**: Manages schedules and records feeding events in the cloud.
- **Wi-Fi Connectivity**: The system connects to the internet to interact with Firebase.

## Circuit Diagram

| Component | ESP8266 Pin |
|-----------|-------------|
| HX711 (DT) | D1 |
| HX711 (SCK) | D2 |
| RTC (SDA) | D3 |
| RTC (SCL) | D4 |
| Servo | D5 |

## Setup

1. **Install Libraries**:
   - Install the following libraries from the Arduino Library Manager:
     - `HX711`
     - `ESP8266WiFi`
     - `FirebaseArduino`
     - `Servo`
     - `RTClib`

2. **Configure Firebase**:
   - Replace the placeholders in the code with your Firebase credentials:
     ```cpp
     #define FIREBASE_HOST "your-firebase-host"
     #define FIREBASE_AUTH "your-firebase-auth"
     ```

3. **Connect to Wi-Fi**:
   - Update the Wi-Fi credentials in the code:
     ```cpp
     #define WIFI_SSID "your-ssid"
     #define WIFI_PASSWORD "your-password"
     ```

4. **Upload the Code**:
   - Upload the code to your ESP8266.

## Usage

- The system reads feeding schedules from Firebase and checks them against the current time from the RTC.
- If a match is found, the servo motor dispenses food, and the event is recorded in Firebase.
- The load cell continuously updates the current weight of the food and sends this data to Firebase.

## Future Enhancements

- **Add a Web Interface**: For easy management of schedules.
- **Notification System**: Send alerts when feeding occurs or if there’s an issue.
- **Calibration Tool**: For easier calibration of the load cell.

## License

This project is licensed under the MIT License. Feel free to modify and distribute as needed.

## Acknowledgments

Thanks to the creators of the libraries used in this project and the open-source community for their support.


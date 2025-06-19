# 🔥 ESP32 + SIM800L: Firebase Realtime Database Integration

This project demonstrates how to connect an **ESP32** microcontroller with a **SIM800L GSM module** to send **sensor data** (temperature & humidity) to a **Firebase Realtime Database** using **AT commands**.

---

## 📦 Features

- Sends HTTP POST request to Firebase using SIM800L
- Uses hardware serial for communication with the GSM module
- Sends data in JSON format (can be adapted for any sensor)
- Modular and readable code with AT command handling

---

## 🛠️ Hardware Requirements

| Component         | Quantity |
|------------------|----------|
| ESP32 Dev Board  | 1        |
| SIM800L Module   | 1        |
| 4G/3G SIM Card (GPRS Enabled) | 1 |
| Power Supply (4V ~ 2A for SIM800L) | 1 |
| Jumper Wires     | As needed |

---

## 🔌 Connections

| ESP32 Pin | SIM800L Pin |
|----------|-------------|
| GPIO 26  | TX          |
| GPIO 27  | RX          |
| GND      | GND         |
| 4V Power | VCC         |

> ⚠️ **Important:** SIM800L requires a stable 4V power supply. Do not power it directly from ESP32 5V pin.

---

## 🧠 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board package
- A registered Firebase Realtime Database (free tier works!)

---

## 🧾 Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Create a new project
3. Go to Realtime Database → Create Database
4. Set Rules temporarily to:
```json
{
  "rules": {
    ".read": true,
    ".write": true
  }
}

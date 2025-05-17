# 🌐 NodeMcuServer – Smart IoT Web Interface

A responsive, auto-refreshing **NodeMCU web server interface** built with **Bootstrap**, featuring real-time control of **LEDs (or relays)** and live sensor feedback from **DHT11** (Temperature & Humidity) and **MQ Gas sensor**.

🎥 **Demo Video:**  
![VIDEO](images/video_Cut.mp4)

---

## 📁 Project Structure

The repository contains **two versions** of the NodeMCU server project:

### 1️⃣ Basic Web Server with 3 LEDs
Control 3 LEDs (or relays) directly from a clean, mobile-responsive web interface.

![Server with 3 LEDs](/images/serverWith3Pins.png)

---

### 2️⃣ Full IoT Server with Sensors + LEDs
Includes:
- 3 controllable LEDs (or relays)
- **DHT11** Sensor (Temperature & Humidity)
- **MQ Gas Sensor** (Air Quality Detection)

The interface displays live readings and dynamically changes colors based on sensor values.

![Completed Server Example](/images/ServerCompleted.jpg)

---

## 💡 Features

- 📱 **Bootstrap-based responsive UI**  
- 🔄 **Auto-refreshing homepage** for real-time data
- 🎛️ **Interactive LED/Relay control buttons**
- 🌡️ **Live sensor readings (Temp, Humidity, Gas)**
- 🎨 **Color-coded feedback for sensor thresholds**
- ⚡ Minimal setup for quick deployment on ESP8266/NodeMCU

---

## 🛠️ Tech Stack

- HTML/CSS (Bootstrap)
- JavaScript
- NodeMCU (ESP8266)
- Arduino IDE (for flashing code)

---

## 🚀 Quick Start

1. Flash the desired `.ino` sketch (basic or sensor version) to your NodeMCU using the Arduino IDE.
2. Upload the `data/` folder (containing web files) to the ESP8266 SPIFFS.
3. Connect to the NodeMCU's IP address to access the smart control panel.

---

## 📌 Use Cases

- Smart home control panels
- Educational IoT projects
- Real-time sensor monitoring dashboards
- DIY automation projects with minimal coding

---

## 🔗 Keywords for GitHub SEO

`NodeMCU` `ESP8266` `Web Server` `Bootstrap UI` `IoT Dashboard` `LED Control` `DHT11` `MQ Sensor` `Arduino` `Smart Home Interface` `Auto Refresh Web UI` `ESP8266 Sensor Web Interface`

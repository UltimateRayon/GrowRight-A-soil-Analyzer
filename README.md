# 🌱 GrowRight: Soil Analyzer

**GrowRight** is an Arduino-based soil monitoring system that helps determine whether current soil conditions are suitable for planting specific seeds. It uses real-time sensor data and compares it against a database of ideal growing conditions for various plants.

## 📦 Features

- Real-time monitoring of:
  - 🌡️ Temperature
  - 💧 Soil moisture
  - 💦 Humidity
  - ☀️ Light intensity
- Easy user interface with rotary encoder and OLED display
- Suggests suitable plants based on current environment
- Helps ensure optimal conditions before planting

## 🛠️ Components Used

- **Arduino Uno**
- **Sensors:**
  - Soil Moisture Sensor
  - DHT11 (Temperature & Humidity)
  - LDR (Light Sensor)
- **User Interface:**
  - OLED Display (128x64)
  - Rotary Encoder with push button
- Breadboard, jumper wires, and battery pack

## 🌾 Supported Plants in Database

- 🌹 Rose  
- 🌵 Cactus  
- 🌶️ Pepper  
- 🍆 Eggplant  
- 🍅 Tomato  

## 🧪 Sensor Thresholds

| Plant     | Moisture | Temp (°C) | Humidity (%) | Light (%) |
|-----------|----------|-----------|---------------|------------|
| Rose      | 550–700  | 20–33     | 45–75         | 10–55      |
| Cactus    | 500–650  | 18–36     | 25–80         | 40–100     |
| Pepper    | 625–750  | 16–30     | 45–80         | 10–75      |
| Eggplant  | 650–825  | 20–30     | 55–85         | 50–100     |
| Tomato    | 750–850  | 16–29     | 45–80         | 25–70      |

## 💻 Source Code

The main program is written in Arduino C++ and can be found here:  
👉 [`GrowRight.ino`](./GrowRight.ino) *(Rename your file to this in GitHub if not already)*

## 🎥 Demo Video

Watch the project in action:  
▶️ [Demo Video](https://drive.google.com/file/d/1B-YSSqrwFUbbEnEhSFm-R-aS0Q_CQtSt/view) 

## 🖼️ Project Image

`![GrowRight Setup](./Connection.jpg)`

## 👥 Team Members

- **Mushfiq Iqbal** — 3126  
- **Sadman Ahmed Sebaz** — 3154  
- **Kawser Jahan Kafi** — 3088  
- **Pritoma Paul Lopa** — 3170  

## 📄 License

This project was developed for educational purposes.  
Feel free to fork, modify, or expand upon it with proper credit to the original authors.

---


# IoT-Based Smart Greenhouse Monitoring and Environmental Data Logging System

## Project Overview
This project implements an IoT-based smart greenhouse monitoring system that continuously monitors environmental parameters and uploads real-time data to the cloud for visualization and analysis. The system is designed to support data-driven decision-making in smart agriculture by providing remote access to greenhouse conditions.

The project uses **Arduino Mega 2560** for sensor data acquisition and **ESP8266 Wi-Fi module** for wireless data transmission to the **ThingSpeak** cloud platform.

## System Architecture
The system is divided into two main layers:

### 1. Sensing Layer (Arduino Mega)
* Collects data from multiple environmental sensors.
* Sends formatted sensor data to the ESP8266 via serial communication.

### 2. Networking & Cloud Layer (ESP8266)
* Receives sensor data from Arduino.
* Connects to Wi-Fi.
* Uploads data to the ThingSpeak cloud for real-time visualization.

## Source Code Files

### 1️⃣ `Green_Arduino.ino`
**Purpose:** Sensor Data Acquisition and Serial Transmission  
This program runs on the Arduino Mega 2560 and performs the following tasks:
* Reads temperature and humidity using a **DHT sensor**.
* Reads soil moisture using:
    * Resistive soil moisture sensor
    * Capacitive soil moisture sensor
* Reads gas/air quality values using an **MQ gas sensor**.
* Formats sensor readings using identifiers:
    * `T`: Temperature
    * `H`: Humidity
    * `S`: Soil moisture
    * `C`: Capacitive soil moisture
    * `G`: Gas value
* Sends the formatted data string to the ESP8266 via serial communication.

### 2️⃣ `Green_ESP.ino`
**Purpose:** Wi-Fi Communication and Cloud Data Upload  
This program runs on the ESP8266 Wi-Fi module and performs the following tasks:
* Connects to a Wi-Fi network.
* Receives sensor data from Arduino via serial communication.
* Parses incoming data using predefined identifiers.
* Uploads sensor values to the **ThingSpeak** cloud using API keys.
* Verifies successful data upload using HTTP response codes.

## Sensors and Components Used
* Arduino Mega 2560
* ESP8266 Wi-Fi Module
* DHT11 Temperature & Humidity Sensor
* Resistive Soil Moisture Sensor
* Capacitive Soil Moisture Sensor
* MQ-2 Gas Sensor
* Breadboard & Jumper Wires
* USB Programming Cable
* 16×2 LCD Display with I2C Module

## Core Functionalities
* Real-time temperature and humidity monitoring
* Soil moisture level detection
* Capacitive soil condition analysis
* Gas and air quality monitoring
* Multi-sensor data integration
* Serial communication between Arduino and ESP8266
* Wireless data transmission via Wi-Fi
* Cloud-based data logging using ThingSpeak
* Live data visualization using graphs and charts

## Technical Specifications
* **Sampling Rate:** 1 sample every 2 seconds (0.5 Hz)
* **End-to-End Latency:** ~1.5–2.5 seconds
* **Temperature Accuracy:** ±0.5 °C
* **Humidity Accuracy:** ±2–3% RH
* **Cloud Upload Success Rate:** >95%

## How to Run the Project
1.  Upload `Green_Arduino.ino` to the **Arduino Mega 2560**.
2.  Upload `Green_ESP.ino` to the **ESP8266 Wi-Fi module**.
3.  Connect all sensors according to the circuit design.
4.  Update Wi-Fi credentials and ThingSpeak API keys in `Green_ESP.ino`.
5.  Power the system and monitor live data on the ThingSpeak dashboard.

## Cloud Platform
* **Platform Used:** ThingSpeak
* **Features:**
    * Real-time data visualization
    * Secure cloud data storage
    * Historical data analysis

## Applications
* Smart greenhouse monitoring
* Precision agriculture
* Environmental data logging
* Remote climate monitoring
* IoT-based agricultural research

## Learning Outcomes
* Practical experience with IoT system design
* Sensor interfacing with microcontrollers
* Serial communication protocol implementation
* Wi-Fi and cloud integration
* Real-time data visualization and analysis

## Author
**Jishan Bhowmick Aopu** Department of ECE  
North South University 

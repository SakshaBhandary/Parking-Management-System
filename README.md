# Parking Management-System
A smart parking management system designed to monitor vehicle count, manage available parking slots, and allocate parking spaces in real-time using Arduino UNO and ultrasonic sensors. This system is ideal for small-scale parking lots and reduces manual effort in tracking availability.

## Features <img src="https://github.com/user-attachments/assets/514c03f4-91a9-44e2-b533-5e36335cd4a8" width="20" height="20">

1. Real-time vehicle count.

2. Entry/Exit detection using ultrasonic or IR sensors.

3. Displays available slots on an LCD.

4. Alerts when parking is full.

## How It Works <image src="https://github.com/user-attachments/assets/bac99f3e-1362-405d-8352-23cbc6faf234" width="20" height="20">

1. Entry Sensor: Detects incoming vehicle → Increments vehicle count.

2. Exit Sensor: Detects leaving vehicle → Decrements count.

3. OLED Display: Shows current available parking slots.

4. Overflow Control: Prevents counting if parking is full.

> The project demonstrates key skills in sensor integration, I2C communication, real-time data display with OLED, and event-driven logic using Arduino.

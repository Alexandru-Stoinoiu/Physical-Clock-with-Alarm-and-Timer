# Physical Clock with Alarm and Timer
## Table of Contents
[1. Introduction](#introduction)\
[2. Overview](#overview)\
[3. Hardware Design](#hardware-design)\
[4. Software Design](#software-design)\
[5. Final Results](#final-results)\
[6. Conclusions](#conclusions)\
[7. Journal](#journal)\
[8. Source Code](#source-code)\
[9. Resources](#resources)
 
## Introduction

Keeping track of time and managing daily tasks efficiently can often be challenging. To address this, we aim to create a **Physical Clock with Alarm and Timer**, a device designed to assist users in organizing their schedules with ease. This clock will provide essential timekeeping features alongside customizable alarms and timers to help users stay on track throughout the day.

Equipped with an intuitive interface, the clock will allow users to set alarms for specific events or use the timer for tasks that require precise tracking. Whether it's waking up in the morning, timing a cooking session, or managing work intervals, this project combines hardware and software to deliver a reliable and user-friendly time management solution.

This project aims to enhance everyday productivity and provide a practical tool that integrates seamlessly into the user's routine.
 
## Overview
This dual-Arduino setup provides a modular design that separates display and control functionalities for better organization and performance. The joystick, LCD, seven-segment display, and buzzer work in tandem to create an efficient and user-friendly clock system with alarm and timer capabilities.
![WhatsApp Image 2025-01-15 at 21 24 56](https://github.com/user-attachments/assets/18d3f275-65a3-4dbf-8c1d-846f92fd6a9c)
https://github.com/user-attachments/assets/f9ec4273-85ec-4202-aeb3-27c0e9919bc4

## Hardware Design
1. Arduino Uno (x2)
The project utilizes two Arduino Uno boards for modular operation:
   - Master Arduino: Handles the main logic, user interface, and control of the 16x2 LCD display.
   - Slave Arduino: Operates the 4-digit seven-segment display and the buzzer, ensuring a clear separation of tasks and effective communication between the two boards.

2. Large Breadboard (Slave Arduino)
The large breadboard is dedicated to housing the slave Arduino, the 4-digit seven-segment display, and the buzzer. This setup is responsible for displaying numerical data such as the clock time or timer countdown and producing the alarm sound when triggered. The large workspace accommodates all necessary connections for these components.

4. Small Breadboard (Master Arduino)
The small breadboard is assigned to the master Arduino and the 16x2 LCD display, which provides detailed alphanumeric feedback such as system status, user settings, or instructions. This compact setup is optimized for the user interface portion of the project.

5. Buzzer
The buzzer is an audio output device connected to the slave Arduino. It serves as the primary alert system, producing sound notifications for the alarm or other user-defined events.

6. 220-Ohm Resistor
A single 220-ohm resistor is used to limit current flow, protecting components like the segments of the seven-segment display from excessive current that could cause damage.

7. 4-Digit Seven-Segment Display (Slave Arduino)
Connected to the slave Arduino via the large breadboard, this display provides a concise and visually clear representation of numerical data such as the time, countdowns, or other metrics relevant to the clock, alarm, or timer functionalities.

8. 16x2 LCD Display (Master Arduino)
The 16x2 LCD display is integrated into the system via the master Arduino and the small breadboard. It serves as the primary user interface, displaying detailed information such as current time, alarm status, or menu options. Its ability to display both text and numbers makes it a vital component for user interaction.

9. Multitude of Cables
Multiple jumper cables are used to connect all components securely and establish communication between the two Arduino boards and their respective peripherals. The cables ensure clean and efficient wiring across both breadboards.

10. Joystick
The joystick is an intuitive input device connected to the master Arduino. It allows users to navigate menus, adjust the clock, set the alarm, or control the timer. Its versatility adds a user-friendly aspect to the project
 
## Software Design
The software design for the clock project prioritizes efficient and reliable communication between the hardware components, such as the joystick, LCD, and alarm system. The project is developed using the Arduino IDE, a user-friendly and widely adopted environment for embedded systems programming.
#Hardcoded Time (12:00 PM) vs RTC Module
Hardcoded Start Time
 
  Advantages:
   Simple and straightforward implementation without the need for additional hardware.
   Works effectively as a proof-of-concept for displaying time and handling alarms and timers.
  
   Limitations:
   The clock resets to 12:00 PM every time the system is powered on, making it impractical for real-world use.
   It lacks the ability to keep track of time accurately if the system is turned off or restarted.
   Using an RTC Module
  
  Advantages:
   Provides real-time tracking of the current time, even when the system is powered off, as the RTC module has its own power source (battery).
   Ensures the displayed time is accurate and eliminates the need for hardcoding a start time.
   Enhances the system’s reliability and usability for real-world applications.
  Limitations:
   Requires additional hardware (RTC module) and slightly more complex coding for integration.
 
## Final Results
The physical clock with alarm and timer successfully demonstrates the following functionalities and features:

 #1. Clock Display
  The time is continuously displayed on the 4-digit seven-segment display in a clear and easy-to-read format.
  The initial time is hardcoded to start at 12:00 PM, simulating a basic clock mechanism.
 #2. Alarm Functionality
  The user can set an alarm using the joystick and confirm the alarm time displayed on the 16x2 LCD screen.
  When the alarm time is reached, the buzzer sounds, providing an audible alert.
  The user has the ability to stop the alarm once it triggers.
#3. Timer Functionality
  The user can set a countdown timer via the joystick, with the timer value displayed on the 4-digit seven-segment display.
  Once the countdown completes, the buzzer sounds to notify the user.
  The user can also stop or reset the timer at any point.
 #4. User Interface
  The 16x2 LCD display provides detailed feedback during alarm and timer setup, such as showing the current settings, time, and status updates.
  The joystick serves as an intuitive input device for setting the time, alarm, or timer values.
 
## Conclusions
The project demonstrates a well-rounded implementation of embedded systems, showcasing innovation in design and effective use of hardware components.

All features, including accurate timekeeping, alarm functionality, and a user-friendly timer, function as intended, validated through multiple test scenarios.
The project is user-friendly, cost-effective, and serves as a practical example of integrating traditional clock mechanisms with modern embedded system design principles.
 
## Journal
### Day 1 (12.12.2024):
Started the documentation.
### Day 2 (17.12.2024):
Milestone 2 - Hardware:
![WhatsApp Image 2025-01-13 at 22 39 26](https://github.com/user-attachments/assets/eea15266-209a-44bb-b5bb-41b3439dd1d5)
### Day 3 (13.01.2025):
First round of coding - functionalities for :
                           - Clock
                           - Alarm
                           - Displayed Menu
                           - Joystick interactions
## Resources
- 2 Arduino Uno
- One Small Breadboard
- One Large Breadboard
- One buzzer
- One 220 ohms resistor
- One 4 Seven Segment Display
- One 16x2 LCD Display
- Multitude of cables
- One Joystick

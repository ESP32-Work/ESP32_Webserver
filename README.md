# ESP32 Multi-Project Workspace

## Table of Contents
- [ESP32 Multi-Project Workspace](#esp32-multi-project-workspace)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Project Structure](#project-structure)
    - [Email\_SMTP\_ESP32](#email_smtp_esp32)
    - [ESP32\_DataBase\_System](#esp32_database_system)
    - [ESP32\_WebServer](#esp32_webserver)
    - [Webcam\_Streaming\_on\_ESP32](#webcam_streaming_on_esp32)
  - [Features](#features)
  - [Hardware Requirements](#hardware-requirements)
  - [Software Requirements](#software-requirements)

## Introduction
This workspace contains multiple projects for ESP32 microcontrollers, each demonstrating different functionalities such as web servers, database systems, and email sending capabilities.

## Project Structure

The workspace is organized into the following directories:

```
ESP32_Webserver/
├── Email_SMTP_ESP32/
│   ├── src/
│   ├── lib/
│   ├── include/
│   └── platformio.ini
├── ESP32_DataBase_System/
│   ├── src/
│   ├── lib/
│   ├── include/
│   └── platformio.ini
├── ESP32_WebServer/
│   ├── src/
│   ├── lib/
│   ├── include/
│   └── platformio.ini
├── Webcam_Streaming_on_ESP32/
│   ├── src/
│   ├── lib/
│   ├── include/
│   └── platformio.ini
└── README.md
```

Each project directory contains:
- `src/`: Source code files.
- `lib/`: Libraries specific to the project.
- `include/`: Header files.
- `platformio.ini`: Configuration file for PlatformIO.

### Email_SMTP_ESP32
This project demonstrates sending emails using an ESP32 microcontroller.

### ESP32_DataBase_System
This project showcases a database system implementation on an ESP32.

### ESP32_WebServer
This project demonstrates the creation of a sophisticated web server using an ESP32 microcontroller operating in dual Wi-Fi mode (both Station and Access Point).

### Webcam_Streaming_on_ESP32
This project involves streaming webcam data using an ESP32.

## Features
- **Email_SMTP_ESP32**: Send emails using SMTP.
- **ESP32_DataBase_System**: Store and retrieve data using a database system.
- **ESP32_WebServer**: Serve multiple interactive web pages with animations, authentication, and real-time updates.
- **Webcam_Streaming_on_ESP32**: Stream webcam data over the network.

## Hardware Requirements
- ESP32 microcontroller board
- USB cable for programming and power
- Power supply (optional, for standalone operation)

## Software Requirements
- Arduino IDE or PlatformIO
- ESP32 board support package
- Required libraries (specific to each project)


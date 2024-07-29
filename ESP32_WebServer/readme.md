# ESP32 Web Server Project

## Table of Contents
- [ESP32 Web Server Project](#esp32-web-server-project)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Hardware Requirements](#hardware-requirements)
  - [Software Requirements](#software-requirements)
  - [Setup and Configuration](#setup-and-configuration)
  - [Code Explanation](#code-explanation)
    - [Wi-Fi Setup](#wi-fi-setup)
    - [Web Server Routes](#web-server-routes)
    - [Main Loop](#main-loop)
  - [Usage](#usage)
  - [Troubleshooting](#troubleshooting)
  - [Future Enhancements](#future-enhancements)
  - [Images](#images)

## Introduction
This project demonstrates the creation of a simple web server using an ESP32 microcontroller. It sets up a Wi-Fi access point and serves HTML pages with different content and styling.

## Features
- Creates a Wi-Fi access point
- Serves a basic "Hello World" page
- Serves a styled page with geometric shapes
- Handles 404 errors for undefined routes

## Hardware Requirements
- ESP32 microcontroller board
- USB cable for programming and power

## Software Requirements
- PlatformIO IDE
- ESP32 board support package
- Arduino framework for ESP32

## Setup and Configuration

1. Clone this repository or create a new PlatformIO project.
2. Configure your `platformio.ini` file to use the ESP32 board and Arduino framework.
3. Install the required libraries:
   ```
   #include <WiFi.h>
   #include <WebServer.h>
   ```
4. Set your Wi-Fi credentials in the code:
   ```cpp
   const char* ssid = "ESP32";
   const char* password = "";
   ```
5. Configure the IP address settings if needed:
   ```cpp
   IPAddress local_ip(192,168,0,10);
   IPAddress gateway(192,168,0,1);
   IPAddress subnet(255,255,255,0);
   ```

## Code Explanation

### Wi-Fi Setup
The ESP32 is configured as a Wi-Fi access point:

```cpp
WiFi.softAP(ssid, password);
WiFi.softAPConfig(local_ip, gateway, subnet);
```

### Web Server Routes
The server is set up with three routes:

1. Root route ("/"):
   ```cpp
   server.on("/", callback);
   ```
   Displays a simple "Hello World" message.

2. Message route ("/msg"):
   ```cpp
   server.on("/msg", msg_callback);
   ```
   Serves an HTML page with styled geometric shapes.

3. 404 Error handler:
   ```cpp
   server.onNotFound(error_callback);
   ```
   Displays a "Page not found" message for undefined routes.

### Main Loop
The `loop()` function continuously handles client requests:

```cpp
void loop(){
  server.handleClient();
}
```

## Usage
1. Upload the code to your ESP32 board.
2. The ESP32 will create a Wi-Fi access point named "ESP32".
3. Connect to this Wi-Fi network from your device.
4. Open a web browser and navigate to `http://192.168.0.10/` to see the "Hello World" message.
5. Navigate to `http://192.168.0.10/msg` to see the styled page with shapes.
6. Any other URL will display a 404 error page.

## Troubleshooting
- If you can't connect to the Wi-Fi, ensure you're using the correct SSID and password.
- If the web pages don't load, verify that you're connected to the ESP32's Wi-Fi network and using the correct IP address.
- Check the Serial Monitor for debugging information.

## Future Enhancements
- Add user interaction features like buttons or form inputs.
- Implement MQTT for IoT functionality.
- Add sensors and display real-time data on the web pages.

## Images
[Place your project images here, showing the ESP32 setup and screenshots of the web pages]
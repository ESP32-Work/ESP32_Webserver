# ESP32 Dual-Mode Web Server Project

## Table of Contents
- [ESP32 Dual-Mode Web Server Project](#esp32-dual-mode-web-server-project)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Hardware Requirements](#hardware-requirements)
  - [Software Requirements](#software-requirements)
  - [Video Demonstration](#video-demonstration)
  - [Setup and Configuration](#setup-and-configuration)
  - [Code Explanation](#code-explanation)
    - [Dual-Mode Wi-Fi Setup](#dual-mode-wi-fi-setup)
    - [Web Server Routes](#web-server-routes)
    - [Authentication](#authentication)
    - [HTML Templates](#html-templates)
    - [Main Loop](#main-loop)
  - [Usage](#usage)
  - [Web Pages](#web-pages)
  - [Troubleshooting](#troubleshooting)
  - [Future Enhancements](#future-enhancements)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction
This project demonstrates the creation of a sophisticated web server using an ESP32 microcontroller operating in dual Wi-Fi mode (both Station and Access Point). It serves multiple interactive web pages with animations, authentication, and real-time updates.

## Features
- Operates in dual Wi-Fi mode:
  - Connects to existing Wi-Fi network (Station mode)
  - Creates its own Wi-Fi access point
- Serves multiple interactive web pages:
  - Welcome page with network information
  - Live-updating clock page
  - Authenticated page with detailed network stats
  - Animated goodbye page
- Responsive design with CSS animations
- Basic HTTP authentication for secure pages
- Real-time JavaScript updates

## Hardware Requirements
- ESP32 microcontroller board
- USB cable for programming and power
- Power supply (optional, for standalone operation)

## Software Requirements
- Arduino IDE or PlatformIO
- ESP32 board support package
- Required libraries:
  ```
  #include <WiFi.h>
  #include <WebServer.h>
  #include <time.h>
  ```

## Video Demonstration
Watch our project in action:

[![ESP32 Web Server Demo](https://img.youtube.com/vi/s6Wjp_YnEWk/0.jpg)](https://www.youtube.com/watch?v=s6Wjp_YnEWk)

## Setup and Configuration

1. Install the required software:
   ```bash
   # If using PlatformIO
   pio init --board esp32dev
   pio lib install "WiFi" "WebServer"
   ```

2. Configure your network credentials:
   ```cpp
   // Station Mode Credentials
   const char* sta_ssid = "YourWiFiName";
   const char* sta_password = "YourWiFiPassword";

   // AP Mode Credentials
   const char* ap_ssid = "ESP32_AP";
   const char* ap_password = "12345678";
   ```

3. Set up IP configurations if needed:
   ```cpp
   IPAddress local_ip(192,168,4,1);
   IPAddress gateway(192,168,4,1);
   IPAddress subnet(255,255,255,0);
   ```

## Code Explanation

### Dual-Mode Wi-Fi Setup
```cpp
void setup() {
  WiFi.mode(WIFI_AP_STA);  // Enable dual mode
  
  // Set up Access Point
  WiFi.softAP(ap_ssid, ap_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  // Connect to existing network
  WiFi.begin(sta_ssid, sta_password);
}
```

### Web Server Routes
```cpp
server.on("/", handleHome);
server.on("/timer", handleTimer);
server.on("/info", handleInfo);
server.on("/goodbye", handleGoodbye);
server.onNotFound(handleNotFound);
```

### Authentication
```cpp
bool is_authenticated() {
  if (!server.authenticate("admin", "admin")) {
    server.requestAuthentication();
    return false;
  }
  return true;
}
```

### HTML Templates
```cpp
String getPage(String content) {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  // ... styling and navigation ...
  html += content;
  html += "</div></body></html>";
  return html;
}
```

### Main Loop
```cpp
void loop() {
  server.handleClient();
}
```

## Usage
1. Flash the code to your ESP32
2. The ESP32 will:
   - Create a Wi-Fi network named "ESP32_AP"
   - Attempt to connect to your specified network
3. Connect to either:
   - Your home network (if ESP32 connected successfully)
   - The ESP32's "ESP32_AP" network
4. Open a web browser and navigate to:
   - Station mode IP (usually assigned by your router)
   - AP mode IP (default: 192.168.4.1)

## Web Pages
1. Home Page (`/`)
   - Welcomes users
   - Displays network information
   - Shows navigation to other pages

2. Timer Page (`/timer`)
   - Displays a live-updating clock
   - Uses JavaScript for real-time updates

3. Info Page (`/info`)
   - Requires authentication (username: admin, password: admin)
   - Shows detailed network statistics
   - Displays connection status

4. Goodbye Page (`/goodbye`)
   - Features CSS animations
   - Provides a friendly farewell message

## Troubleshooting
| Problem | Possible Cause | Solution |
|---------|----------------|----------|
| Can't connect to ESP32 AP | Incorrect password | Verify AP password in code |
| Web pages don't load | Wrong IP address | Check serial monitor for correct IPs |
| Authentication fails | Browser cache | Clear browser cache |
| Station mode won't connect | Wrong credentials | Verify home network credentials |

## Future Enhancements
- [ ] Implement HTTPS for secure connections
- [ ] Add WebSocket support for real-time sensor data
- [ ] Create a configuration page for network settings
- [ ] Add OTA (Over The Air) update capability

## Contributing
1. Fork the repository
2. Create a new branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

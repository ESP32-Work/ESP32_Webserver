## Overview

This project demonstrates how to use the WiFiManager library to manage WiFi connections on an ESP32 device. The code automatically connects to a saved WiFi network or starts an access point if the connection fails.

## Project Structure

```
.gitignore
.pio/
.vscode/
include/
lib/
platformio.ini
readme.md
src/
    main.cpp
test/
```

## Dependencies

- [WiFiManager](https://github.com/tzapu/WiFiManager)

## Setup

1. **Install PlatformIO**: Ensure you have PlatformIO installed in your development environment.
2. **Clone the Repository**: Clone this repository to your local machine.
3. **Install Dependencies**: PlatformIO will automatically install the required libraries specified in platformio.ini


## Usage

1. **Open the Project**: Open the project in Visual Studio Code with the PlatformIO extension.
2. **Build the Project**: Use the PlatformIO build command to compile the project.
3. **Upload to ESP32**: Upload the compiled firmware to your ESP32 device.

## Code Explanation




```cpp
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

void setup() {
    Serial.begin(115200);
    
    WiFiManager wm;

    bool res;
    res = wm.autoConnect("AutoConnectAP","password"); // password protected AP

    if(!res) {
        Serial.println("Failed to connect");
    } 
    else {
        Serial.println("connected...yeey :)");
    }
}

void loop() {
    // put your main code here, to run repeatedly:   
}
```

- **WiFiManager Initialization**: Initializes the WiFiManager object.
- **AutoConnect**: Attempts to connect to a saved WiFi network. If it fails, it starts an access point with the SSID "AutoConnectAP" and password "password".
- **Connection Status**: Prints the connection status to the Serial monitor.


## Video Setup
![wificonfigmanager](https://github.com/user-attachments/assets/74fed3ce-6c39-42f8-ba68-45ed38329d0a)


## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## Contact

For any questions or issues, please open an issue on the GitHub repository.

---
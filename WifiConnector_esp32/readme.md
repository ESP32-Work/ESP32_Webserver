# ESP32 Wi-Fi Manager

This project is an ESP32-based Wi-Fi manager that allows users to configure and manage Wi-Fi connections through a web interface. The project uses the ESPAsyncWebServer library to serve web pages and handle HTTP requests.

## Features

- Create an access point (AP) with a configurable SSID and password.
- Serve a web interface for Wi-Fi configuration.
- Scan for available Wi-Fi networks and display them on the web interface.
- Connect to a selected Wi-Fi network and save the credentials in non-volatile storage (NVS).
- Automatically attempt to reconnect to the saved Wi-Fi network on startup.
- Display the current connection status and IP address on the web interface.
- Handle Wi-Fi events and manage connection attempts with a timeout.

## Project Structure



## Dependencies

The project depends on the following libraries:

- [AsyncTCP](https://github.com/esphome/AsyncTCP-esphome)
- [ESPAsyncWebServer](https://github.com/esphome/ESPAsyncWebServer-esphome)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

These dependencies are specified in the `platformio.ini` file:

```ini
[env:ESP32_S3_DEV_4MB_QD_No_PSRAM]
platform = espressif32
board = ESP32_S3_DEV_4MB_QD_No_PSRAM
framework = arduino
lib_deps = 	
    esphome/AsyncTCP-esphome@^2.1.4
	esphome/ESPAsyncWebServer-esphome@^3.3.0
    bblanchon/ArduinoJson@^7.0.4
```

## Setup and Usage

1. **Clone the repository:**

   ```sh
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Open the project in PlatformIO:**

   Open the project directory in Visual Studio Code with the PlatformIO extension installed.

3. **Build and upload the firmware:**

   Connect your ESP32 board to your computer and use PlatformIO to build and upload the firmware.

   ```sh
   pio run --target upload
   ```

4. **Access the web interface:**

   After uploading the firmware, the ESP32 will create an access point with the SS

ID

 `ESP32-AP` and password `123456789`. Connect to this access point using a Wi-Fi-enabled device.

   Open a web browser and navigate to `http://192.168.4.1` to access the web interface.

5. **Configure Wi-Fi:**

   Use the web interface to scan for available Wi-Fi networks, select a network, and enter the password to connect. The credentials will be saved in NVS, and the ESP32 will attempt to reconnect to the saved network on subsequent startups.

## Files Overview

- **[src/prefs_for_nvs.txt](src/prefs_for_nvs.txt):** Contains the main implementation of the Wi-Fi manager, including the web interface and Wi-Fi event handling.
- **[src/prefs_jugar_working.txt](src/prefs_jugar_working.txt):** Similar to `prefs_for_nvs.txt` but with additional functionality for handling Wi-Fi events and reconnection attempts.
- **[src/advanced.txt](src/advanced.txt):** Contains advanced features such as connection status checks and handling connection attempts with a timeout.
- **[src/moreadvanced-->not solved.txt](src/moreadvanced-->not solved.txt):** Contains additional advanced features and improvements for handling Wi-Fi connections and events.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [AsyncTCP](https://github.com/esphome/AsyncTCP-esphome)
- [ESPAsyncWebServer](https://github.com/esphome/ESPAsyncWebServer-esphome)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

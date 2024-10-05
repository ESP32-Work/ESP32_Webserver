#include <WiFi.h>
#include <WebServer.h>
#include <time.h>

// Station Mode Credentials
const char* sta_ssid = "Testwifi";
const char* sta_password = "x11y22z33";

// AP Mode Credentials
const char* ap_ssid = "ESP32_AP";
const char* ap_password = "12345678";

// IP Configurations
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

bool is_authenticated() {
  if (!server.authenticate("admin", "admin"))
  {
    server.requestAuthentication();
    return false;
  }
  return true;
}

String getPage(String content) {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Web Server</title>";
  html += "<style>";
  html += "body{font-family:Arial,sans-serif;margin:0;padding:20px;background:#f0f2f5;}";
  html += "nav{background:#333;padding:10px;margin-bottom:20px;}";
  html += "nav a{color:white;text-decoration:none;margin-right:15px;}";
  html += ".container{max-width:800px;margin:0 auto;background:white;padding:20px;border-radius:8px;box-shadow:0 2px 4px rgba(0,0,0,0.1);}";
  html += "@keyframes fadeIn{from{opacity:0;}to{opacity:1;}}";
  html += ".animate{animation:fadeIn 1s;}";
  html += "</style></head><body>";
  html += "<nav>";
  html += "<a href='/'>Home</a>";
  html += "<a href='/timer'>Timer</a>";
  html += "<a href='/info'>Info</a>";
  html += "<a href='/goodbye'>Goodbye</a>";
  html += "</nav>";
  html += "<div class='container animate'>";
  html += content;
  html += "</div></body></html>";
  return html;
}

void handleHome() {
  String content = "<h1>Welcome to ESP32 Web Server</h1>";
  content += "<div style='text-align:center;'>";
  content += "<div style='font-size:48px;animation:bounce 1s infinite;'>👋</div>";
  content += "<p>Welcome! Explore our pages using the navigation bar above.</p>";
  content += "<div style='background:#e8f5e9;padding:10px;border-radius:5px;margin-top:20px;'>";
  content += "<h2>Network Information</h2>";
  content += "<p><strong>WiFi Station IP:</strong> ";
  if (WiFi.status() == WL_CONNECTED) {
    content += WiFi.localIP().toString();
  } else {
    content += "Not connected";
  }
  content += "</p>";
  content += "<p><strong>Access Point IP:</strong> ";
  content += WiFi.softAPIP().toString();
  content += "</p>";
  content += "<p><strong>Access Point SSID:</strong> ";
  content += ap_ssid;
  content += "</p>";
  content += "</div>";
  content += "</div>";
  content += "<style>@keyframes bounce{0%,100%{transform:translateY(0);}50%{transform:translateY(-20px);}}</style>";
  server.send(200, "text/html", getPage(content));
}

void handleTimer() {
  String content = "<h1>Current Time</h1>";
  content += "<div id='clock' style='font-size:48px;text-align:center;'>Loading...</div>";
  content += "<script>";
  content += "function updateClock(){";
  content += "const now=new Date();";
  content += "document.getElementById('clock').textContent=now.toLocaleTimeString();}";
  content += "setInterval(updateClock,1000);updateClock();";
  content += "</script>";
  server.send(200, "text/html", getPage(content));
}

void handleInfo() {
  if (!is_authenticated()) {
    return;
  }
  
  String content = "<h1>Detailed Network Information</h1>";
  content += "<div style='background:#e3f2fd;padding:15px;border-radius:5px;'>";
  content += "<h2>Station Mode (Client)</h2>";
  content += "<p><strong>Status:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? "Connected" : "Disconnected";
  content += "</p>";
  content += "<p><strong>IP Address:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.localIP().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>Subnet Mask:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.subnetMask().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>Gateway IP:</strong> ";
  content += (WiFi.status() == WL_CONNECTED) ? WiFi.gatewayIP().toString() : "N/A";
  content += "</p>";
  content += "<p><strong>MAC Address:</strong> ";
  content += WiFi.macAddress();
  content += "</p>";
  content += "<p><strong>Connected to SSID:</strong> ";
  content += sta_ssid;
  content += "</p>";
  
  content += "<h2>Access Point Mode</h2>";
  content += "<p><strong>AP IP:</strong> ";
  content += WiFi.softAPIP().toString();
  content += "</p>";
  content += "<p><strong>AP MAC Address:</strong> ";
  content += WiFi.softAPmacAddress();
  content += "</p>";
  content += "<p><strong>AP SSID:</strong> ";
  content += ap_ssid;
  content += "</p>";
  content += "<p><strong>Connected Stations:</strong> ";
  content += WiFi.softAPgetStationNum();
  content += "</p>";
  content += "</div>";
  
  server.send(200, "text/html", getPage(content));
}

void handleGoodbye() {
  String content = "<h1>Goodbye!</h1>";
  content += "<div style='text-align:center;'>";
  content += "<div style='font-size:48px;animation:wave 1s infinite;'>👋</div>";
  content += "<p>Thank you for visiting. Come back soon!</p>";
  content += "</div>";
  content += "<style>@keyframes wave{0%,100%{transform:rotate(0deg);}50%{transform:rotate(20deg);}}</style>";
  server.send(200, "text/html", getPage(content));
}

void handleNotFound() {
  String content = "<h1>404: Not Found</h1><p>The requested page was not found.</p>";
  server.send(404, "text/html", getPage(content));
}
void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi network
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ap_ssid, ap_password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  
  WiFi.begin(sta_ssid, sta_password);
  
  Serial.println("Setting up Access Point: ");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  Serial.println("Connecting to WiFi network...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("Station IP address: ");
    Serial.println(WiFi.localIP());
    
    // Init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  } else {
    Serial.println("\nFailed to connect to WiFi network");
  }

  server.on("/", handleHome);
  server.on("/timer", handleTimer);
  server.on("/info", handleInfo);
  server.on("/goodbye", handleGoodbye);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
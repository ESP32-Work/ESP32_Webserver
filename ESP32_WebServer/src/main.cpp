#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32";
const char* password = "";

IPAddress local_ip(192,168,0,10);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);


void callback(){
  server.send(200, "text/html", "<h1>Hello World</h1>");
  Serial.println("First callback");
}

void msg_callback(){
  String html = "<!DOCTYPE html>\n";
  html += "<html>\n";
  html += "<head>\n";
  html += "<title>Message Page</title>\n";
  html += "<style>\n";
  html += "body {\n";
  html += "  font-family: Arial, sans-serif;\n";
  html += "  background-color: #f2f2f2;\n";
  html += "}\n";
  html += "h1 {\n";
  html += "  color: #333;\n";
  html += "  text-align: center;\n";
  html += "}\n";
  html += ".box {\n";
  html += "  width: 200px;\n";
  html += "  height: 200px;\n";
  html += "  background-color: #ccc;\n";
  html += "  margin: 0 auto;\n";
  html += "}\n";
  html += ".circle {\n";
  html += "  width: 100px;\n";
  html += "  height: 100px;\n";
  html += "  background-color: #f00;\n";
  html += "  border-radius: 50%;\n";
  html += "  margin: 20px auto;\n";
  html += "}\n";
  html += ".triangle {\n";
  html += "  width: 0;\n";
  html += "  height: 0;\n";
  html += "  border-left: 50px solid transparent;\n";
  html += "  border-right: 50px solid transparent;\n";
  html += "  border-bottom: 100px solid #00f;\n";
  html += "  margin: 20px auto;\n";
  html += "}\n";
  html += "</style>\n";
  html += "</head>\n";
  html += "<body>\n";
  html += "<h1>Message Page</h1>\n";
  html += "<div class=\"box\"></div>\n";
  html += "<div class=\"circle\"></div>\n";
  html += "<div class=\"triangle\"></div>\n";
  html += "</body>\n";
  html += "</html>\n";
  
  server.send(200, "text/html", html);
  Serial.println("Second callback");
}

void error_callback(){
  server.send(404, "text/html", "<h1>Page not found</h1>");
  Serial.println("Error callback");
}

void setup(){
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(1000);

  server.on("/", callback);
  server.on("/msg", msg_callback);
  server.onNotFound(error_callback);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();

}
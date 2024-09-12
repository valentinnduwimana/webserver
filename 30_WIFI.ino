#include <WiFi.h>  
#include <WebServer.h>  

const char* ssid = "val";      // Replace with your Wi-Fi network name  
const char* password = "valentin1"; // Replace with your Wi-Fi password  

WebServer server(80); // Create a server on port 80  

const int ledPin = 2; // Pin where the LED is connected  

void setup() {  
  Serial.begin(115200);  
  pinMode(ledPin, OUTPUT); // Configure the LED pin as an output  
  digitalWrite(ledPin, LOW); // Turn the LED off at startup  

  // Connect to Wi-Fi  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {  
    delay(1000);  
    Serial.println("Connecting to Wi-Fi...");  
  }  
  Serial.println("Connected to Wi-Fi");  
  Serial.print("IP Address: ");  
  Serial.println(WiFi.localIP()); // Print the IP address of the ESP32  

  // Define server routes  
  server.on("/", handleRoot);  
  server.on("/led/on", handleLedOn);  
  server.on("/led/off", handleLedOff);  

  server.begin(); // Start the server  
  Serial.println("Server started");  
}  

void loop() {  
  server.handleClient(); // Handle incoming client requests  
}  

void handleRoot() {  
  String html = "<html><body><h1>LED Control</h1>";  
  html += "<button onclick=\"location.href='/led/on'\">Turn ON LED</button><br>";  
  html += "<button onclick=\"location.href='/led/off'\">Turn OFF LED</button><br>";  
  html += "</body></html>";  
  server.send(200, "text/html", html); // Send HTML content  
}  

void handleLedOn() {  
  digitalWrite(ledPin, HIGH); // Turn on the LED  
  server.send(200, "text/html", "<h1>LED is ON</h1><a href='/'>Go Back</a>");  
}  

void handleLedOff() {  
  digitalWrite(ledPin, LOW); // Turn off the LED  
  server.send(200, "text/html", "<h1>LED is OFF</h1><a href='/'>Go Back</a>");  
}

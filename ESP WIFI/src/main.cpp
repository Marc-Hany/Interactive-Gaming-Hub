  #include <Arduino.h>
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <ArduinoJson.h>
  #define STM_RX 16
  #define STM_TX 17
  #define LED_PIN 2

  HardwareSerial STMSerial(2);

  // WiFi credentials
  const char* ssid     = "Home_DSL";
  const char* password = "dc7d94a7";

  // Server URL
  const char* serverURL = "http://gamehubtest.atwebpages.com/receive.php";

  String rxBuffer = "";

  void initWiFi()
  {
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      Serial.print("Connecting to WiFi");
      while (WiFi.status() != WL_CONNECTED) {
          Serial.print(".");
          delay(1000);
      }

      Serial.println();
      Serial.print("Connected, IP: ");
      Serial.println(WiFi.localIP());
      // Turn the LED on
      digitalWrite(LED_PIN, HIGH);
  }

  void sendToServer(const String& data)
  {
      if (WiFi.status() != WL_CONNECTED) {
          Serial.println("WiFi not connected");
          return;
      }

      HTTPClient http;
      http.begin(serverURL);
      http.addHeader("Content-Type", "application/json");

      String payload = data;

      int httpCode = http.POST(payload);

      Serial.print("Sent: ");
      Serial.print(payload);
      Serial.print(" | HTTP Code: ");
      Serial.println(httpCode);

      http.end();
  }

  // New function to check for reset command from website
  void checkServerCommand() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    http.begin(serverURL); 
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
        String response = http.getString();
        int command = response.toInt();

        if (command > 0) {
            Serial.print("Command received: ");
            Serial.println(command);
            
            // Send the actual character ('1' or '2') to STM32
            if (command == 1) STMSerial.write('1');
            else if (command == 2) STMSerial.write('2');
        }
    }
    http.end();
}


  void setup()
  {
      Serial.begin(9600);
      STMSerial.begin(9600, SERIAL_8N1, STM_RX, STM_TX);
      while (STMSerial.available()) STMSerial.read(); // flush old bytes
      // Initialize digital pin 2 as an output
      pinMode(LED_PIN, OUTPUT);
      Serial.println("ESP32 ready");
      initWiFi();
  }

  void loop() {
    // 1. Check for data from STM32 to send to Web
    while (STMSerial.available()) {
        char c = STMSerial.read();
        if (rxBuffer.length() == 0 && c != '{') continue;
        rxBuffer += c;

        if (c == '\n') {
            rxBuffer.trim();
            DynamicJsonDocument doc(200);
            if (!deserializeJson(doc, rxBuffer)) {
                sendToServer(rxBuffer);
                // ACK REMOVED FROM HERE
            }
            rxBuffer = "";
        }
    }

    // 2. Periodically check website for Reset Button click
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 2000) { 
        checkServerCommand(); // Updated name
        lastCheck = millis();
    }
}
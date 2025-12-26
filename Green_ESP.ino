#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <SPI.h>

// WiFi credentials
const char* ssid = "Saad";
const char* password = "aaaaaaaa";

// ThingSpeak settings
unsigned long myChannelNumber = 2969987; // Replace with your channel number
const char* myWriteAPIKey = "OK9W7176MBUPBPVR"; // Replace with your API key

WiFiClient client;

// Variables
float temperature = 0, humidity = 0;
int gasValue = 0, soilResistive = 0, soilCapacitive = 0;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 20000; // 20 seconds

void setup() {
  Serial.begin(115200);
  Serial.println("ESP8266 Started");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available()) {
    String sensorData = Serial.readStringUntil('\n');
    sensorData.trim();

    // Expected format: temperature,humidity,gasValue,soilResistive,soilCapacitive
    int comma1 = sensorData.indexOf(',');
    int comma2 = sensorData.indexOf(',', comma1 + 1);
    int comma3 = sensorData.indexOf(',', comma2 + 1);
    int comma4 = sensorData.indexOf(',', comma3 + 1);

    if (comma1 > 0 && comma2 > comma1 && comma3 > comma2 && comma4 > comma3) {
      temperature = sensorData.substring(0, comma1).toFloat();
      humidity = sensorData.substring(comma1 + 1, comma2).toFloat();
      gasValue = sensorData.substring(comma2 + 1, comma3).toInt();
      soilResistive = sensorData.substring(comma3 + 1, comma4).toInt();
      soilCapacitive = sensorData.substring(comma4 + 1).toInt();

      // Debug print
      Serial.println("Received Data:");
      Serial.print("\tTemperature: "); Serial.println(temperature);
      Serial.print("\tHumidity: "); Serial.println(humidity);
      Serial.print("\tGas Value: "); Serial.println(gasValue);
      Serial.print("\tSoil (Resistive): "); Serial.println(soilResistive);
      Serial.print("\tSoil (Capacitive): "); Serial.println(soilCapacitive);

      unsigned long currentTime = millis();
      if (currentTime - lastUpdateTime >= updateInterval) {
        lastUpdateTime = currentTime;

        // Send to ThingSpeak
        ThingSpeak.setField(1, temperature);
        ThingSpeak.setField(2, humidity);
        ThingSpeak.setField(3, gasValue);
        ThingSpeak.setField(4, soilResistive);
        ThingSpeak.setField(5, soilCapacitive);

        int responseCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if (responseCode == 200) {
          Serial.println("Data sent to ThingSpeak successfully!");
        } else {
          Serial.print("ThingSpeak update failed. HTTP error code: ");
          Serial.println(responseCode);
        }
      }
    } else {
      Serial.println("Error: Malformed sensor data!");
    }
  }
}

#include <DHT.h>
#include <Wire.h>
#define espSerial Serial1 // Use Serial1 for ESP8266

// Constants
#define DHTPIN 7        // Pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT22 sensor
#define MQ135_PIN A8    // MQ135 air quality sensor
#define SOIL_RESISTIVE A3  // Resistive soil moisture sensor
#define SOIL_CAPACITIVE A6 // Capacitive soil moisture sensor

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT22 sensor

// Variables
float temperature = 0, humidity = 0;
int gasValue = 0;
int soilResistiveValue = 0;
int soilCapacitiveValue = 0;

// Timing variables
unsigned long lastSensorReadTime = 0;
const unsigned long sensorInterval = 1000;

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  dht.begin();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSensorReadTime >= sensorInterval) {
    lastSensorReadTime = currentTime;

    // MQ135 Reading
    int mqRaw = analogRead(MQ135_PIN);
    gasValue = map(mqRaw, 0, 1023, 0, 500); // Map to 0-500 range

    // Soil Moisture (Resistive)
    soilResistiveValue = analogRead(SOIL_RESISTIVE);
    if (soilResistiveValue > 400) {
      Serial.println("Soil (resistive) is DRY");
    } else {
      Serial.println("Soil (resistive) is WET");
    }

    // Soil Moisture (Capacitive)
    soilCapacitiveValue = analogRead(SOIL_CAPACITIVE);

    // DHT22 Temperature & Humidity
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    // Send data via ESP8266
    if (!isnan(temperature) && !isnan(humidity)) {
      espSerial.print(temperature); espSerial.print(",");
      espSerial.print(humidity); espSerial.print(",");
      espSerial.print(gasValue); espSerial.print(",");
      espSerial.print(soilResistiveValue); espSerial.print(",");
      espSerial.println(soilCapacitiveValue);
    }

    // Debug output via Serial
    Serial.println();
    Serial.print("Temp: "); Serial.print(temperature); Serial.print("°C\t");
    Serial.print("Hum: "); Serial.print(humidity); Serial.print("%\t");
    Serial.print("Gas: "); Serial.print(gasValue); Serial.print("\t");
    Serial.print("Res Soil: "); Serial.print(soilResistiveValue); Serial.print("\t");
    Serial.print("Cap Soil: "); Serial.println(soilCapacitiveValue);
  }
}

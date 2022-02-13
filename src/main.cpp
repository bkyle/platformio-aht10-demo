#include <Adafruit_AHTX0.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>

#define SDA 16
#define SCL 17
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

TwoWire i2c(SDA, SCL);
Adafruit_AHTX0 aht;
Adafruit_SSD1306 ssd1306(SSD1306_WIDTH, SSD1306_HEIGHT, &i2c);

void setup() {
  Serial.begin(9600);

  // Initialize the AHT10 sensor at its default address, 0x38.
  bool ok = aht.begin(&i2c);
  if (!ok) {
    while (true) {
      Serial.println("No AHT");
      delay(500);
    }
  }
  Serial.println("AHT initialized");

  // Initialize the SSD1306 display at address 0x3C
  ok = ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, true);
  if (!ok) {
    while (true) {
      Serial.println("No SSD1309");
      delay(500);
    }
  }
}

void loop() {
  sensors_event_t temp, humidity;

  aht.getEvent(&humidity, &temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.print("C");
  Serial.print("    ");
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.print("%");
  Serial.println();

  ssd1306.clearDisplay();
  ssd1306.setTextColor(SSD1306_WHITE);
  ssd1306.setCursor(0, 20);

  ssd1306.print("Temperature: ");
  ssd1306.print(temp.temperature);
  ssd1306.println(" C");
  ssd1306.println();
  ssd1306.print("   Humidity: ");
  ssd1306.print(humidity.relative_humidity);
  ssd1306.println(" %");

  ssd1306.display();

  delay(5000);
}

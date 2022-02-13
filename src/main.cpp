#include <Adafruit_AHTX0.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Fonts/FreeSans12pt7b.h>

#define SDA 16
#define SCL 17
#define AHT_ADDRESS 0x38
#define SSD1306_ADDRESS 0x3C

TwoWire ahtI2C(SDA, SCL);
Adafruit_AHTX0 aht;

TwoWire displayI2C(SDA, SCL);
Adafruit_SSD1306 ssd1306((uint8_t)128, (uint8_t)64, &displayI2C);

void setup() {
  Serial.begin(9600);

  ahtI2C.begin(AHT_ADDRESS);
  bool ok = aht.begin(&ahtI2C);
  if (!ok) {
    while (true) {
      Serial.println("No AHT");
      delay(500);
    }
  }
  Serial.println("AHT initialized");

  ok = ssd1306.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS, false, true);
  if (!ok) {
    while (true) {
      Serial.println("No SSD1309");
      delay(500);
    }
  }
  ssd1306.clearDisplay();
  ssd1306.setTextColor(SSD1306_WHITE);
  // ssd1306.setFont(&FreeSans12pt7b);
  ssd1306.setTextSize(1);
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

  ssd1306.setCursor(0, 20);
  ssd1306.print("Temperature: ");
  ssd1306.print(temp.temperature);
  ssd1306.println("C");

  ssd1306.println();

  ssd1306.print("Humidity:    ");
  ssd1306.print(humidity.relative_humidity);
  ssd1306.println("%");

  ssd1306.display();

  delay(5000);
}

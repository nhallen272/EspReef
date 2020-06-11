#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
/*Wifi Libraries
#include "connect_wifi.h"
#include <FS.h>
*/
// Screen definitions
#define OLED_RESET -1
#define SDA 5
#define SCL 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// GPIO of temp sensor and OneWire instance
const int oneWireBus = 0;
OneWire temp_wire(oneWireBus);
// Pass ref of onewire to dallas temp.
DallasTemperature temp_sensor(&temp_wire);


// Display instance 0x3, SDA, SCL
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  // Setup the SSD1306
  Wire.begin(SDA, SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  // screen splash and text setup
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
  
  // begin the temp sensor
  temp_sensor.begin();
  

}

void loop()
{
  // Setup display for printing text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  // setCursor to middle of screen.
 
  
  // Request temperature
  temp_sensor.requestTemperatures();
  float temperatureF = temp_sensor.getTempFByIndex(0);
  Serial.print(temperatureF);
  Serial.println("ºF");
  // Print to display
  display.clearDisplay();
  display.display();
  display.setCursor(5, 16);
  display.println("Temp:");
  display.setCursor(5, SCREEN_HEIGHT / 2);
  display.setTextSize(3);
  display.print(temperatureF);
  display.println("F");
  display.display();
  
  // Wait 10 secs between readings
  delay(10000);
  
  
 
  

}

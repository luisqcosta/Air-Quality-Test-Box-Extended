#include <DS1307.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include "DHT.h"
#include <avr/pgmspace.h>

static unsigned char LCAlogo[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07,
0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F,
0x0F, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x64, 0x66, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F,
0x7F, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF,
0x7F, 0x3F, 0x3F, 0x0F, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0xF8, 0xF8, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0xC0, 0x40, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x07, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x3F, 0x20, 0x20, 0x20, 0x00, 0x0E,
0x1F, 0x39, 0x30, 0x20, 0x20, 0x20, 0x20, 0x30, 0x1C, 0x0F, 0x09, 0x08, 0x09, 0x0F, 0x1C, 0x38,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F,
0x7F, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xF0, 0xC0, 0xC0, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF,
0x7F, 0x3F, 0x1F, 0x0F, 0x0F, 0x0F, 0x1F, 0x3F, 0x78, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x11, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x20, 0x20, 0x20, 0xE0, 0xE0, 0x20, 0x20, 0x20, 0x00, 0xE0, 0xE0, 0x20, 0x20, 0x20,
0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x80,
0x00, 0x00, 0x00, 0x00, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0,
0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xE1, 0xE1,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0xC1, 0x41, 0x41, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x22, 0x22, 0x20,
0x00, 0x30, 0x1C, 0x0E, 0x09, 0x08, 0x09, 0x0F, 0x1C, 0x38, 0x20, 0x20, 0x3C, 0x07, 0x01, 0x03,
0x0E, 0x1C, 0x04, 0x03, 0x01, 0x07, 0x1E, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
0x07, 0x0F, 0x1F, 0x3E, 0x7C, 0xFC, 0xF8, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF,
0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F,
0x7F, 0xFF, 0xFE, 0xFE, 0xFE, 0x1E, 0x1E, 0x0F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0E, 0x1F, 0x31, 0x20, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xF1, 0xE0,
0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xE0, 0xF9, 0xFF, 0xFF, 0x7F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
0x07, 0x0F, 0x1F, 0x3E, 0x3C, 0x7C, 0xF8, 0xF8, 0xF0, 0xF0, 0xF8, 0x7C, 0x3C, 0x3E, 0x1F, 0x0F,
0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//initialization

int pin = 8; //inititalizing digital pin 8, dust sensor
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
int sensorValueA = 0; //Ch4 sensor A0
int sensorValueB = 0; //VOC sensor A1
int sensorValueC = 0; //loudness sensor A2

#define DHTPIN A3 //defining temp and humi sensor analog pin A3
#define DHTTYPE DHT11 //define the type of sensor. check the specsheet and seeed wiki
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  
Wire.begin();

SeeedOled.init(); //initialze SEEED OLED display
DDRB |= 0x21;
PORTB |= 0x21;
SeeedOled.setNormalDisplay(); // Set normal display
SeeedOled.clearDisplay(); // clear the screen and set start position to top left corner
SeeedOled.drawBitmap(LCAlogo, 1024); // 1024 = 128 Pixels * 64 Pixels / 8
delay(3000);
SeeedOled.clearDisplay(); // end of logo display

Serial.begin(9600); //seting the serial speed. if including more sensors increase to a standard value. not needed at the moment as overall sampling speed is +/-5 secs (use 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200)

starttime = millis();
Serial.println("Air Quality Gizmo by LMO");
Serial.println("Time s, Humidity %, Temperature C, PM ug/m^3, VOC mg/m^3, Hydrocarbs mg/dm^3, Sound Pressure %"); //header of the text file; can be imported as csv in excell
dht.begin();
}

void loop() {
  
float vol_meth; // CH4 sensor
sensorValueA = analogRead(A0);
vol_meth = (float)sensorValueA / 2048 * 25.0; // unit conversion to mg/dm3

float vol_voc; // VOC sensor
sensorValueB = analogRead(A1);
vol_voc = (float)sensorValueB / 1024 * 1.2; // unit conversion to mg/m3

float vol_loud; // Loudness sensor
sensorValueC = analogRead(A2);
vol_loud = (float)sensorValueC / 1024 * 100; // Sound pressure in %

// Dust sensor begin
pinMode(8, INPUT); // digital pin for dust sensor
duration = pulseIn(pin, LOW);
lowpulseoccupancy = lowpulseoccupancy + duration;
if ((millis() - starttime) > sampletime_ms)
{
ratio = lowpulseoccupancy / (sampletime_ms * 10.0); // Integer percentage 0=>100
concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve
lowpulseoccupancy = 0;
starttime = millis();
}
// dust sensor end
float h = dht.readHumidity(); //sensor pooling time of 2 seconds (both temp and humi)
float t = dht.readTemperature();

{
Serial.print(millis()/1000); // elapsed seconds since boot
Serial.print(",");
Serial.print(h,1);
Serial.print(",");
Serial.print(t,1);
Serial.print(",");
Serial.print(concentration / 500,3);
Serial.print(",");
Serial.print(vol_voc,3);
Serial.print(",");
Serial.print(vol_meth,3);
Serial.print(",");
Serial.print(vol_loud,3);
Serial.println("");

// no need to include any SD library as Open Hardware SD Logger works as a standalone arduino and records all serial output
}
{
SeeedOled.clearDisplay();
SeeedOled.setTextXY(1, 1);
SeeedOled.putString("Particulates:");
SeeedOled.setTextXY(2, 1);
SeeedOled.putFloat((concentration / 500),4);
SeeedOled.setTextXY(2, 8);
SeeedOled.putString("ug/m^3");
SeeedOled.setTextXY(3, 1);
SeeedOled.putString("Volatile OC:");
SeeedOled.setTextXY(4, 1);
SeeedOled.putFloat(vol_voc,4);
SeeedOled.setTextXY(4, 8);
SeeedOled.putString("mg/m^3");
SeeedOled.setTextXY(5, 1); // location of text , fifth row, first collumn
SeeedOled.putString("Methane:");
SeeedOled.setTextXY(6, 1); // location to display variable
SeeedOled.putFloat(vol_meth,4); // variable to display
SeeedOled.setTextXY(6, 8);
SeeedOled.putString("mg/dm^3");

delay(2000); // screen delay to allow reading in the OLED

SeeedOled.clearDisplay();
SeeedOled.setTextXY(1, 1);
SeeedOled.putString("Loudness:");
SeeedOled.setTextXY(2, 1);
SeeedOled.putFloat(vol_loud,2);
SeeedOled.setTextXY(2, 7);
SeeedOled.putString("%");
SeeedOled.setTextXY(3, 1);
SeeedOled.putString("Humidity:");
SeeedOled.setTextXY(4, 1);
SeeedOled.putFloat(h,1);
SeeedOled.setTextXY(4, 7);
SeeedOled.putString("%");
SeeedOled.setTextXY(5, 1);
SeeedOled.putString("Temperature:");
SeeedOled.setTextXY(6, 1);
SeeedOled.putFloat(t,1);
SeeedOled.setTextXY(6, 7);
SeeedOled.putString("C");
}
}

/* Arduino Weather Station
 * 
 * Sketch for a compact Arduino Weather Station composed of a DHT11 sensor, an LCD display, and (soon) a Wi-Fi module
 * The sensor calculates the actual temperature, heat index (air temperature combined with relative humidity, in shaded areas), but not "feels like"/apparent temperature (heat index stuff, combined with wind speed/wind chill)
 * TODO: maybe try adding buttons or resistors to reduce backlight strength? it is too bright in the dark
 * TODO: also, adding push buttons to toggle between temperature / humidity / heat index, and between °F and °C would be a nice addition
 *
 */

// include libraries
#include <LiquidCrystal.h>
#include "DHT.h"

// digital pin connected to the DHT sensor
// (note for "Feather HUZZAH ESP8266" board: use pins 3, 4, 5, 12, 13 or 14; pin 15 can work but DHT must be disconnected during program upload): 
// (current board is Arduino UNO so ignore about note above)
#define DHTPIN 8

// define as whatever type of sensor you're using: DHT11 / DHT21 / DHT22
#define DHTTYPE DHT11   // DHT11 // DHT21: (AM2301) // DHT22: (AM2302, AM2321)

// initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initialize DHT sensor
// (note that older versions of this library took an optional third parameter to tweak the timings for faster processors)
// (this parameter is no longer needed as the current DHT reading algorithm adjusts itself to work on faster processors)
DHT dht(DHTPIN, DHTTYPE);

// sketch members
int dhtMs = 0;   // Delta in miliseconds since last DHT run
const int DHTDELAY = 3000;   // DHT sensor (simulated) delay
String degC = "__";   // Temperature in Celsius degrees, as String

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.blink();   // note: the cursor will flicker on all characters slots if not given enough time to show up; avoid printing text on the main loop to prevent the cursor from distorting text output

  // print a placeholder message to the LCD, while the sensor obtains the first reading
  lcd.print("Loading...");
	
	// DHT sensor setup code
	Serial.begin(9600);   // Set BPS rate for serial communication (for Serial Monitor only, at the moment)
  Serial.println(F("DHT11 test!"));
  dht.begin();
}

// note that delays cannot be used like in the "DHT tester" example, both devices (LCD and DHT11) must run sequentially without stopping each other, simulating parallel execution
// TODO: also note that the millis() variable will reset to 0 after some time... But one problem at a time, I will address this later
void loop() {
  // DHT code: runs once approximately every DHTDELAY miliseconds because: 
  // - reading temperature or humidity takes about 250 milliseconds
  // - DHT11 sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	if (int(millis() - dhtMs) >= DHTDELAY) {		
		float h = dht.readHumidity();
		float t = dht.readTemperature();
		float f = dht.readTemperature(true);
		
		dhtMs = millis(); // this is placed here so "return" doesn't leave the loop before resetting this variable

		if (isnan(h) || isnan(t) || isnan(f)) {
	    Serial.println(F("Failed to read from DHT sensor!"));
  	  return;
	  }

    degC = String(t); // once validated, the new value can be stored to the display variable
		
		float hif = dht.computeHeatIndex(f, h);
		float hic = dht.computeHeatIndex(t, h, false);
		
		Serial.print(F("Humidity: "));
	  Serial.print(h);
	  Serial.print(F("%  Temperature: "));
	  Serial.print(t);
	  Serial.print(F("°C "));
	  Serial.print(f);
	  Serial.print(F("°F  Heat index: "));
	  Serial.print(hic);
	  Serial.print(F("°C "));
	  Serial.print(hif);
	  Serial.println(F("°F"));

    // overwrites the previous "standing" text, and allows the blinking cursor to show up
    lcd.noBlink();
    lcd.setCursor(0, 0);   // set cursor at first column (0) of first line (0)
    lcd.print("Weather Station");
    lcd.setCursor(0, 1);   // set cursor at first column (0) of second line (1)
    // (note that this LCD driver uses a custom charset, different than ASCII; the character code to get the degrees symbol "char(223)" was obtained from the datasheet of 1602A LCD display)
    lcd.print("T=" + degC + char(223) + 'C');
	}
}

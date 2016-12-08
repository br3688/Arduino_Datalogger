#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

void setup(void)
{
	// start serial port
	Serial.begin(9600);
	sensors.begin();

	// Method 1:
	// search for devices on the bus and assign based on an index.  ideally,
	// you would do this to initially discover addresses on the bus and then 
	// use those addresses and manually assign them (see above) once you know 
	// the devices on your bus (and assuming they don't change).
	if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

	// set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
	sensors.setResolution(insideThermometer, 9);
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
	float tempC = sensors.getTempC(deviceAddress);
	//Serial.print("Temp C: ");
	//Serial.print(tempC);
	//Serial.print(" Temp F: ");
	Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}

void loop(void)
{
	sensors.requestTemperatures(); // Send the command to get temperatures

								   // It responds almost immediately. Let's print out the data
	printTemperature(insideThermometer); // Use a simple function to print out the data
										 //delay(5*60*1000UL);
}
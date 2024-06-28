
#include <Wire.h> // Include the I2C library

void setup() {
  Wire.begin();  // Initialize the I2C bus
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  while (!Serial);    // Wait for the serial communication to start
  Serial.println("\nI2C Scanner"); // Print message to serial monitor
}

void loop() {
  byte error, address; // Variables to store error flag and device address
  int nDevices; // Variable to count number of devices found

  Serial.println("Scanning..."); // Print scanning message

  nDevices = 0; // Initialize device count to zero
  for (address = 1; address < 127; address++) { // Scan all addresses from 1 to 126
    Wire.beginTransmission(address); // Start transmission to the I2C device
    error = Wire.endTransmission(); // End transmission and check for error

    if (error == 0) { // If no error, device found
      Serial.print("I2C device found at address 0x"); // Print device found message
      if (address < 16) Serial.print("0"); // Add leading zero for single digit addresses
      Serial.print(address, HEX); // Print address in hexadecimal format
      Serial.println("  !");

      nDevices++; // Increment device count
    } else if (error == 4) { // If error 4, unknown error
      Serial.print("Unknown error at address 0x"); // Print unknown error message
      if (address < 16) Serial.print("0"); // Add leading zero for single digit addresses
      Serial.println(address, HEX); // Print address in hexadecimal format
    }
  }
  if (nDevices == 0) // If no devices found
    Serial.println("No I2C devices found\n"); // Print no devices found message
  else
    Serial.println("done\n"); // Print done message

  delay(5000); // Wait 5 seconds before scanning again
}

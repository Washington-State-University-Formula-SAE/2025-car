// #include "BMI088.h"
// #include <SparkFun_u-blox_GNSS_Arduino_Library.h>
// #include <Wire.h>
// #include <SD.h>

// Bmi088Accel accel(Wire,0x18);
// Bmi088Gyro gyro(Wire,0x68);

// SFE_UBLOX_GNSS myGNSS;


// #define PIN_SPI_CS 10

// File file;
// char buf[] = "Arduino";

// void setup() {
//   Serial.begin(9600);

// if (!SD.begin(BUILTIN_SDCARD)) {
//     Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
//     while(1);
// }



//   SD.remove("arduino.txt"); // delete the file if existed

//   // create new file by opening file for writing
//   file = SD.open("arduino.txt", FILE_WRITE);

//   if (file) {
//     file.write('H'); // a character
//     file.write('i'); // a character
//     file.write('\n'); // new line
//     file.write(buf, 7);

//     file.close();
//   } else {
//     Serial.print(F("SD Card: error on opening file arduino.txt"));
//   }

//   accel.begin();
//   gyro.begin();

//   pinMode(24, INPUT_PULLUP);
// 	pinMode(25, INPUT_PULLUP);

//   Wire2.begin();


//   // myGNSS.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

//   // myGNSS.begin(Wire2);
//   if (myGNSS.begin(Wire2) == false) //Connect to the u-blox module using Wire port
// 	{
// 		Serial.println(F("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing."));
// 		while (1);
// 	}
//   myGNSS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
// 	myGNSS.setNavigationFrequency(10); //Produce two solutions per second
// 	myGNSS.setAutoPVT(true); //Tell the GNSS to "send" each solution
// 	// myGNSS.saveConfiguration();
// }

// void loop() {
//   accel.readSensor();
//   gyro.readSensor();

// myGNSS.checkUblox(); // Check for the arrival of new data and process it.
// 	int latitude = myGNSS.getLatitude();
// 	int longitude = myGNSS.getLongitude();
// 	int altitude = myGNSS.getAltitude();
// 	int groundSpeed = myGNSS.getGroundSpeed();
	
// 	int SIV = myGNSS.getSIV();

// 	Serial.println(String(latitude) + "|" 
// 				+ String(longitude) + "|" 
// 				+ String(altitude) + "|"
// 				+ String(groundSpeed) + "|" 
// 				+ String(SIV) + "|"
// 				  );
//   delay(100);

//   Serial.printf("ACEL:\tx: %f\ty: %f\tz: %f\n", accel.getAccelX_mss(), accel.getAccelY_mss(), accel.getAccelZ_mss());
//   Serial.printf("GYRO:\tx: %f\ty: %f\tz: %f\n", gyro.getGyroX_rads(), gyro.getGyroY_rads(), gyro.getGyroZ_rads());
//   Serial.println();
// }

// Basic demo for readings from Adafruit BNO08x
#include <Adafruit_BNO08x.h>

// For SPI mode, we need a CS pin
#define BNO08X_CS 10
#define BNO08X_INT 9
#define BNO08X_I2C_ADDRESS 0x4B
// For SPI mode, we also need a RESET
//#define BNO08X_RESET 5
// but not for I2C or UART
#define BNO08X_RESET -1
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup(void) {
    Wire.begin();
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit BNO08x test!");

  // Try to initialize!
  if (!bno08x.begin_I2C(BNO08X_I2C_ADDRESS)) {
    // if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte
    // UART buffer! if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
       Serial.println("Failed to find BNO08x chip");
    while (1) {
      delay(10);
    }
  }
    Serial.println("BNO08x Found!");

  for (int n = 0; n < bno08x.prodIds.numEntries; n++) {
    

        Serial.print("Part ");
        Serial.print(bno08x.prodIds.entry[n].swPartNumber);
        Serial.print(": Version :");
        Serial.print(bno08x.prodIds.entry[n].swVersionMajor);
        Serial.print(".");
        Serial.print(bno08x.prodIds.entry[n].swVersionMinor);
        Serial.print(".");
        Serial.print(bno08x.prodIds.entry[n].swVersionPatch);
        Serial.print(" Build ");
        Serial.println(bno08x.prodIds.entry[n].swBuildNumber);
    
  }

  setReports();
  checkI2C();
  


  //  Serial.println("Reading events");
  delay(100);
}

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  if (!bno08x.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED)) {
      Serial.println("Could not enable magnetic field calibrated");
  }

  if (!bno08x.enableReport(SH2_MAGNETIC_FIELD_UNCALIBRATED)) {
      Serial.println("Could not enable magnetic field calibrated");
  }


  if (!bno08x.enableReport(SH2_RAW_MAGNETOMETER)) {
    Serial.println("Could not enable magnetic field uncalibrated");
  }


}

void checkI2C() {
  int nDevices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
    // The i2c_scanner uses the return value of
    // the Wire.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("done\n");
  }
}






void loop() {
  delay(10);

  if (bno08x.wasReset()) {
    //   Serial.print("sensor was reset ");
    setReports();
  }

  if (!bno08x.getSensorEvent(&sensorValue)) {
    return;
  }

  switch (sensorValue.sensorId) {

    case SH2_MAGNETIC_FIELD_CALIBRATED:
      Serial.print(sensorValue.un.magneticField.x, 6);
      Serial.print(", "); Serial.print(sensorValue.un.magneticField.y, 6);
      Serial.print(", "); Serial.print(sensorValue.un.magneticField.z, 6);
      break;

    case SH2_MAGNETIC_FIELD_UNCALIBRATED:
       Serial.print(", ");Serial.print(sensorValue.un.magneticFieldUncal.x, 6);
      Serial.print(", "); Serial.print(sensorValue.un.magneticFieldUncal.y, 6);
      Serial.print(", "); Serial.print(sensorValue.un.magneticFieldUncal.z, 6);
      break;

    case SH2_RAW_MAGNETOMETER:
      Serial.print(", ");Serial.print(sensorValue.un.rawMagnetometer.x);
      Serial.print(", ");Serial.print(sensorValue.un.rawMagnetometer.y);
      Serial.print(", "); Serial.println(sensorValue.un.rawMagnetometer.z);
      break;

      delay(BNO055_SAMPLERATE_DELAY_MS);


  }
}

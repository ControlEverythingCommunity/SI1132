// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SI1132
// This code is designed to work with the SI1132_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// SI1132 I2C address is 0x60(96)
#define Addr 0x60

float visible = 0.0, ir = 0.0, uv = 0.0;
int response = 0;

void setup()
{
  Particle.variable("i2cdevice", "SI1132");
  Particle.variable("visible", visible);
  Particle.variable("uv", uv);
  Particle.variable("ir", ir);
  
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, Baud rate = 9600
  Serial.begin(9600);

  // Enable UVindex measurement coefficients
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COFF-1 register
  Wire.write(0x13);
  // Default value
  Wire.write(0x29);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COFF-2 register
  Wire.write(0x14);
  // Default value
  Wire.write(0x89);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COFF-3 register
  Wire.write(0x15);
  // Default value
  Wire.write(0x02);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COFF-4 register
  Wire.write(0x16);
  // Default value
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();


  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Enable uv, Visible, IR
  Wire.write(0xF0);
  // Stop I2C Transmission
  Wire.endTransmission();


  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select command register
  Wire.write(0x18);
  // Select CHLIST register in RAM
  Wire.write(0x01 | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select HW_KEY register
  Wire.write(0x07);
  // Default value
  Wire.write(0x17);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Small IR photodiode
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Select ALS_IR_ADCMUX register in RAM
  Wire.write(0x0E | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Set ADC Clock divided / 1
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Select ALS_IR_ADC_GAIN register in RAM
  Wire.write(0x1E | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Set 511 ADC Clock
  Wire.write(0x70);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  /// Select ALS_IR_ADC_COUNTER register in RAM
  Wire.write(0x1D | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Set ADC Clock divided / 1
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
 // Select ALS_VIS_ADC_GAIN register in RAM
  Wire.write(0x11 | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // High Signal Range
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Select ALS_IR_ADC_MISC register in RAM
  Wire.write(0x1F | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // Set 511 ADC Clock
  Wire.write(0x70);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Select ALS_VIS_ADC_COUNTER register in RAM
  Wire.write(0x10 | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_WR register
  Wire.write(0x17);
  // High Signal Range
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Select ALS_VIS_ADC_MISC register in RAM
  Wire.write(0x12 | 0xA0);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(10);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select PARAM_RD register
  Wire.write(0x2E);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);
  // Read 1 byte of data
  response = Wire.read();
  delay(300);
}

void loop()
{
  unsigned int data[4];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select COMMAND register
  Wire.write(0x18);
  // Start ALS conversion
  Wire.write(0x0E);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(500);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x22);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 4 byte of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // visible lsb, visible msb, ir lsb, ir msb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  visible = (data[1] * 256.0 + data[0]);
  ir = (data[3] * 256.0 + data[2]);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x2C);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // uv lsb, uv msb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  
  // Convert the data
  uv = (data[1] * 256.0 + data[0]);

  // Output data to screen
  Particle.publish("Visible Light of Source : ", String(visible));
  delay(100);
  Particle.publish("IR Of Source : ", String(ir));
  delay(100);
  Particle.publish("UV Of the Source : ", String(uv));
  delay(1000);
}



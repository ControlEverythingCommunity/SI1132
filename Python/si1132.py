# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# SI1132
# This code is designed to work with the SI1132_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Light?sku=SI1132_I2CS#tabs-0-product_tabset-2

#import usmbus as smbus
#import smbus
import time
from machine import Pin

class SI1132:
    def __init__(
                 self,
                 smbus=None):
        self.bus = smbus
    
    def read(self):
        # SI1132 address, 0x60(96)
        # Enable UVindex measurement coefficients
        self.bus.write_byte_data(0x60, 0x13, 0x29)
        self.bus.write_byte_data(0x60, 0x14, 0x89)
        self.bus.write_byte_data(0x60, 0x15, 0x02)
        self.bus.write_byte_data(0x60, 0x16, 0x00)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        # 		0xF0(15)	Enable UV, Visible, IR
        self.bus.write_byte_data(0x60, 0x17, 0xF0)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x01 | 0xA0(161)   Select CHLIST register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x01 | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select INT Output Enable register, 0x03(03)
        #		0x01(01)	INT pin driven low
        self.bus.write_byte_data(0x60, 0x03, 0x01)
        # SI1132 address, 0x60(96)
        # Select ALS Interrupt Enable register, 0x04(04)
        #		0x01(01)	Assert INT pin whenever VIS or UV measurements are ready
        self.bus.write_byte_data(0x60, 0x04, 0x01)
        # SI1132 address, 0x60(96)
        # Select HW_KEY register, 0x07(07)
        #		0x17(23)	Default value
        self.bus.write_byte_data(0x60, 0x07, 0x17)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        #		0x00(0)		Small IR photodiode
        self.bus.write_byte_data(0x60, 0x17, 0x00)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x0E | 0xA0(174)    Select ALS_IR_ADCMUX register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x0E | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        #		0x00(0)		Set ADC Clock divided / 1
        self.bus.write_byte_data(0x60, 0x17, 0x00)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x1E | 0xA0(190)    Select ALS_IR_ADC_GAIN register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x1E | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        # 		0x70(112)	Set 511 ADC Clock
        self.bus.write_byte_data(0x60, 0x17, 0x70)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x1D | 0xA0(189)    Select ALS_IR_ADC_COUNTER register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x1D | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        # 		0x00(0)		Set ADC Clock divided / 1
        self.bus.write_byte_data(0x60, 0x17, 0x00)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x11 | 0xA0(177)    Select ALS_VIS_ADC_GAIN register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x11 | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        #		0x20(32)	High Signal Range
        self.bus.write_byte_data(0x60, 0x17, 0x20)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x1F | 0xA0(191)    Select ALS_IR_ADC_MISC register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x1F | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        # 		0x70(112)	Set 511 ADC Clock
        self.bus.write_byte_data(0x60, 0x17, 0x70)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x10 | 0xA0(176)    Select ALS_VIS_ADC_COUNTER register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x10 | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select PARAM_WR register, 0x17(23)
        #		0x20(32)	High Signal Range
        self.bus.write_byte_data(0x60, 0x17, 0x20)
        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x12 | 0xA0(178)    Select ALS_VIS_ADC_MISC register in RAM
        self.bus.write_byte_data(0x60, 0x18, (0x12 | 0xA0))
        time.sleep(0.01)
        # SI1132 address, 0x60(96)
        # Read data back from 0x2E(46), 1 byte
        response = self.bus.read_byte_data(0x60, 0x2E)

        # SI1132 address, 0x60(96)
        # Select COMMAND register, 0x18(24)
        #		0x0E(14)	Start ALS conversion
        self.bus.write_byte_data(0x60, 0x18, 0x0E)
        time.sleep(0.5)

        # SI1132 address, 0x60(96)
        # Read data back from 0x22(34), 4 bytes
        # visible lsb, visible msb, ir lsb, ir msb
        data = self.bus.read_i2c_block_data(0x60, 0x22, 4)

        # Convert the data
        visible = data[1] * 256 + data[0]
        ir = data[3] * 256 + data[2]

        # SI1132 address, 0x60(96)
        # Read data back from 0x2C(44), 2 bytes
        # uv lsb, uv msb
        data = self.bus.read_i2c_block_data(0x60, 0x2C, 2)

        # Convert the data
        uv = data[1] * 256 + data[0]

        # Output data to screen
        #print("Visible Light of Source : %d lux" %visible)
        #print("IR Of Source : %d lux" %ir)
        #print("UV Of the Source : %d lux" %uv)
        print('si1132 uv, ir, visible = %d, %d, %d lux' % (uv, ir, visible))
        return uv, ir, visible

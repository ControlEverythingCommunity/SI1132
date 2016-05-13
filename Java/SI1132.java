import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class SI1132
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, SI1132 I2C address is 0x60(96)
		I2CDevice device = bus.getDevice(0x60);
		
		// Enable UVindex measurement coefficients
		device.write(0x13, (byte)0x29);
		device.write(0x14, (byte)0x89);
		device.write(0x15, (byte)0x02);
		device.write(0x16, (byte)0x00);
		
		// Select PARAM_WR register
		// Enable UV, Visible, IR
		device.write(0x17, (byte)0xF0);
		// Select COMMAND register
		// Select CHLIST register in RAM
		device.write(0x18, (byte)(0x01 | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		byte status = (byte)device.read(0x2E);
		
		// Select INT Output Enable register
		// INT pin driven low
		device.write(0x03, (byte)0x01);
		
		// Select ALS Interrupt Enable register
		// Assert INT pin whenever VIS or UV measurements are ready
		device.write(0x04, (byte)0x01);
		
		// Select HW_KEY register
		// Default value
		device.write(0x07, (byte)0x17);
		
		// Select PARAM_WR register
		// Small IR photodiode
		device.write(0x17, (byte)0x00);
		// Select COMMAND register
		// Select ALS_IR_ADCMUX register in RAM
		device.write(0x18, (byte)(0x0E | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// Set ADC Clock divided / 1
		device.write(0x17, (byte)0x00);
		// Select COMMAND register
		// Select ALS_IR_ADC_GAIN register in RAM
		device.write(0x18, (byte)(0x1E | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// Set 511 ADC Clock
		device.write(0x17, (byte)0x70);
		// Select COMMAND register
		// Select ALS_IR_ADC_COUNTER register in RAM
		device.write(0x18, (byte)(0x1D | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// Set ADC Clock divided / 1
		device.write(0x17, (byte)0x00);
		// Select COMMAND register
		// Select ALS_VIS_ADC_GAIN register in RAM
		device.write(0x18, (byte)(0x11 | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// High Signal Range
		device.write(0x17, (byte)0x20);
		// Select COMMAND register
		// Select ALS_IR_ADC_MISC register in RAM
		device.write(0x18, (byte)(0x1F | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// Set 511 ADC Clock
		device.write(0x17, (byte)0x70);
		// Select COMMAND register
		// Select ALS_VIS_ADC_COUNTER register in RAM
		device.write(0x18, (byte)(0x10 | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select PARAM_WR register
		// High Signal Range
		device.write(0x17, (byte)0x20);
		// Select COMMAND register
		// Select ALS_VIS_ADC_MISC register in RAM
		device.write(0x18, (byte)(0x12 | 0xA0));
		Thread.sleep(10);
		// Select PARAM_RD register
		// Read 1 byte of data
		status = (byte)device.read(0x2E);
		
		// Select COMMAND register
		// Start ALS conversion
		device.write(0x18, (byte)0x0E);
		Thread.sleep(500);
		
		// Read 4 bytes from address 0x22(34)
		// visible lsb, visible msb, ir lsb, ir msb
		byte[] data = new byte[4];
		device.read(0x22, data, 0, 4);
		
		// Convert the data
		int visible = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF));
		int ir = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF));
		
		// Read 2 bytes from address 0x2C(44)
		// uv lsb, uv msb
		device.read(0x2C, data, 0, 2);
		
		// Convert the data
		int uv = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF));
		
		// Output data to screen
		System.out.printf("Ambient Light Of Source : %d lux %n", visible);
		System.out.printf("IR Of Source : %d lux %n", ir);
		System.out.printf("UV Of the Source : %d lux %n", uv);
	}
}	
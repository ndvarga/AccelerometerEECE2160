#include "GSensor.h"
using namespace std;

GSensor::GSensor() : DE1SoChps() {

	cout << "Objects created" << endl;
	PinmuxConfig();
	I2C0_Init();
}

void GSensor::PinmuxConfig() {
	RegisterWrite(PIN_MUX_I2C0USEFPGA, 0);
	RegisterWrite(PIN_MUX_GEN_I07, 1);
	RegisterWrite(PIN_MUX_GEN_I08, 1);	
}

void GSensor::I2C0_Init() {
	// Abort any ongoing transmits and disable I2C0.
	RegisterWrite(I2C0_ENABLE, 2); //ABORTS ANY pending transmissions
	// Wait until I2C0 is disabled
	while ((RegisterRead(I2C0_ENABLE_STATUS) & 0x1) == 1) {}
	
	// Configure the config reg with the desired setting (act as
	// a master, use 7bit addressing, fast mode (400kb/s)).
	RegisterWrite(I2C0_CON, 0x65);

	// Set target address (disable special commands, use 7bit addressing)
	RegisterWrite(I2C0_TAR, 0x53);
	
	// Set SCL high/low counts (Assuming default 100MHZ clock input to I2C0 Controller).
	// The minimum SCL high period is 0.6us, and the minimum SCL low period is 1.3us,
	// However, the combined period must be 2.5us or greater, so add 0.3us to each.
	RegisterWrite(I2C0_FS_SCL_HCNT, 60 + 30); // 0.6us + 0.3us
	RegisterWrite(I2C0_FS_SCL_LCNT , 130 + 30); // 1.3us + 0.3us
	
	// Enable the controller
	RegisterWrite(I2C0_ENABLE , 1); //write 1 to enable a transmission

	// Wait until controller is powered on
	while((RegisterRead(I2C0_ENABLE_STATUS) & 0x1) == 0){}
}

void GSensor::ADXL345_Init() {
	// +- 16g range, full resolution
	ADXL345_RegWrite(ADXL345_REG_DATA_FORMAT, XL345_RANGE_16G | XL345_FULL_RESOLUTION);
	 // Output Data Rate: 200Hz
	 ADXL345_RegWrite(ADXL345_REG_BW_RATE, XL345_RATE_200);
	 // The DATA_READY bit is not reliable. It is updated at a much higher rate than the Data Rate
	 // Use the Activity and Inactivity interrupts as indicators for new data.
	ADXL345_RegWrite(ADXL345_REG_THRESH_ACT, 0x04); //activity threshold
	ADXL345_RegWrite(ADXL345_REG_THRESH_INACT, 0x02); //inactivity threshold
	ADXL345_RegWrite(ADXL345_REG_TIME_INACT, 0x02); //time for inactivity
	ADXL345_RegWrite(ADXL345_REG_ACT_INACT_CTL, 0xFF); //Enables AC coupling for thresholds
	ADXL345_RegWrite(ADXL345_REG_INT_ENABLE, XL345_ACTIVITY |XL345_INACTIVITY ); 
	//enable interrupts

	// stop measure
	ADXL345_RegWrite(ADXL345_REG_POWER_CTL, XL345_STANDBY);

	// start measure
	ADXL345_RegWrite(ADXL345_REG_POWER_CTL, XL345_MEASURE);
}

void GSensor::ADXL345_RegRead(uint8_t address, uint8_t *values) {
	// Send reg address (+0x400 to send START signal)
	RegisterWrite(I2C0_DATA_CMD, address + 0x400);

	// Send read signal
	RegisterWrite(I2C0_DATA_CMD, 0x100);
	// Read the response (first wait until RX buffer contains data)
	while (RegisterRead(I2C0_RXFLR) == 0){}
	*values = RegisterRead(I2C0_DATA_CMD);
}	// Write value to internal register at address

void GSensor::ADXL345_RegWrite(uint8_t address, uint8_t value) {
	// Send reg address (+0x400 to send START signal)
	RegisterWrite(I2C0_DATA_CMD, address + 0x400);

	// Send value
	RegisterWrite(I2C0_DATA_CMD, value);
}

void GSensor::ADXL345_Reg_Multi_Read(uint8_t address, uint8_t values[], uint8_t len) {

 	// Send reg address (+0x400 to send START signal)
	RegisterWrite(I2C0_DATA_CMD, address + 0x400);

	// Send read signal len times
	int i;
	for (i=0;i<len;i++)
	RegisterWrite(I2C0_DATA_CMD, 0x100);

	// Read the bytes
	int nth_byte=0;
	while (len){
		if (RegisterRead(I2C0_RXFLR) > 0){
			values[nth_byte] = RegisterRead(I2C0_DATA_CMD);
			nth_byte++;
			len--;
		}
	}
}

void GSensor::ADXL345_XYZ_Read(int16_t szData16[3],int16_t mg_per_lsb) {
	uint8_t szData8[6];
	ADXL345_Reg_Multi_Read(0x32, (uint8_t *)&szData8, sizeof(szData8));

	szData16[0] = ((szData8[1] << 8) | szData8[0]) * mg_per_lsb;
	szData16[1] = ((szData8[3] << 8) | szData8[2]) * mg_per_lsb;
	szData16[2] = ((szData8[5] << 8) | szData8[4]) * mg_per_lsb;
	
}

bool GSensor::ADXL345_IsDataReady() {
	bool bRead = false;
	uint8_t status; //will need to see if annything new pops up
	ADXL345_RegRead(ADXL345_REG_INT_SOURCE, &status);
	if(status & XL345_ACTIVITY)
		bRead = true;

	//check if the data ready is set using the deined constant
	return bRead; //)
}

/**
 * @brief Destruct the GSensor object
 */
GSensor::~GSensor() { cout << "GSensor object destructed." << endl;}

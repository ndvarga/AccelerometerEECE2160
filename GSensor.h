/**
* @file GSensor.h
* @brief Process accelerometer input from from the DE1-SoC
* Reads the XYZ accelerometer data from ADXL345 via the I2C0 line
*/
#ifndef GSENSOR_H
#define GSENSOR_H

// project includes
#include <stdint.h>
#include "ADXL345.h"
#include "DE1SoChps.h"

class GSensor : public DE1SoChps
{
private:
	/* Prototypes for functions used to configure Pin Mux and I2C0 */
	/**
	* Configure I2C Pin Multiplexer to use I2C for ADXL345.
	* - Writes the settings to the corresponding pin_mux registers
	*/
	void PinmuxConfig();
	/**
	* Configure I2C0 for communication with ADXL345
	*- Writes the settings to the corresponding I2C0 registers
	*/
	void I2C0_Init();
public:
	/**
	* Constructor Initializes Pin Multiplexer I2C0
	* by calling the two functions
	*/
	GSensor(); // Constructor
	/**
	* Destructor to finalize G-Sensor module
	* Does nothing other than print a finalizing message
	*/
	~GSensor(); // Destructor
	/* Prototypes for functions used to configure ADXL345 */
	/**
	* Initialize the ADXL345 chip
	*- Writes the settings to the corresponding I2C0 registers
	*/
	void ADXL345_Init();
	/**
	* Read value from internal register at address
	*
	* @param address Address of register to read.
	* @param value Address of value to read
	*/
	void ADXL345_RegRead(uint8_t address, uint8_t *value);
	/**
	* Write value to internal register at address
	* @param address Address of register to write to.
	* @param value Value to write to register
	*/
	void ADXL345_RegWrite(uint8_t address, uint8_t value);
	/**
	* Reads values from multiple internal registers
	*
	* @param address Address of the first register to read.
	* @param values Buffer to read data into
	* @param len Number of registers to read from
	*/
	void ADXL345_Reg_Multi_Read(uint8_t address, uint8_t values[], uint8_t len);
	/**
	* Read acceleration data of all three axes
	*
	* @param szData16 Buffer to read data into
	* @param mg_per_lsb Resolution multiplier factor
	*/
	void ADXL345_XYZ_Read(int16_t szData16[3], int16_t mg_per_lsb);
	/**
	* Return true if there is new data
	*
	* @param None
	* @return None
	*/
	bool ADXL345_IsDataReady();
};

#endif

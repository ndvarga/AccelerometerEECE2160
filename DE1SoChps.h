#ifndef DE1SOCHPS_H
#define DE1SOCHPS_H
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/mman.h> 
#include <iostream> 

using namespace std;
// Physical base address of FPGA Devices 
const unsigned int HPS_BRIDGE_BASE       = 0xFF700000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int HPS_BRIDGE_SPAN	= 0x006FFFFF;  // Address map size

//I2C0 Peripheral Registers
const unsigned int I2C0_BASE		= 0x00504000; //I2C BASE ADDRESS
const unsigned int I2C0_CON		= 0x00504000; //CONTROL REGISTER
const unsigned int I2C0_TAR		= 0x00504004; //TARGET ADDRESS REGISTER
const unsigned int I2C0_DATA_CMD	= 0x00504010; // TX RX DATA AND COMMAND REGISTER
const unsigned int I2C0_FS_SCL_HCNT	= 0x0050401C; //FAST SPEED CLOCK SCL HCNT REGISTER
const unsigned int I2C0_FS_SCL_LCNT	= 0x00504020; //FAST SPEED CLOCK SCL LCNT REGISTER
const unsigned int I2C0_CLR_INTR	= 0x00504040; //COMBINED AND INDIVIDUAL INTERRUPT
const unsigned int I2C0_ENABLE 		= 0x0050406C; //ENABLE REGISTER
const unsigned int I2C0_TXFLR 		= 0x00504074; //TRANSMIT FIFO LEVEL REGISTER
const unsigned int I2C0_RXFLR 		= 0x00504078; //RECEIVE FIFO LEVEL REGISTER
const unsigned int I2C0_ENABLE_STATUS	= 0x0050409C; //ENABLE STATUS REGISTER

//The Pin Multiplexer selection
const unsigned int PIN_MUX_GEN_I07 	= 0x0060849C; 
const unsigned int PIN_MUX_GEN_I08 	= 0x006084A0;
const unsigned int PIN_MUX_GPLMUX55 	= 0x006086B0;
const unsigned int PIN_MUX_GPLMUX56 	= 0x006086B4;
const unsigned int PIN_MUX_I2C0USEFPGA  = 0x00608704;

/*
//Cyclone V FPGA device address
const unsigned int LEDR_BASE            = 0x00000000;  // Leds offset 
const unsigned int SW_BASE              = 0x00000040;  // Switches offset 
const unsigned int KEY_BASE             = 0x00000050;  // Push buttons offset 
const unsigned int HEX3_HEX0_BASE 	= 0x00000020;  //hex register1
const unsigned int HEX5_HEX4_BASE 	= 0x00000030;  //hex register2 offset

//JP2 ports for the robotic arm
const unsigned int JP2_BASE             = 0x00000070;  // J2 data register
const unsigned int JP2_DDR              = 0x00000074;  // Data direction register
*/

class DE1SoChps { 

        private: 

                char *pBase; 
                int fd; 

        public: 

                //initialize the object 
                DE1SoChps();  //constructor
		~DE1SoChps();  //deconstructor
		
		void RegisterWrite(unsigned int reg_offset, int value); 

  
                int RegisterRead(unsigned int reg_offset);
}; 

#endif  


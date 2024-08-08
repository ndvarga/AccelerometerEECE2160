#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/mman.h> 
#include <iostream> 

using namespace std;
// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE       = 0xFF200000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN       = 0x00005000;  // Address map size 

// Cyclone V FPGA device addresses 
//const unsigned int KEY_BASE             = 0x00000050;  // Push buttons offset 

//PIO addresses
const unsigned int OUT_BASE		= 0x00000020; //PIO output
const unsigned int IN_BASE		= 0x00000040; //PIO input

class DE1SoCfpga { 

        private: 

                char *pBase; 
                int fd; 

        public: 

                //initialize the object 
                DE1SoCfpga();  //constructor 
                ~DE1SoCfpga();  //deconstruct the object 

                void RegisterWrite(unsigned int reg_offset, int value); 

  
                int RegisterRead(unsigned int reg_offset); 

  

}; 

#endif  

  

#include <iostream>
#include "DE1SoChps.h"


using namespace std;


                //initialize the object
DE1SoChps::DE1SoChps() //constructor
{
	// Open /dev/mem to give access to physical addresses
	fd = open( "/dev/mem", (O_RDWR | O_SYNC)); 
        if (fd == -1)                  //  check for errors in openning /dev/mem 
	{
		cout << "Error: could not open /dev/mem..." << endl;
		exit(1);
	}

	// Get a mapping from physical address to virtual address
	char *virtual_base = (char *)mmap (NULL, HPS_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HPS_BRIDGE_BASE); 
        if (virtual_base == MAP_FAILED)              // check for errors 
        {
		cout << "ERROR: mmap() failed..." << endl; 
                close(fd);              // close memory before exiting 
                exit(1);        // Returns 1 to the operating system; 
	}
	pBase = virtual_base;
	cout << "created DE1SoChps" << endl;
	cout << pBase << endl;
}

DE1SoChps::~DE1SoChps()  //deconstruct the object 
{ 
	if (munmap (pBase, HPS_BRIDGE_SPAN) != 0) 
        { 
        	cout << "ERROR: munmap() failed..." << endl; 
                exit(1); 
        } 
                close (fd);  // close memory 
}

void DE1SoChps::RegisterWrite(unsigned int reg_offset, int value) 
{ 
        * (volatile unsigned int *)(pBase + reg_offset) = value;
} 

int DE1SoChps::RegisterRead(unsigned int reg_offset) 
{ 
        return * (volatile unsigned int *)(pBase + reg_offset); 
} 


#include <iostream>
#include "GSensor.h"
#include "PIOControl.h"

using namespace std;

int main() {
    //intantiate an object with dunamic memory allocation
    GSensor *gsen = new GSensor();
    PIOControl *pio = new PIOControl();
    
    
    //initate the ADXL chip
    gsen->ADXL345_Init();

    //assume alls good, read the ADXL345 id and verify it, if not right output an error message
    uint8_t deviceID;
    gsen->ADXL345_RegRead(ADXL345_REG_DEVID, &deviceID); 
    
    //quickly check that the object was successfully created
    if(!gsen) {
        cerr << "Error: Failed to intiate object." << endl;
        //return 1 and exit out
        return 1;
    }

    //verify the id
    if(deviceID != 0xE5) {
        cerr << "Error: Incorrect device ID, Expected: " << ADXL345_REG_DEVID <<", Actual: " << deviceID << endl;//wanted the device id
        delete gsen; // then free the memory
        return 1;
    } 
    
    //create a loop that reads and writes the x y and z
    while(true) {
//	cout << "in loop" << endl;
        if(gsen->ADXL345_IsDataReady()) {
	    int xangle;
            int16_t acceleration[3];
	    int16_t mgPerLSB = 4;
            gsen->ADXL345_XYZ_Read(acceleration, mgPerLSB);
	    pio->WritePIOout(acceleration[0]);
	    xangle = pio->ReadAllPIOin();
            //the output the x y and z
            cout << "Acceleration: ";
            for(int i = 0; i < 3; ++i) {
                //the outputs in 16 bit in 2s compliment, mulitply by 4 for LSB
		cout << (acceleration[i]) << " ";
            }
            cout << endl;
	    cout << "X angle: " << xangle << endl;
        }
        //wait for some time to check that theres new data
        usleep(1000); //sleep for 1000 miliseconds
    }

    //cout << "Acceleration (X, Y, Z): " << acceleration[0] << ", " << acceleration[1] << ", " << acceleration[2] << endl;
    
    //delete the object 
    delete gsen;

    return 0;
}

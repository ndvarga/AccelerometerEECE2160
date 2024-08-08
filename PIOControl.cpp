#include <iostream>
#include "DE1SoCfpga.h"
#include "PIOControl.h"
#include <unistd.h>


using namespace std;
PIOControl::PIOControl():DE1SoCfpga() {
        cout << "made PIOControl Object" << endl;
	in_regValue = RegisterRead(IN_BASE);
	out_regValue = RegisterRead(OUT_BASE);
}

int PIOControl::ReadAllPIOin() {
        int sws = RegisterRead(IN_BASE); //use the object to access registerread
	in_regValue = sws;
	//cout << "IN_BASE: " << IN_BASE << "int: " << sws << endl;
        return sws;
}

void PIOControl::WritePIOout(int value) {
        //write the specified value to the board's led
        RegisterWrite(OUT_BASE, value);
	out_regValue = value;
}

PIOControl::~PIOControl() {
        cout << "Closing PIOs......." << endl;
}


#ifndef PIOCONTROL_H
#define PIOCONTROL_H
#include "DE1SoCfpga.h"

class PIOControl : public DE1SoCfpga
{
        private:
               // unsigned int leds_regValue; //the state of the 10 leds register
		unsigned int out_regValue;
		unsigned int in_regValue;
        public:
                PIOControl();
                       // cout << "made LEDControl object" << endl;


                int ReadAllPIOin(); //does not have any inputs

                void WritePIOout(int value);
                ~PIOControl();
};
#endif  //PIOControl_H

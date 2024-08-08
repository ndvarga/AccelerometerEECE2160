MAIN = GSensorMain
PIO = PIOControl

$(MAIN): DE1SoChps.o DE1SoCfpga.o $(PIO).o GSensor.o $(MAIN).o 
	g++ DE1SoChps.o DE1SoCfpga.o  $(PIO).o $(MAIN).o GSensor.o -o $(MAIN)

$(MAIN).o: $(MAIN).cpp GSensor.h $(PIO).h
	g++ -g -Wall -c GSensorMain.cpp 

$(PIO).o: $(PIO).cpp $(PIO).h DE1SoCfpga.h
	g++ -g -Wall -c $(PIO).cpp

GSensor.o: GSensor.cpp GSensor.h ADXL345.h DE1SoChps.h 
	g++ -g -Wall -c GSensor.cpp

DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall -c DE1SoCfpga.cpp

DE1SoChps.o: DE1SoChps.cpp DE1SoChps.h
	g++ -g -Wall -c DE1SoChps.cpp

clean: 
	rm DE1SoChps.o DE1SoCfpga.o $(PIO).o $(MAIN).o $(MAIN) GSensor.o 

 

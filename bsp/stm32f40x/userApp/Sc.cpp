#include "Sc.h"

Sc::Sc(void)
{
	sensorList.Add(&input1Current);
	sensorList.Add(&input2Current);
	sensorList.Add(&inputAc1Voltage);
	sensorList.Add(&inputAc2Voltage);
	sensorList.Add(&inputBusVoltage);
	
	pt100List.Add(&module1Temp);
	pt100List.Add(&module2Temp);
	pt100List.Add(&fanInTemp);
	pt100List.Add(&fanOutTemp);
	pt100List.Add(&cap1Temp);
	pt100List.Add(&cap2Temp);
	
	ioList.Add(&inFuse1);
	ioList.Add(&inFuse2);
	ioList.Add(&outFuse1);
	ioList.Add(&outFuse2);
	ioList.Add(&outFuse3);
	ioList.Add(&outFuse4);
	ioList.Add(&outFuse5);
	
	ContactList.Add(&mainCon1);
	ContactList.Add(&mainCon2);
	ContactList.Add(&preCon);
	ContactList.Add(&outCon1);
	ContactList.Add(&outCon2);
	ContactList.Add(&outCon3);
	ContactList.Add(&outCon4);
	ContactList.Add(&outCon5);
}

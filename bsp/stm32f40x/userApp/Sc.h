#pragma once
#include "DCTransducer.h"
#include "IOTransducer.h"
#include "Contactor.h"
#include "List.h"
#include "PT100.h"
#include "hmi_def.h"
#include "can_app_def.h"
#include "DataStruct.h"

class Sc
{
public:
    Sc(void);
    ~Sc(void)
    {
    }
protected:
    List<ITransducer*> sensorList;
	List<ITransducer*> ioList;
	List<Contactor*> ContactList;
	List<PT100*> pt100List;
public:

	DCTransducer input1Current;
	DCTransducer input2Current;
	DCTransducer inputAc1Voltage;
	DCTransducer inputAc2Voltage;
	DCTransducer inputBusVoltage;

	PT100 module1Temp;
	PT100 module2Temp;
	PT100 fanInTemp;
	PT100 fanOutTemp;
	PT100 cap1Temp;
	PT100 cap2Temp;

	IOTransducer inFuse1;
	IOTransducer inFuse2;
	IOTransducer outFuse1;
	IOTransducer outFuse2;
	IOTransducer outFuse3;
	IOTransducer outFuse4;
	IOTransducer outFuse5;

	Contactor	mainCon1;
	Contactor	mainCon2;
	Contactor	preCon;
	Contactor	outCon1;
	Contactor	outCon2;
	Contactor	outCon3;
	Contactor	outCon4;
	Contactor	outCon5;
	
public:
	ScData shareData;
};

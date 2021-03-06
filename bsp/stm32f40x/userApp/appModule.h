#ifndef _APP_MODULE_H_
#define _APP_MODULE_H_

#include "stm32f4xx.h"
#include <rtthread.h>
#include "MB_DataStruct.h"
#include "logicApp.h"
#include "StateMachine.h"
#include "Relay.h"

class CbMode :public StateMachine
{
public:
	void SetChargeEn(bool a)
	{ chargeEnable = a; }
	void SetCondition(bool isFine)
	{ condition = isFine; }
	
	void SetInstation(bool b)
	{
		Instation = b;
	}
	void SetCharging(bool b)
	{
		Charging = b;
	}
	void SetFloatCharge(bool b)
	{
		floatCharge = b;
	}
	bool GetpwmOnStatus()
	{
		return pwmOnFail;
	}
	bool GetpwuOffStatus()
	{
		return pwmOffFail;
	}
private:
		// ժҪ: 
    //     ģ���Ƿ����?
		uint8_t &   chargeCmd;

		bool	chargeEnable;

		bool	condition;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool 	Instation;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool 	Charging;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool	floatCharge;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool	pwmOnFail;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool	pwmOffFail;
		// ժҪ: 
    //     ģ���Ƿ����?
		bool	chargeComplet;
		// ժҪ: 
    //     ģ���Ƿ����?
		int canIndex;
public:
	CbMode(uint8_t & cmd):chargeCmd(cmd)
	{;}
	Relay * startDelay;
	Relay * floatDelay;
	void Run(void);
	void Init(int index, int mode)
	{
		this->canIndex = index;
		this->modeSet = mode;
	}
	void CB_Idle_Cal(void);
	void CB_Standby_Cal(void);
	void CB_Manual_Cal(void);
	void CB_Auto_Cal(void);
	void CB_Fault_Cal(void);
	void ModuleManage(void);
	void OutputManage(void);

};

#endif

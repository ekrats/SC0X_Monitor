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
	bool GetpwmOnStatus()
	{
		return pwmOnFail;
	}
	bool GetpwuOffStatus()
	{
		return pwmOffFail;
	}
private:
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		int *   chargeCmd;

		bool	chargeEnable;

		bool	condition;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool 	Instation;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool 	Charging;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool	floatCharge;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool	pwmOnFail;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool	pwmOffFail;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		bool	chargeComplet;
		// ÕªÒª: 
    //     Ä£¿éÊÇ·ñ¹ÊÕÏ?
		int canIndex;
public:
	CbMode(void)
	{;}
	Relay * startDelay;
	Relay * floatDelay;
	void Run(void);
	void Init(int index, int mode, int * cmd)
	{
		this->canIndex = index;
		this->modeSet = mode;
		chargeCmd = cmd;
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

#ifndef _APP_MODULE_H_
#define _APP_MODULE_H_

#include "stm32f4xx.h"
#include <rtthread.h>
#include "MB_DataStruct.h"
#include "logicApp.h"
#include "StateMachine.h"

#define CB_STATE_IDLE				0x0000
#define CB_STATE_MANUAL				0x0010
#define CB_STATE_AUTO				0x0020
#define CB_STATE_FAULT				0x0030

#define CB_OUT_IDLE					0x0001
#define CB_OUT_MANUAL				0x0002
#define CB_OUT_STANDY				0x0003
#define CB_OUT_AUTO					0x0004
#define CB_OUT_FAULT				0x0005

#define CHARGE_BASE_T						10//ms

#define CHARGE_START_T						(2000/CHARGE_BASE_T)//启动时间
#define CHARGE_FLOAT_T						(5000/CHARGE_BASE_T)//恒压时间

enum{
	CB_STANDBY,
	CB_MANUAL,
	CB_AUTO,
	CB_FAULT,
};

enum{
	CHARGE_MODE_NONE,
	CHARGE_MODE_AUTO,
	CHARGE_MODE_MANUAL,
	CHARGE_MODE_STANDBY,
};

class CbMode :public StateMachine
{
public:
	void SetChargeEn(bool a)
	{ chargeEnable = a; }
	
private:
		// 摘要: 
    //     模块是否故障?
		int 	chargeCmd;

		bool	chargeEnable;

		bool	condition;
		// 摘要: 
    //     模块是否故障?
		bool 	Instation;
		// 摘要: 
    //     模块是否故障?
		bool 	Charging;
		// 摘要: 
    //     模块是否故障?
		bool	floatCharge;
		// 摘要: 
    //     模块是否故障?
		bool	pwmOnFail;
		// 摘要: 
    //     模块是否故障?
		bool	pwmOffFail;
		// 摘要: 
    //     模块是否故障?
		bool	chargeComplet;
		// 摘要: 
    //     模块是否故障?
		int canIndex;
public:

	CbMode(void)
	{ ; }
	void Run(void);
	void Init(int index, int mode, int outputMode)
	{
		this->canIndex = index;
		this->modeSet = mode;
		this->outputMode = outputMode;
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

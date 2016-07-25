#include "appModule.h"
#include "stm32f4xx.h"
#include <rtthread.h>


void CbMode::ModuleManage(void)
{
	switch (State)
	{
		//待机态
		case CB_STATE_IDLE:
			if (isAbnormal == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (modeSet == CHARGE_MODE_AUTO)
			{
				State = CB_STATE_AUTO;
				OutputMode = CB_OUT_AUTO;
			}
			else if (modeSet == CHARGE_MODE_MANUAL)
			{
				State = CB_STATE_MANUAL;
				OutputMode = CB_OUT_MANUAL;
			}
			else
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			break;
		//手动充电
		case CB_STATE_MANUAL:
			if (isAbnormal == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (SysMode.SystemState != SYS_STATE_STANDBY)
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			else if (modeSet == CHARGE_MODE_AUTO)
			{
				State = CB_STATE_AUTO;
				OutputMode = CB_OUT_AUTO;
			}
			else if (modeSet == CHARGE_MODE_STANDBY)
			{
				State = CB_STATE_MANUAL;
				OutputMode = CB_OUT_STANDY;
			}
			else
			{
				State = CB_STATE_MANUAL;
				OutputMode = CB_OUT_MANUAL;
			}
			break;
		//自动充电
		case CB_STATE_AUTO:
			if (isAbnormal == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (SysMode.SystemState != SYS_STATE_STANDBY)
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			else if (modeSet == CHARGE_MODE_MANUAL)
			{
				State = CB_STATE_MANUAL;
				OutputMode = CB_OUT_MANUAL;
			}
			else
			{
				State = CB_STATE_AUTO;
				OutputMode = CB_OUT_AUTO;
			}
			break;
		//故障态
		case CB_STATE_FAULT:
			if (isAbnormal == false)
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			else
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			break;
		default:
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			break;
	}
	modeNow = State;
}

void CbMode::CB_Idle_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		//can.SendCan(canIndex);
	}
	//startDelay = CHARGE_START_T;
	//floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Manual_Cal(void)
{
	if (Charging != true)
	{
		chargeCmd = 1;
		//can.SendCan(canIndex);
		return ;
	}
	chargeCmd = 1;
	//startDelay = CHARGE_START_T;
	//floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Standby_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		//can.SendCan(canIndex);
	}
	chargeCmd = 0;
	//startDelay = CHARGE_START_T;
	//floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Auto_Cal(void)
{
	if (Instation)
	{
		if (!Charging
		 && !chargeComplet)
		{
			//delay
//			if (startDelay > 0)
//			{
//				startDelay--;
//			}
//			else
//			{
//				chargeCmd = 1;
//				//can.SendCan(canIndex);
//			}
		}
		else if (floatCharge)
		{
			//delay
//			if (floatDelay > 0)
//			{
//				floatDelay--;
//			}
//			else
//			{
//				chargeCmd = 0;
//				can.SendCan(canIndex);
//			}
		}
	}
	else
	{
		if (Charging == true)
		{
			chargeCmd = 0;
			//can.SendCan(canIndex);
		}
		chargeCmd = 0;
//		startDelay = CHARGE_START_T;
//		floatDelay = CHARGE_FLOAT_T;
	}
}

void CbMode::CB_Fault_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		//can.SendCan(canIndex);
	}
//	startDelay = CHARGE_START_T;
//	floatDelay = CHARGE_FLOAT_T;
}

void CbMode::OutputManage(void)
{
	switch (this->OutputMode)
	{
		//待机态
		case CB_OUT_IDLE:
			CB_Idle_Cal();
			break;
		//手动充电
		case CB_OUT_MANUAL:
			CB_Manual_Cal();
			break;
		//手动待机
		case CB_OUT_STANDY:
			CB_Standby_Cal();
			break;
		//自动充电
		case CB_OUT_AUTO:
			CB_Auto_Cal();
			break;
		//故障态
		case CB_OUT_FAULT:
			CB_Fault_Cal();
			break;
		default:
			break;
	}
}

void CbMode::CbCtrl(void)
{
	ModuleManage();
	OutputManage();
}



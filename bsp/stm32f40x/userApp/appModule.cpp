#include "appModule.h"
#include "stm32f4xx.h"
#include <rtthread.h>
#include "ScManagerExtern.h"


void CbMode::ModuleManage(void)
{
	switch (state)
	{
		//待机态
		case CB_STATE_IDLE:
			if (Abnormal == true)
			{
				state = CB_STATE_FAULT;
				outputMode = CB_OUT_FAULT;
			}
			else if (condition == false || chargeEnable == false)
			{
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			}
			else if (modeSet == CHARGE_MODE_AUTO)
			{
				state = CB_STATE_AUTO;
				outputMode = CB_OUT_AUTO;
			}
			else if (modeSet == CHARGE_MODE_MANUAL)
			{
				state = CB_STATE_MANUAL;
				outputMode = CB_OUT_MANUAL;
			}
			else
			{
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			}
			break;
		//手动充电
		case CB_STATE_MANUAL:
			if (Abnormal == true)
			{
				state = CB_STATE_FAULT;
				outputMode = CB_OUT_FAULT;
			}
			else if (condition == false || chargeEnable == false)
			{
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			}
			else if (modeSet == CHARGE_MODE_AUTO)
			{
				state = CB_STATE_AUTO;
				outputMode = CB_OUT_AUTO;
			}
			else if (modeSet == CHARGE_MODE_STANDBY)
			{
				state = CB_STATE_MANUAL;
				outputMode = CB_OUT_STANDY;
			}
			else
			{
				state = CB_STATE_MANUAL;
				outputMode = CB_OUT_MANUAL;
			}
			break;
		//自动充电
		case CB_STATE_AUTO:
			if (Abnormal == true)
			{
				state = CB_STATE_FAULT;
				outputMode = CB_OUT_FAULT;
			}
			else if (condition == false || chargeEnable == false)
			{
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			}
			else if (modeSet == CHARGE_MODE_MANUAL)
			{
				state = CB_STATE_MANUAL;
				outputMode = CB_OUT_MANUAL;
			}
			else
			{
				state = CB_STATE_AUTO;
				outputMode = CB_OUT_AUTO;
			}
			break;
		//故障态
		case CB_STATE_FAULT:
			if (Abnormal == false)
			{
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			}
			else
			{
				state = CB_STATE_FAULT;
				outputMode = CB_OUT_FAULT;
			}
			break;
		default:
				state = CB_STATE_IDLE;
				outputMode = CB_OUT_IDLE;
			break;
	}
}

void CbMode::CB_Idle_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		SendCan(canIndex);
	}
	startDelay->Stop();
	floatDelay->Stop();
}

void CbMode::CB_Manual_Cal(void)
{
	if (Charging != true)
	{
		*chargeCmd = 1;
		SendCan(canIndex);
		return ;
	}
	*chargeCmd = 1;
	startDelay->Stop();
	floatDelay->Stop();
}

void CbMode::CB_Standby_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		SendCan(canIndex);
	}
	chargeCmd = 0;
	startDelay->Stop();
	floatDelay->Stop();
}

void CbMode::CB_Auto_Cal(void)
{
	if (Instation)
	{
		if (!Charging
		 && !chargeComplet)
		{
			//delay
			startDelay->Start();
			if (startDelay->GetResult())
			{
				*chargeCmd = 1;
				SendCan(canIndex);
			}
		}
		else if (floatCharge)
		{
			//delay
			floatDelay->Start();
			if (floatDelay->GetResult())
			{
				chargeCmd = 0;
				chargeComplet = true;
				SendCan(canIndex);
			}
		}
	}
	else
	{
		if (Charging == true)
		{
			chargeCmd = 0;
			SendCan(canIndex);
		}
		chargeCmd = 0;
		chargeComplet = false;
		startDelay->Stop();
		floatDelay->Stop();
	}
}

void CbMode::CB_Fault_Cal(void)
{
	if (Charging == true)
	{
		chargeCmd = 0;
		SendCan(canIndex);
	}
	startDelay->Stop();
	floatDelay->Stop();
}

void CbMode::OutputManage(void)
{
	switch (this->outputMode)
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

void CbMode::Run(void)
{
	ModuleManage();
	OutputManage();
}


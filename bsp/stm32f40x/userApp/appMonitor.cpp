#include "appMonitor.h"
#include "stm32f4xx.h"
#include <rtthread.h>
#include "logicApp.h"
#include "canApp.h"

System_Mode::System_Mode(void)
{
	state = SYS_STATE_STOP;
	outputMode = SYS_OUT_STOP;
}

void System_Mode::ChargeModeManage(void)
{
	switch (state)
	{
		case SYS_STATE_STOP :
			//休眠
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//器件测试
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//严重故障
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//起停按钮 按下
			else if (*cabinet == true)
			{
				state = SYS_STATE_PRECHARGE;
				outputMode = SYS_OUT_PRECHARGE;
			}
			else
			{
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			break;
			
		case SYS_STATE_PRECHARGE :
			//休眠
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//器件测试
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//严重故障
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//起停按钮 按下
			else if (*cabinet == false)
			{
				PreChargeStep1 = false;
				PreChargeStep2 = false;
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			//预充电完成
			else if (this->PreFinsh)
			{
				state = SYS_STATE_STANDBY;
				outputMode = SYS_OUT_STANDBY;
			}
			//预充电ing
			else
			{
				state = SYS_STATE_PRECHARGE;
				outputMode = SYS_OUT_PRECHARGE;
			}
			break;
			//待机态
		case SYS_STATE_STANDBY :
			//休眠
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//器件测试
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//严重故障
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//起停按钮 按下
			else if (*cabinet == false)
			{
				PreChargeStep1 = false;
				PreChargeStep2 = false;
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			else
			{
				state = SYS_STATE_STANDBY;
				outputMode = SYS_OUT_STANDBY;
			}
			break;
			//故障态
		case SYS_STATE_FAULT :
			//休眠
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//器件测试
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//故障消失
			else if (Abnormal == false)
			{
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			else
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			break;
			//器件测试
		case SYS_STATE_TEST:
			//休眠
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
			}
			//退出器件测试
			else if (modeSet == CHARGE)
			{
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			else
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			break;
			//休眠态
		case SYS_STATE_SLEEP:
			//进入休眠
			if (inSleep == true)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//退出休眠
			else if (inSleep == false)
			{
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			else
			{
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			break;
			//其他
		default:
			state = SYS_STATE_STOP;
			outputMode = SYS_OUT_STOP;
			break;
			
	}
}

void System_Mode::StopCal(void)
{
	if (scData->hmi.mbStatus.dcdc1_step == 0 && scData->hmi.mbStatus.dcdc2_step == 0
	 && scData->hmi.mbStatus.dcdc3_step == 0 && scData->hmi.mbStatus.dcdc4_step == 0
	 && scData->hmi.mbStatus.dcdc5_step == 0)
	 {
		scData->output.io.out_32.mainCon1 = false;
		scData->output.io.out_32.mainCon2 = false;
		scData->output.io.out_32.preCon = false;
		scData->output.io.out_32.outCon1 = false;
		scData->output.io.out_32.outCon2 = false;
		scData->output.io.out_32.outCon3 = false;
		scData->output.io.out_32.outCon4 = false;
		scData->output.io.out_32.outCon5 = false;
	 }
}

void System_Mode::PreChargeCal(void)
{
	scData->output.io.out_32.mainCon1 = false;
	scData->output.io.out_32.mainCon2 = false;
	scData->output.io.out_32.preCon = true;
	scData->output.io.out_32.outCon1 = false;
	scData->output.io.out_32.outCon2 = false;
	scData->output.io.out_32.outCon3 = false;
	scData->output.io.out_32.outCon4 = false;
	scData->output.io.out_32.outCon5 = false;
	
	//预充电第一阶段开始
	PreChargeStep1 = true;
	
	preStep1Relay->Start();
	if (preStep1Relay->GetResult())
	{
		PreChargeStep2 = true;
		if (scData->status.status_bit.busVoltOK)
		{
			scData->output.io.out_32.mainCon1 = true;
			preStep2Relay->Start();
			if (preStep2Relay->GetResult())
			{
				scData->output.io.out_32.mainCon2 = true;
				scData->output.io.out_32.preCon = false;
				
				PreFinsh = true;
				preStep1Relay->Stop();
				preStep2Relay->Stop();
			}
		}
	}
}

void System_Mode::StandbyCal(void)
{
	scData->output.io.out_32.mainCon1 = true;
	scData->output.io.out_32.mainCon2 = true;
	scData->output.io.out_32.preCon = false;
	
	preStep1Relay->Stop();
	preStep2Relay->Stop();
}

void System_Mode::FaultCal(void)
{
	if (scData->hmi.mbStatus.dcdc1_step == 0 && scData->hmi.mbStatus.dcdc2_step == 0
	 && scData->hmi.mbStatus.dcdc3_step == 0 && scData->hmi.mbStatus.dcdc4_step == 0
	 && scData->hmi.mbStatus.dcdc5_step == 0)
	 {
		scData->output.io.out_32.mainCon1 = false;
		scData->output.io.out_32.mainCon2 = false;
		scData->output.io.out_32.preCon = false;
		scData->output.io.out_32.outCon1 = false;
		scData->output.io.out_32.outCon2 = false;
		scData->output.io.out_32.outCon3 = false;
		scData->output.io.out_32.outCon4 = false;
		scData->output.io.out_32.outCon5 = false;
	 }
	 
	preStep1Relay->Stop();
	preStep2Relay->Stop();
}

void System_Mode::DevTestCal(void)
{
	uint16_t DevTestCmd;
	DevTestCmd = scData->hmi.CtrCmd.DevTestCmd;
	
	if (DevTestCmd & (0x0001 << 0))
	{
		scData->output.io.out_32.preCon = true;
	}
	else
	{
		scData->output.io.out_32.preCon = false;
	}
	if (DevTestCmd & (0x0001 << 1))
	{
		scData->output.io.out_32.mainCon1 = true;
	}
	else
	{
		scData->output.io.out_32.mainCon1 = false;
	}
	if (DevTestCmd & (0x0001 << 2))
	{
		scData->output.io.out_32.mainCon2 = true;
	}
	else
	{
		scData->output.io.out_32.mainCon2 = false;
	}
	if (DevTestCmd & (0x0001 << 3))
	{
		scData->output.io.out_32.outCon1 = true;
	}
	else
	{
		scData->output.io.out_32.outCon1 = false;
	}
	if (DevTestCmd & (0x0001 << 4))
	{
		scData->output.io.out_32.outCon2 = true;
	}
	else
	{
		scData->output.io.out_32.outCon2 = false;
	}
	if (DevTestCmd & (0x0001 << 5))
	{
		scData->output.io.out_32.outCon3 = true;
	}
	else
	{
		scData->output.io.out_32.outCon3 = false;
	}
	if (DevTestCmd & (0x0001 << 6))
	{
		scData->output.io.out_32.outCon4 = true;
	}
	else
	{
		scData->output.io.out_32.outCon4 = false;
	}
	if (DevTestCmd & (0x0001 << 7))
	{
		scData->output.io.out_32.outCon5 = true;
	}
	else
	{
		scData->output.io.out_32.outCon5 = false;
	}
	preStep1Relay->Stop();
	preStep2Relay->Stop();
}

void System_Mode::SleepCal(void)
{
	__NOP();
	preStep1Relay->Stop();
	preStep2Relay->Stop();
}

void System_Mode::System_Output(void)
{
	switch (outputMode)
	{
		//停机态
		case SYS_OUT_STOP:
			StopCal();
			break;
		//预充电
		case SYS_OUT_PRECHARGE:
			PreChargeCal();
			break;
		//待机态
		case SYS_OUT_STANDBY:
			StandbyCal();
			break;
		//故障态
		case SYS_OUT_FAULT:
			FaultCal();
			break;
		//器件测试
		case SYS_OUT_TEST:
			DevTestCal();
			break;
		//休眠
		case SYS_OUT_SLEEP:
			SleepCal();
			break;
		default:
			break;
	}
}


void System_Mode::Run(void)
{
	ChargeModeManage();
	System_Output();
}

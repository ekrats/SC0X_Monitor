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
			//����
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//��������
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//���ع���
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//��ͣ��ť ����
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
			//����
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//��������
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//���ع���
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//��ͣ��ť ����
			else if (*cabinet == false)
			{
				PreChargeStep1 = false;
				PreChargeStep2 = false;
				state = SYS_STATE_STOP;
				outputMode = SYS_OUT_STOP;
			}
			//Ԥ������
			else if (this->PreFinsh)
			{
				state = SYS_STATE_STANDBY;
				outputMode = SYS_OUT_STANDBY;
			}
			//Ԥ���ing
			else
			{
				state = SYS_STATE_PRECHARGE;
				outputMode = SYS_OUT_PRECHARGE;
			}
			break;
			//����̬
		case SYS_STATE_STANDBY :
			//����
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//��������
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//���ع���
			else if (Abnormal == true)
			{
				state = SYS_STATE_FAULT;
				outputMode = SYS_OUT_FAULT;
			}
			//��ͣ��ť ����
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
			//����̬
		case SYS_STATE_FAULT :
			//����
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//��������
			else if (modeSet == DEVICE_TEST)
			{
				state = SYS_STATE_TEST;
				outputMode = SYS_OUT_TEST;
			}
			//������ʧ
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
			//��������
		case SYS_STATE_TEST:
			//����
			if (modeSet == SLEEP)
			{
				state = SYS_STATE_SLEEP;
			}
			//�˳���������
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
			//����̬
		case SYS_STATE_SLEEP:
			//��������
			if (inSleep == true)
			{
				state = SYS_STATE_SLEEP;
				outputMode = SYS_OUT_SLEEP;
			}
			//�˳�����
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
			//����
		default:
			state = SYS_STATE_STOP;
			outputMode = SYS_OUT_STOP;
			break;
			
	}
}
/*
void System_Mode::StopCal(void)
{
	if (MB_LGA.cb1_SYS.input.Charging == false && MB_LGA.cb2_SYS.input.Charging == false
	 && MB_LGA.cb3_SYS.input.Charging == false && MB_LGA.cb4_SYS.input.Charging == false
	 && MB_LGA.cb5_SYS.input.Charging == false)
	 {
		MB_LGA.MB_IO_OUT.mainCon1N = false;
		MB_LGA.MB_IO_OUT.mainCon2N = false;
		MB_LGA.MB_IO_OUT.preConN = false;
		MB_LGA.MB_IO_OUT.outCon1N = false;
		MB_LGA.MB_IO_OUT.outCon2N = false;
		MB_LGA.MB_IO_OUT.outCon3N = false;
		MB_LGA.MB_IO_OUT.outCon4N = false;
		MB_LGA.MB_IO_OUT.outCon5N = false;
	 }
	 
	PreDelayCnt = PRE_CHARGE_DELAY1;
	PreDelay2Cnt = PRE_CHARGE_DELAY2;
}

void System_Mode::PreChargeCal(void)
{
	MB_LGA.MB_IO_OUT.mainCon1N = false;
	MB_LGA.MB_IO_OUT.mainCon2N = false;
	MB_LGA.MB_IO_OUT.preConN = true;
	MB_LGA.MB_IO_OUT.outCon1N = false;
	MB_LGA.MB_IO_OUT.outCon2N = false;
	MB_LGA.MB_IO_OUT.outCon3N = false;
	MB_LGA.MB_IO_OUT.outCon4N = false;
	MB_LGA.MB_IO_OUT.outCon5N = false;
	
	//Ԥ����һ�׶ο�ʼ
	this->PreChargeStep1 = true;
	
	if(PreDelayCnt > 0)
	{
		PreDelayCnt --;
	}
	else
	{
		this->PreChargeStep2 = true;
		if (MB_LGA.MB_SYS_INFO.busVoltOK)
		{
			MB_LGA.MB_IO_OUT.mainCon1N = true;
			if (PreDelay2Cnt > 0)
			{
				PreDelay2Cnt --;
			}
			else
			{
				MB_LGA.MB_IO_OUT.mainCon2N = true;
				MB_LGA.MB_IO_OUT.preConN = false;
				
				this->PreFinsh = true;
				PreDelayCnt = PRE_CHARGE_DELAY1;
				PreDelay2Cnt = PRE_CHARGE_DELAY2;
			}
		}
	}
}

void System_Mode::StandbyCal(void)
{
	MB_LGA.MB_IO_OUT.mainCon1N = true;
	MB_LGA.MB_IO_OUT.mainCon2N = true;
	MB_LGA.MB_IO_OUT.preConN = false;
	
	PreDelayCnt = PRE_CHARGE_DELAY1;
	PreDelay2Cnt = PRE_CHARGE_DELAY2;
}

void System_Mode::FaultCal(void)
{
	if (MB_LGA.cb1_SYS.input.Charging == false && MB_LGA.cb2_SYS.input.Charging == false
	 && MB_LGA.cb3_SYS.input.Charging == false && MB_LGA.cb4_SYS.input.Charging == false
	 && MB_LGA.cb5_SYS.input.Charging == false)
	 {
		MB_LGA.MB_IO_OUT.mainCon1N = false;
		MB_LGA.MB_IO_OUT.mainCon2N = false;
		MB_LGA.MB_IO_OUT.preConN = false;
		MB_LGA.MB_IO_OUT.outCon1N = false;
		MB_LGA.MB_IO_OUT.outCon2N = false;
		MB_LGA.MB_IO_OUT.outCon3N = false;
		MB_LGA.MB_IO_OUT.outCon4N = false;
		MB_LGA.MB_IO_OUT.outCon5N = false;
	 }
	 
	PreDelayCnt = PRE_CHARGE_DELAY1;
	PreDelay2Cnt = PRE_CHARGE_DELAY2;
}

void System_Mode::DevTestCal(void)
{
	uint16_t DevTestCmd;
	DevTestCmd = MB_LGA.CtrCmd.DevTestCmd;
	
	if (DevTestCmd & (0x0001 << 0))
	{
		MB_LGA.MB_IO_OUT.preConN = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.preConN = false;
	}
	if (DevTestCmd & (0x0001 << 1))
	{
		MB_LGA.MB_IO_OUT.mainCon1N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.mainCon1N = false;
	}
	if (DevTestCmd & (0x0001 << 2))
	{
		MB_LGA.MB_IO_OUT.mainCon2N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.mainCon2N = false;
	}
	if (DevTestCmd & (0x0001 << 3))
	{
		MB_LGA.MB_IO_OUT.outCon1N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.outCon1N = false;
	}
	if (DevTestCmd & (0x0001 << 4))
	{
		MB_LGA.MB_IO_OUT.outCon2N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.outCon2N = false;
	}
	if (DevTestCmd & (0x0001 << 5))
	{
		MB_LGA.MB_IO_OUT.outCon3N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.outCon3N = false;
	}
	if (DevTestCmd & (0x0001 << 6))
	{
		MB_LGA.MB_IO_OUT.outCon4N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.outCon4N = false;
	}
	if (DevTestCmd & (0x0001 << 7))
	{
		MB_LGA.MB_IO_OUT.outCon5N = true;
	}
	else
	{
		MB_LGA.MB_IO_OUT.outCon5N = false;
	}
	PreDelayCnt = PRE_CHARGE_DELAY1;
	PreDelay2Cnt = PRE_CHARGE_DELAY2;
}

void System_Mode::SleepCal(void)
{
	__NOP();
	PreDelayCnt = PRE_CHARGE_DELAY1;
	PreDelay2Cnt = PRE_CHARGE_DELAY2;
}

void System_Mode::System_Output(void)
{
	switch (this->SystemOutput)
	{
		//ͣ��̬
		case SYS_OUT_STOP:
			StopCal();
			break;
		//Ԥ���
		case SYS_OUT_PRECHARGE:
			PreChargeCal();
			break;
		//����̬
		case SYS_OUT_STANDBY:
			StandbyCal();
			break;
		//����̬
		case SYS_OUT_FAULT:
			FaultCal();
			break;
		//��������
		case SYS_OUT_TEST:
			DevTestCal();
			break;
		//����
		case SYS_OUT_SLEEP:
			SleepCal();
			break;
		default:
			break;
	}
}
*/

void System_Mode::Run(void)
{
	
}

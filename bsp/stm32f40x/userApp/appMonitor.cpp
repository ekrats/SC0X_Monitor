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
	
	//Ԥ����һ�׶ο�ʼ
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


void System_Mode::Run(void)
{
	ChargeModeManage();
	System_Output();
}

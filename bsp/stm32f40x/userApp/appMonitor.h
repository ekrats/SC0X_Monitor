#ifndef _APP_MONITOR_H_
#define _APP_MONITOR_H_

#include "stm32f4xx.h"
#include <rtthread.h>
#include "StateMachine.h"
#include "DataStruct.h"
#include "Relay.h"


class System_Mode :
	public StateMachine
{
public:
	void SetDevTestCmd(int cmd)
	{ devTestCmd = cmd; }
	void SetSleepMode(bool sleep)
	{ inSleep = sleep;}
private:
		int 	*cabinet;
		int 	devTestCmd;
		bool	inSleep;
		//Ԥ���Ӵ����պ�
		bool	PreChargeStep1;
		//Ԥ���ʱ��֮��
		bool  	PreChargeStep2;
		//Ԥ������
		bool	PreFinsh;
		
public:
	System_Mode(void);
	ScData * scData;
	Relay * preStep1Relay;
	Relay * preStep2Relay;
	void Init(int * button)
	{
		cabinet = button;
	}
	void Run(void);
	void StopCal(void);
	void PreChargeCal(void);
	void StandbyCal(void);
	void FaultCal(void);
	void DevTestCal(void);
	void SleepCal(void);
	void System_Output(void);
	void ChargeModeManage(void);
};

#endif

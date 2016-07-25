#include "appModule.h"

#include "stm32f4xx.h"
#include <rtthread.h>
#include "logicApp.h"
#include "canApp.h"
#include "appMonitor.h"

CbMode::CbMode(MODULE_SYS_STYP *sys, Charge_Cmd_STYP *cmd, u8 Index)
{
	canIndex = Index;
	pcb_sys = sys;
	pcb_cmd = cmd;
	
	State = CB_STATE_IDLE;
	OutputMode = CB_OUT_IDLE;
}

void CbMode::ModuleManage(void)
{
	switch (State)
	{
		//����̬
		case CB_STATE_IDLE:
			if (pcb_sys->input.Fault == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (pcb_sys->input.Charge_Mode_Set == CHARGE_MODE_AUTO)
			{
				State = CB_STATE_AUTO;
				OutputMode = CB_OUT_AUTO;
			}
			else if (pcb_sys->input.Charge_Mode_Set == CHARGE_MODE_MANUAL)
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
		//�ֶ����
		case CB_STATE_MANUAL:
			if (MB_LGA.cb1_SYS.input.Fault == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (SysMode.SystemState != SYS_STATE_STANDBY)
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			else if (pcb_sys->input.Charge_Mode_Set == CHARGE_MODE_AUTO)
			{
				State = CB_STATE_AUTO;
				OutputMode = CB_OUT_AUTO;
			}
			else if (pcb_sys->input.Charge_Mode_Set == CHARGE_MODE_STANDBY)
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
		//�Զ����
		case CB_STATE_AUTO:
			if (MB_LGA.cb1_SYS.input.Fault == true)
			{
				State = CB_STATE_FAULT;
				OutputMode = CB_OUT_FAULT;
			}
			else if (SysMode.SystemState != SYS_STATE_STANDBY)
			{
				State = CB_STATE_IDLE;
				OutputMode = CB_OUT_IDLE;
			}
			else if (pcb_sys->input.Charge_Mode_Set == CHARGE_MODE_MANUAL)
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
		//����̬
		case CB_STATE_FAULT:
			if (MB_LGA.cb1_SYS.input.Fault == false)
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
	pcb_sys->output.Charge_Mode_Now = State;
}

void CbMode::CB_Idle_Cal(void)
{
	if (pcb_sys->input.Charging == true)
	{
		pcb_cmd->CMD = 0;
		can.SendCan(canIndex);
	}
	startDelay = CHARGE_START_T;
	floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Manual_Cal(void)
{
	if (pcb_sys->input.Charging != true)
	{
		pcb_cmd->CMD = 1;
		can.SendCan(canIndex);
		return ;
	}
	pcb_cmd->CMD = 1;
	startDelay = CHARGE_START_T;
	floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Standby_Cal(void)
{
	if (pcb_sys->input.Charging == true)
	{
		pcb_cmd->CMD = 0;
		can.SendCan(canIndex);
	}
	pcb_cmd->CMD = 0;
	startDelay = CHARGE_START_T;
	floatDelay = CHARGE_FLOAT_T;
}

void CbMode::CB_Auto_Cal(void)
{
	if (pcb_sys->input.Instation)
	{
		if (!pcb_sys->input.Charging
		 && !pcb_sys->output.chargeComplet)
		{
			//delay
			if (startDelay > 0)
			{
				startDelay--;
			}
			else
			{
				pcb_cmd->CMD = 1;
				can.SendCan(canIndex);
			}
		}
		else if (pcb_sys->input.floatChargeN)
		{
			//delay
			if (floatDelay > 0)
			{
				floatDelay--;
			}
			else
			{
				pcb_cmd->CMD = 0;
				can.SendCan(canIndex);
			}
		}
	}
	else
	{
		if (pcb_sys->input.Charging == true)
		{
			pcb_cmd->CMD = 0;
			can.SendCan(canIndex);
		}
		pcb_cmd->CMD = 0;
		startDelay = CHARGE_START_T;
		floatDelay = CHARGE_FLOAT_T;
	}
}

void CbMode::CB_Fault_Cal(void)
{
	if (pcb_sys->input.Charging == true)
	{
		pcb_cmd->CMD = 0;
		can.SendCan(canIndex);
	}
	startDelay = CHARGE_START_T;
	floatDelay = CHARGE_FLOAT_T;
}

void CbMode::OutputManage(void)
{
	switch (this->OutputMode)
	{
		//����̬
		case CB_OUT_IDLE:
			CB_Idle_Cal();
			break;
		//�ֶ����
		case CB_OUT_MANUAL:
			CB_Manual_Cal();
			break;
		//�ֶ�����
		case CB_OUT_STANDY:
			CB_Standby_Cal();
			break;
		//�Զ����
		case CB_OUT_AUTO:
			CB_Auto_Cal();
			break;
		//����̬
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



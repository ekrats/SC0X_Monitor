#include "ScManager.h"
#include "ScManagerExtern.h"
#include "io.h"
#include "ad.h"
#include "fsmc.h"


ScManager sc;
CanApp can;
System_Mode SysMode;
CbMode	Cb1Mode;
CbMode	Cb2Mode;
CbMode	Cb3Mode;
CbMode	Cb4Mode;
CbMode	Cb5Mode;

void ScManager::RelayRun(void)
{
    relays.Refresh();
	ContactRelayRun();
}

void ScManager::Init(void)
{
	sc.sysMode = &SysMode;
	sc.cb1Mode = &Cb1Mode;
	sc.cb2Mode = &Cb2Mode;
	sc.cb3Mode = &Cb3Mode;
	sc.cb4Mode = &Cb4Mode;
	sc.cb5Mode = &Cb5Mode;
	
	cbModelist.Add(&Cb1Mode);
	cbModelist.Add(&Cb2Mode);
	cbModelist.Add(&Cb3Mode);
	cbModelist.Add(&Cb4Mode);
	cbModelist.Add(&Cb5Mode);
}

int * buffer = NULL;
void ad_init(void)
{
	buffer = get_ad_data_buffer();
	
	sc.input1Current.Init(&buffer[i_in1_index], 4500, 95);
	sc.input2Current.Init(&buffer[i_in2_index], 4500, 95);
	sc.inputAc1Voltage.Init(&buffer[u_ac1_index], 13330, 95);
	sc.inputAc2Voltage.Init(&buffer[u_ac2_index], 13330, 95);
	sc.inputBusVoltage.Init(&buffer[u_bus_index], 13330, 95);
	sc.module1Temp.Init(&buffer[temp_module1_index], 0, 5);
	sc.module2Temp.Init(&buffer[temp_module2_index], 0, 5);
	sc.fanInTemp.Init(&buffer[temp_in_index], 0, 5);
	sc.fanOutTemp.Init(&buffer[temp_out_index], 0, 5);
	sc.cap1Temp.Init(&buffer[temp_cap1_index], 0, 5);
	sc.cap2Temp.Init(&buffer[temp_cap2_index], 0, 5);
}

int *io_buffer = NULL;
int *io_out_buffer = NULL;
void io_init(void)
{
	io_buffer = get_io_input_address();
	io_out_buffer = sc.shareData.output.io.out;
	
	sc.cabinet.Init(&io_buffer[cabinetN]);
	sc.inFuse1.Init(&io_buffer[inFuse1N]);
	sc.inFuse2.Init(&io_buffer[inFuse2N]);
	sc.outFuse1.Init(&io_buffer[outFuse1N]);
	sc.outFuse2.Init(&io_buffer[outFuse2N]);
	sc.outFuse3.Init(&io_buffer[outFuse3N]);
	sc.outFuse4.Init(&io_buffer[outFuse4N]);
	sc.outFuse5.Init(&io_buffer[outFuse5N]);
	
	sc.mainCon1.Init(&io_buffer[mainCon1N], &io_out_buffer[mainCon1], 10);
	sc.mainCon2.Init(&io_buffer[mainCon2N], &io_out_buffer[mainCon2], 10);
	sc.preCon.Init(&io_buffer[preConN], &io_out_buffer[preCon], 10);
	sc.outCon1.Init(&io_buffer[outCon1N], &io_out_buffer[outCon1], 10);
	sc.outCon2.Init(&io_buffer[outCon2N], &io_out_buffer[outCon2], 10);
	sc.outCon3.Init(&io_buffer[outCon3N], &io_out_buffer[outCon3], 10);
	sc.outCon4.Init(&io_buffer[outCon4N], &io_out_buffer[outCon4], 10);
	sc.outCon5.Init(&io_buffer[outCon5N], &io_out_buffer[outCon5], 10);
}

void sc_init(void)
{
	sc.SetCan(&can);
	can.scData = &sc.shareData;
	ad_init();
	io_init();
}

void ScManager::MonitorStatusUpdata(void)
{
	HMI_Status_STYP *p = &sc.shareData.hmi.mbStatus;
	
	
	
	p->sys_mode = sysMode->GetMode();
	p->dcdc1_mode = cb1Mode->GetMode();
	p->dcdc2_mode = cb2Mode->GetMode();
	p->dcdc3_mode = cb3Mode->GetMode();
	p->dcdc4_mode = cb4Mode->GetMode();
	p->dcdc5_mode = cb5Mode->GetMode();
	
	p->dcdc1_step = sc.shareData.cb1Status.flags.chargeOnN + sc.shareData.cb1Status.flags.floatChargeN;
	p->dcdc2_step = sc.shareData.cb2Status.flags.chargeOnN + sc.shareData.cb2Status.flags.floatChargeN;
	p->dcdc3_step = sc.shareData.cb3Status.flags.chargeOnN + sc.shareData.cb3Status.flags.floatChargeN;
	p->dcdc4_step = sc.shareData.cb4Status.flags.chargeOnN + sc.shareData.cb4Status.flags.floatChargeN;
	p->dcdc5_step = sc.shareData.cb5Status.flags.chargeOnN + sc.shareData.cb5Status.flags.floatChargeN;
	
	p->In_Flags.cabinetEnN = sc.shareData.input.io.in_32.cabinet;
	p->In_Flags.inFuse1N = sc.shareData.input.io.in_32.inFuse1;
	p->In_Flags.inFuse2N = sc.shareData.input.io.in_32.inFuse2;
	p->In_Flags.mainCon1N = sc.shareData.input.io.in_32.mainCon1;
	p->In_Flags.mainCon2N = sc.shareData.input.io.in_32.mainCon2;
	p->In_Flags.outCon1N = sc.shareData.input.io.in_32.outCon1;
	p->In_Flags.outCon2N = sc.shareData.input.io.in_32.outCon2;
	p->In_Flags.outCon3N = sc.shareData.input.io.in_32.outCon3;
	p->In_Flags.outCon4N = sc.shareData.input.io.in_32.outCon4;
	p->In_Flags.outCon5N = sc.shareData.input.io.in_32.outCon5;
	p->In_Flags.outFuse1N = sc.shareData.input.io.in_32.outFuse1;
	p->In_Flags.outFuse2N = sc.shareData.input.io.in_32.outFuse2;
	p->In_Flags.outFuse3N = sc.shareData.input.io.in_32.outFuse3;
	p->In_Flags.outFuse4N = sc.shareData.input.io.in_32.outFuse4;
	p->In_Flags.outFuse5N = sc.shareData.input.io.in_32.outFuse5;
	
	
}

void ScManager::UpdateCbState(void)
{
	cbModelist.Begin();
	CbMode * tmp = NULL;
	while ((tmp = cbModelist.Next()) != NULL)
    {
        tmp->Run();
    }
}

void ScManager::RefreshAdData(void)
{
    sensorList.Begin();
    ITransducer * tmp = NULL;
    while ((tmp = sensorList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshPt100Data(void)
{
	pt100List.Begin();
	PT100 * tmp = NULL;
	while ((tmp = pt100List.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshIoData(void)
{
	ioList.Begin();
	ITransducer * tmp = NULL;
	while ((tmp = ioList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshConData(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::ContactRelayRun(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Refresh();
    }
}

void ScManager::ContactCheck(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Check();
    }
}

void ScManager::SetCan(CanApp* pCan)
{
	this->can = pCan;
}

void ScManager::Run(void)
{
	sc.sysMode->Run();
	sc.UpdateCbState();
}

void data_deal(void)
{
	sc.RefreshAdData();
	sc.RefreshIoData();
	sc.RefreshConData();
	sc.RefreshPt100Data();
	sc.ContactCheck();
}

void io_output(void)
{
	io_write_output(sc.shareData.output.io.out);
}

void UpdateData(void)
{
	sc.shareData.input.ad.i_in1 = sc.input1Current.GetAverageRealValue();
	sc.shareData.input.ad.i_in2 = sc.input2Current.GetAverageRealValue();
	sc.shareData.input.ad.u_ac1 = sc.inputAc1Voltage.GetAverageRealValue();
	sc.shareData.input.ad.u_ac2 = sc.inputAc2Voltage.GetAverageRealValue();
	sc.shareData.input.ad.u_bus = sc.inputBusVoltage.GetAverageRealValue();
	sc.shareData.input.ad.temp_cap1 = sc.cap1Temp.GetRealValue();
	sc.shareData.input.ad.temp_cap2 = sc.cap2Temp.GetRealValue();
	sc.shareData.input.ad.temp_in = sc.fanInTemp.GetRealValue();
	sc.shareData.input.ad.temp_out = sc.fanOutTemp.GetRealValue();
	sc.shareData.input.ad.temp_module1 = sc.module1Temp.GetRealValue();
	sc.shareData.input.ad.temp_module2 = sc.module2Temp.GetRealValue();
	
	sc.shareData.input.io.in_32.cabinet = sc.cabinet.GetRealValue();
	sc.shareData.input.io.in_32.inFuse1 = sc.inFuse1.GetRealValue();
	sc.shareData.input.io.in_32.inFuse2 = sc.inFuse2.GetRealValue();
	sc.shareData.input.io.in_32.mainCon1 = sc.mainCon1.GetRealValue();
	sc.shareData.input.io.in_32.mainCon2 = sc.mainCon2.GetRealValue();
	sc.shareData.input.io.in_32.outCon1 = sc.outCon1.GetRealValue();
	sc.shareData.input.io.in_32.outCon2 = sc.outCon2.GetRealValue();
	sc.shareData.input.io.in_32.outCon3 = sc.outCon3.GetRealValue();
	sc.shareData.input.io.in_32.outCon4 = sc.outCon4.GetRealValue();
	sc.shareData.input.io.in_32.outCon5 = sc.outCon5.GetRealValue();
	sc.shareData.input.io.in_32.outFuse1 = sc.outFuse1.GetRealValue();
	sc.shareData.input.io.in_32.outFuse2 = sc.outFuse2.GetRealValue();
	sc.shareData.input.io.in_32.outFuse3 = sc.outFuse3.GetRealValue();
	sc.shareData.input.io.in_32.outFuse4 = sc.outFuse4.GetRealValue();
	sc.shareData.input.io.in_32.outFuse5 = sc.outFuse5.GetRealValue();
	
}

void state_control(void)
{
	sc.Run();
}

void slow_check(void)
{
	sc.SlowCheck();
	
	UpdateData();
}

void relays_refresh(void)
{
	sc.RelayRun();
    //faultKeeping.Refresh();
}

void ScManager::hmi_data_update(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	uint8_t i;
	uint16_t	hmi_cmd1;
	uint16_t	hmi_cmd2;
	static uint8_t cnt1 = 0;
	static uint8_t cnt2 = 0;
	static uint8_t cnt3 = 0;
	static uint8_t cnt4 = 0;
	static uint8_t cnt5 = 0;
	
	for (i=ADDR_W_MB_PARA; i<HMI_ADDR_W_NUM-1; i++)
	{
		if (p->hmi.HMI_WAddr_flag[i])
			break;
	}
	switch (i)
	{
		case ADDR_CHARGE_EN:
			hmi_cmd1 = p->hmi.CtrCmd.ChargeEn.CMD1;
			hmi_cmd2 = p->hmi.CtrCmd.ChargeEn.CMD2;
			switch (hmi_cmd1)
			{
				case MODULE1:
					if (hmi_cmd2 == 1)
					{
						sc.cb1Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						sc.cb1Mode->SetChargeEn(false);
					}
					break;
				case MODULE2:
					if (hmi_cmd2 == 1)
					{
						sc.cb2Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						sc.cb2Mode->SetChargeEn(false);
					}
					break;
				case MODULE3:
					if (hmi_cmd2 == 1)
					{
						sc.cb3Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						sc.cb3Mode->SetChargeEn(false);
					}
					break;
				case MODULE4:
					if (hmi_cmd2 == 1)
					{
						sc.cb4Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						sc.cb4Mode->SetChargeEn(false);
					}
					break;
				case MODULE5:
					if (hmi_cmd2 == 1)
					{
						sc.cb5Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						sc.cb5Mode->SetChargeEn(false);
					}
					break;
				default:
					break;
			}
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_CHARGE_CMD:
			sc.sysMode->ModeSet(CHARGE);
			hmi_cmd1 = p->hmi.CtrCmd.ChargeCmd.CMD1;
			hmi_cmd2 = p->hmi.CtrCmd.ChargeCmd.CMD2;
			switch (hmi_cmd1){
				case MODULE1:
					MB_LGA.cb1_SYS.input.Charge_Mode_Set = HMI_Cmd2;
					break;
				case MODULE2:
					MB_LGA.cb2_SYS.input.Charge_Mode_Set = HMI_Cmd2;
					break;
				case MODULE3:
					MB_LGA.cb3_SYS.input.Charge_Mode_Set = HMI_Cmd2;
					break;
				case MODULE4:
					MB_LGA.cb4_SYS.input.Charge_Mode_Set = HMI_Cmd2;
					break;
				case MODULE5:
					MB_LGA.cb5_SYS.input.Charge_Mode_Set = HMI_Cmd2;
					break;
				default:
					break;
					
			}
			HMI.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_DEV_TEST:
			MB_LGA.MB_SYS_INFO.SysModeSet = DEVICE_TEST;
			MB_LGA.CtrCmd.DevTestCmd = HMI.CtrCmd.DevTestCmd;
			HMI.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_SLEEP:
			MB_LGA.MB_SYS_INFO.SysModeSet = SLEEP;
			MB_LGA.CtrCmd.SleepCmd = HMI.CtrCmd.SleepCmd;
			HMI.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_RESTART:
			//发送停止充电指令
		
			//给控制板发送重启指令
			can.SendCan(Reboot);
			
			//延时
			
			//监控板重启
			HMI.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_RESTORE:
			HMI.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_W_MB_PARA:
			if(memcmp((void *)(&p->hmi.mbWrPara), (void *)(&p->hmi.mbPara), sizeof(MB_Para_STYP)) != 0)
			{
				//参数更新
				p->hmi.mbPara = p->hmi.mbPara;
				//参数写入Flash标志位置1
				p->sysInfo.wParFlag = true;
				p->hmi.HMI_WAddr_flag[i] = false;
			}
			break;
		
		case ADDR_W_CB1_PARA:
			if(memcmp((void *)(&p->Cb1WPara), (void *)(&p->Cb1Para), sizeof(CB_Para_STYP)) != 0)
			{
				//参数更新
				p->Cb1Para = p->Cb1WPara;
				if (cnt1 == 0)
				{
					//can.SendCan(Module1_Set_Par);
					cnt1++;
				}
				else
				{
					//can.SendCan(Module1_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt1 = 0;
				}
			}
			break;
			
		case ADDR_W_CB2_PARA:	
			if(memcmp((void *)(&p->Cb2WPara), (void *)(&p->Cb2Para), sizeof(CB_Para_STYP)) != 0)
			{
				//参数更新
				p->Cb2Para = p->Cb2WPara;
				if (cnt2 == 0)
				{
					//can.SendCan(Module2_Set_Par);
					cnt2++;
				}
				else
				{
					//can.SendCan(Module2_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt2 = 0;
				}
			}
			break;
		
		case ADDR_W_CB3_PARA:	
			if(memcmp((void *)(&p->Cb3WPara), (void *)(&p->Cb3Para), sizeof(CB_Para_STYP)) != 0)
			{
				//参数更新
				p->Cb3Para = p->Cb3WPara;
				if (cnt3 == 0)
				{
					//can.SendCan(Module3_Set_Par);
					cnt3++;
				}
				else
				{
					//can.SendCan(Module3_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt3 = 0;
				}
			}
			break;
			
		case ADDR_W_CB4_PARA:	
			if(memcmp((void *)(&p->Cb4WPara), (void *)(&p->Cb4Para), sizeof(CB_Para_STYP)) != 0)
			{
				//参数更新
				p->Cb4Para = p->Cb4WPara;
				if (cnt4 == 0)
				{
					//can.SendCan(Module4_Set_Par);
					cnt4++;
				}
				else
				{
					//can.SendCan(Module4_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt4 = 0;
				}
			}
			break;
			
		case ADDR_W_CB5_PARA:	
			if(memcmp((void *)(&p->Cb5WPara), (void *)(&p->Cb5Para), sizeof(CB_Para_STYP)) != 0)
			{
				//参数更新
				p->Cb5Para = p->Cb5WPara;
				if (cnt5 == 0)
				{
					//can.SendCan(Module5_Set_Par);
					cnt5++;
				}
				else
				{
					//can.SendCan(Module5_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt5 = 0;
				}
			}
			break;
			
		case ADDR_W_MB_RTC:
			//监控板时间设置
			HMI.HMI_WAddr_flag[i] = false;
			
		default:
			break;
	}
}


void * GetShareDataPtr(void)
{
	ScData * p = &(sc.shareData);
	return p;
}

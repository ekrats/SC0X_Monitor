#include "ScManager.h"
#include "ScManagerExtern.h"
#include "hmi_def.h"
#include "flash_storage_at45dbxx.h"
#include "string.h"

void ScManager::hmi_data_update(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	static int oldStatus;
	uint8_t i;
	uint16_t	hmi_cmd1;
	uint16_t	hmi_cmd2;
	static int cnt1 = 0;
	static int cnt2 = 0;
	static int cnt3 = 0;
	static int cnt4 = 0;
	static int cnt5 = 0;
	
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
						cb1Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						cb1Mode->SetChargeEn(false);
					}
					break;
				case MODULE2:
					if (hmi_cmd2 == 1)
					{
						cb2Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						cb2Mode->SetChargeEn(false);
					}
					break;
				case MODULE3:
					if (hmi_cmd2 == 1)
					{
						cb3Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						cb3Mode->SetChargeEn(false);
					}
					break;
				case MODULE4:
					if (hmi_cmd2 == 1)
					{
						cb4Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						cb4Mode->SetChargeEn(false);
					}
					break;
				case MODULE5:
					if (hmi_cmd2 == 1)
					{
						cb5Mode->SetChargeEn(true);
					}
					else if (hmi_cmd2 == 2)
					{
						cb5Mode->SetChargeEn(false);
					}
					break;
				default:
					break;
			}
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_CHARGE_CMD:
			sysMode->ModeSet(CHARGE);
			hmi_cmd1 = p->hmi.CtrCmd.ChargeCmd.CMD1;
			hmi_cmd2 = p->hmi.CtrCmd.ChargeCmd.CMD2;
			switch (hmi_cmd1){
				case MODULE1:
					cb1Mode->ModeSet(hmi_cmd2);
					break;
				case MODULE2:
					cb2Mode->ModeSet(hmi_cmd2);
					break;
				case MODULE3:
					cb3Mode->ModeSet(hmi_cmd2);
					break;
				case MODULE4:
					cb4Mode->ModeSet(hmi_cmd2);
					break;
				case MODULE5:
					cb5Mode->ModeSet(hmi_cmd2);
					break;
				default:
					break;
					
			}
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_DEV_TEST:
			sysMode->ModeSet(DEVICE_TEST);
			sysMode->SetDevTestCmd(p->hmi.CtrCmd.DevTestCmd);
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_SLEEP:
			if (p->hmi.CtrCmd.SleepCmd == true)
			{
				sysMode->ModeSet(SLEEP);
				sysMode->SetSleepMode(p->hmi.CtrCmd.SleepCmd);
				oldStatus = sysMode->GetMode();
			}
			else if (sysMode->GetMode() == SLEEP)
			{
				sysMode->ModeSet(oldStatus);
				sysMode->SetSleepMode(p->hmi.CtrCmd.SleepCmd);
			}
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_RESTART:
			//发送停止充电指令
		
			//给控制板发送重启指令
			SendCan(Reboot);
			
			//延时
			
			//监控板重启
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
			
		case ADDR_RESTORE:
			p->hmi.HMI_WAddr_flag[i] = false;
			break;
		
		case ADDR_W_MB_PARA:
			if(memcmp((void *)(&p->hmi.mbWrPara), (void *)(&p->hmi.mbPara), sizeof(MB_Para_STYP)) != 0)
			{
				//参数更新
				p->hmi.mbPara = p->hmi.mbPara;
				//参数写入Flash标志位置1
				shareData.status.status_bit.wParFlag = true;
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
					SendCan(Module1_Set_Par);
					cnt1++;
				}
				else
				{
					SendCan(Module1_Read_Par);
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
					SendCan(Module2_Set_Par);
					cnt2++;
				}
				else
				{
					SendCan(Module2_Read_Par);
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
					SendCan(Module3_Set_Par);
					cnt3++;
				}
				else
				{
					SendCan(Module3_Read_Par);
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
					SendCan(Module4_Set_Par);
					cnt4++;
				}
				else
				{
					SendCan(Module4_Read_Par);
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
					SendCan(Module5_Set_Par);
					cnt5++;
				}
				else
				{
					SendCan(Module5_Read_Par);
					p->hmi.HMI_WAddr_flag[i] = false;
					cnt5 = 0;
				}
			}
			break;
			
		case ADDR_W_MB_RTC:
			//监控板时间设置
			p->hmi.HMI_WAddr_flag[i] = false;
			
		default:
			break;
	}
}

void sys_par_write(MB_Para_STYP *par)
{
	int bch_record_size = sizeof(MB_Para_STYP);
	
	rt_device_t fs = rt_device_find("fs");
	rt_uint8_t *tmp = (rt_uint8_t *)rt_malloc(bch_record_size);
	
	rt_memcpy(tmp, par, bch_record_size);
	rt_device_write(fs, RECORD_PAR, tmp, bch_record_size);
	
	rt_free(tmp);
}

void sys_par_read(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	int bch_record_size = sizeof(MB_Para_STYP);
	rt_uint8_t * read_buf = (rt_uint8_t *)rt_malloc(512);
	
	rt_device_t fs = rt_device_find("fs");
	rt_uint8_t *tmp = (rt_uint8_t *)rt_malloc(bch_record_size);
	
	rt_device_read(fs, (RECORD_PAR << 16) ,&read_buf[0], 512);
	
	rt_memcpy(tmp, &read_buf[8], bch_record_size);
	
	rt_memcpy(&p->hmi.mbPara, tmp, bch_record_size);
	
	p->hmi.mbWrPara = p->hmi.mbPara;
	
	rt_free(tmp);
	rt_free(read_buf);
	
}

void UserRecord(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	if (p->status.status_bit.wParFlag)
	{
		p->status.status_bit.wParFlag = false;
		sys_par_write(&p->hmi.mbPara);
	}
	else if (p->status.status_bit.rParFlag)
	{
		p->status.status_bit.rParFlag = false;
		sys_par_read();
	}
}

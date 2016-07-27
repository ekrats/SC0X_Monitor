#include "ScManager.h"
#include "ScManagerExtern.h"
#include "hmi_def.h"
#include "string.h"
#include "flash_storage_at45dbxx.h"


void ParManage(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	uint8_t i;
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
	//MB_Para_STYP * p = (MB_Para_STYP *)&MB_LGA.MB_Para;
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
	
}

void UserRecord(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	if (p->sysInfo.wParFlag)
	{
		p->sysInfo.wParFlag = false;
		sys_par_write(&p->hmi.mbPara);
	}
	else if (p->sysInfo.rParFlag)
	{
		p->sysInfo.rParFlag = false;
		sys_par_read();
	}
}

#include "ScManager.h"
#include "ScManagerExtern.h"
#include "hmi_def.h"
#include "string.h"
#include "flash_storage_at45dbxx.h"


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

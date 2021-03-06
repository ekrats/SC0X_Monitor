
#ifndef __HMI_DEF__H__
#define __HMI_DEF__H__

//#include "stm32f4xx.h"
#include "MB_DataStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

#define 		true		1
#define			false		0

enum {
	NONE,
	MODULE1,
	MODULE2,
	MODULE3,
	MODULE4,
	MODULE5,
	MODULE_ALL = 16,
};

enum {
	CHARGE,
	DEVICE_TEST,
	SLEEP,
};

enum {
	NONE_EVENT,
	IN_SLEEP,
	OUT_SLEEP,
};

enum {
	ADDR_CHARGE_EN,
	ADDR_CHARGE_CMD,
	ADDR_DEV_TEST,
	ADDR_SLEEP,
	ADDR_RESTART,
	ADDR_RESTORE,
	ADDR_W_MB_PARA,
	ADDR_W_CB1_PARA,
	ADDR_W_CB2_PARA,
	ADDR_W_CB3_PARA,
	ADDR_W_CB4_PARA,
	ADDR_W_CB5_PARA,
	ADDR_W_MB_RTC,
	ADDR_MAX,
};

#define HMI_ADDR_W_NUM			ADDR_MAX

//写地址
#define HMI_ADDR_CHARGE_EN		0x0240//控制命令
#define HMI_ADDR_CHARGE_CMD		0x0242//控制命令
#define HMI_ADDR_DEV_TEST		0x0244//控制命令
#define HMI_ADDR_SLEEP			0x0246//控制命令
#define HMI_ADDR_RESTART		0x0248//控制命令
#define HMI_ADDR_RESTORE		0x024A//控制命令
#define HMI_ADDR_W_MB_PARA		0x0260//设置监控板控制参数
#define HMI_ADDR_W_CB1_PARA		0x0280//设置控制板1控制参数
#define HMI_ADDR_W_CB2_PARA   	0x02A0//设置控制板2控制参数
#define HMI_ADDR_W_CB3_PARA		0x02C0//设置控制板3控制参数
#define HMI_ADDR_W_CB4_PARA   	0x02E0//设置控制板4控制参数
#define HMI_ADDR_W_CB5_PARA   	0x0300//设置控制板5控制参数
#define HMI_ADDR_W_MB_RTC   	0x0380//?????????

typedef struct _HmiBuffApp_
{
//--------------------------------------------------------
//Monitor向触摸屏输出
//--------------------------------------------------------
	HMI_Status_STYP	mbStatus;
	MB_Para_STYP    mbPara;
	Version_STYP    version;
//--------------------------------------------------------
// 触摸屏向Monitor输出
//--------------------------------------------------------
	uint8_t 		HMI_WAddr_flag[HMI_ADDR_W_NUM];
	CtrCmd_STYP     CtrCmd;
	MB_Para_STYP    mbWrPara;
	TIME_STYP       Time;
}HMI_TYPE;

typedef struct _mb_RegData
{
	
	HMI_Status_STYP	mbStatus;
	CAN_CB_Status_STYP cb1Status;
	CAN_CB_Status_STYP cb2Status;
	CAN_CB_Status_STYP cb3Status;
	CAN_CB_Status_STYP cb4Status;
	CAN_CB_Status_STYP cb5Status;
	uint16_t		res1[146];
	//uint16_t        res1[256];

	MB_Para_STYP    mbPara;
	uint16_t        res2[18];
	CB_Para_STYP	Modue1_Para;
	uint16_t        res3[20];
	CB_Para_STYP	Modue2_Para;
	uint16_t        res4[20];
	CB_Para_STYP	Modue3_Para;
	uint16_t        res5[20];
	CB_Para_STYP	Modue4_Para;
	uint16_t        res6[20];
	CB_Para_STYP	Modue5_Para;
	uint16_t        res7[20];
	CB_Para_STYP	Modue6_Para;
	uint16_t        res8[20];
	CB_Para_STYP	Modue7_Para;
	uint16_t        res9[20];
	CB_Para_STYP	Modue8_Para;
	uint16_t        res10[20];
	
	Version_STYP    version;
	uint16_t        res11[26];
//--------------------------------------------------------
// 触摸屏向DSP输出
//--------------------------------------------------------			
	CtrCmd_STYP     CtrCmd;
	uint16_t		res12[24];
	MB_Para_STYP    mbWrPara;
	uint16_t        res13[18];
	CB_Para_STYP	Modue1_WPara;
	uint16_t        res14[20];
	CB_Para_STYP	Modue2_WPara;
	uint16_t        res15[20];
	CB_Para_STYP	Modue3_WPara;
	uint16_t        res16[20];
	CB_Para_STYP	Modue4_WPara;
	uint16_t        res17[20];
	CB_Para_STYP	Modue5_WPara;
	uint16_t        res18[20];
	CB_Para_STYP	Modue6_WPara;
	uint16_t        res19[20];
	CB_Para_STYP	Modue7_WPara;
	uint16_t        res20[20];
	CB_Para_STYP	Modue8_WPara;
	uint16_t        res21[20];
	TIME_STYP       Time;

}MB_RegData;

/*=============================================================================*/
/*******************************************************************************
*                                                                              *
*                       工程数据集  (Drive Layer)                              *
*                                                                              *
*                                                                              *
********************************************************************************/
/*=============================================================================*/

typedef struct _DS_HMI_
{
	MB_RegData	theDS_Reg;

}DS_HMI, *PDS_HMI;


/*******************************************************************************
*                                                                              *
*                       工程数据集: '引用'宏定义                               *
*                                                                              *
*                                                                              *
********************************************************************************/
/*=============================================================================*/
#define PDHMI(name)             (&(theDHMI.theDS_##name))
#define SDHMI(name)             (sizeof(##name))

/*=============================================================================*/
/*******************************************************************************
*                                                                              *
*                       工程数据集: 结构体变量定义                             *
*                                                                              *
*                                                                              *
********************************************************************************/
/*=============================================================================*/

#ifdef DSA_HMI
DS_HMI	theDHMI = { 0 };
#else
extern	DS_HMI	theDHMI;
#endif

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2016 TongYe **********END OF FILE****/




/*@}*/



#ifndef	 __MB_DATASTRUCT_H__
#define	 __MB_DATASTRUCT_H__
#include "stm32f4xx.h"

#define CAN_SINK_ID_MASK	(0x1F<<3)//refer to EXTID_STYP

#define CAN_ID_C0					0x00	
#define CAN_ID_C1					0x01//???1????					
#define CAN_ID_C2					0x02	
#define CAN_ID_C3					0x03
#define CAN_ID_C4					0x04
#define CAN_ID_C5					0x05					
#define CAN_ID_C6					0x06	
#define CAN_ID_C7					0x07
#define CAN_ID_C8					0x08
#define CAN_ID_C9					0x09//???1????					
#define CAN_ID_C10					0x0A	
#define CAN_ID_C11					0x0B
#define CAN_ID_C12					0x0C
#define CAN_ID_C13					0x0D//???1????					
#define CAN_ID_C14					0x0E	
#define CAN_ID_C15					0x0F

#define CAN_ID_M1					0x11//????1????
#define CAN_ID_M2					0x12//????2
#define CAN_ID_Mx					0x13//?????
#define CAN_ID_Cx					0x1C//?????
#define CAN_ID_M1CX					0x1D//?????
#define CAN_ID_M2CX					0x1E//?????
//#define CAN_ID_ALL					0x1F//?????
#define CAN_ID_AD					0x1F

typedef struct _Can_Ram_
{
	uint32_t  Tick;
	uint16_t  CanPort;
	uint16_t  BoardId;

}CAN_DATA_RAM, *PCAN_DATA_RAM;

typedef struct _Can_Rx_Ram_
{
	CAN_DATA_RAM parent;
	CanRxMsg     data;

}CAN_RX_DATA_RAM, *PCAN_RX_DATA_RAM;

enum{
	Module1_Set_Par	= 15,
	Module2_Set_Par,
	Module3_Set_Par,
	Module4_Set_Par,
	Module5_Set_Par,
	Module1_Charge,
	Module2_Charge,
	Module3_Charge,
	Module4_Charge,
	Module5_Charge,
	Module1_Read_Par,
	Module2_Read_Par,
	Module3_Read_Par,
	Module4_Read_Par,
	Module5_Read_Par,
	Reboot,
};

//------------function--------------------
enum{
	CAN_FUNC_CHARGE=0x01,	//?????	
	CAN_FUNC_SYNCH,				//???		
	CAN_FUNC_REBOOT,			//????	
	CAN_FUNC_SET_PARA,			//??????
	CAN_FUNC_SET_ADJUST,		//??????
	CAN_FUNC_SET_TIME,			//????
	CAN_FUNC_MB_STATUS,		//????????
	CAN_FUNC_CB_STATUS,		//?????????
	CAN_FUNC_CB_CONST,			//?????????,??????,?????????	
	CAN_FUNC_MB_CONST,		//?????????,??????,?????????	
	CAN_FUNC_SLEEP,				//????
	CAN_FUNC_STOP,				//??????????
	CAN_FUNC_S_POLL,				//???????????
	CAN_FUNC_P_POLL,				//?????????
	CAN_FUNC_AD_POLL,
};

typedef struct {
	u8 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;
}TIME_TYPE;

typedef struct{
	u16  day;
	u8   hour;
	u8   min;
}RUN_TIME_STYP;

typedef struct{
	u16 mbHwVersionW;
	u16 mbARMVersionW;
	u16 mbFPGAVersionW;
	u16 cbHwVersionW;
	u16 cbARMVersionW;
	u16 cbFPGAVersionW;
}Version_STYP;

typedef  struct{
	u16	   cabinetEnN :			1;
	u16    inFuse1N   :  		1;
	u16    inFuse2N   :  		1;
	u16    outFuse1N  : 		1;
	u16    outFuse2N  : 		1;
	u16    outFuse3N  : 		1;
	u16    outFuse4N  : 		1;
	u16    outFuse5N  : 		1;
	u16    preConN  : 		1;
	u16    mainCon1N: 	 	1;
	u16    mainCon2N: 	 	1;
	u16    outCon1N :  		1;
	u16    outCon2N :  		1;
	u16    outCon3N :  		1;
	u16    outCon4N :  		1;
	u16    outCon5N :  		1;
}In_Flags_STYP;

typedef  struct{
	u16	   outCon1N   :			1;
	u16    outCon2N   :  		1;
	u16    outCon3N   :  		1;
	u16    outCon4N   : 		1;
	u16    outCon5N   : 		1;
	u16    res1  	  : 		1;
	u16    preConN    : 		1;
	u16    mainCon1N  : 		1;
	u16    mainCon2N  : 		1;
	u16    res2		  :			7;
}Out_Flags_STYP;

typedef  struct{
	u16		canLostN	:		1;
	u16		AdLost		:		1;
	u16		res1		:		1;
	u16		rail1FailN	:		1;
	u16		rail2FailN	:		1;
	u16		rail3FailN	:		1;
	u16		rail4FailN	:		1;
	u16		rail5FailN	:		1;
	u16		res2		:		8;
}Run_Flags_STYP;

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

//д��ַ
#define HMI_ADDR_CHARGE_EN		0x0240//��������
#define HMI_ADDR_CHARGE_CMD		0x0242//��������
#define HMI_ADDR_DEV_TEST		0x0244//��������
#define HMI_ADDR_SLEEP			0x0246//��������
#define HMI_ADDR_RESTART		0x0248//��������
#define HMI_ADDR_RESTORE		0x024A//��������
#define HMI_ADDR_W_MB_PARA		0x0260//���ü�ذ���Ʋ���
#define HMI_ADDR_W_CB1_PARA		0x0280//���ÿ��ư�1���Ʋ���
#define HMI_ADDR_W_CB2_PARA   	0x02A0//���ÿ��ư�2���Ʋ���
#define HMI_ADDR_W_CB3_PARA		0x02C0//���ÿ��ư�3���Ʋ���
#define HMI_ADDR_W_CB4_PARA   	0x02E0//���ÿ��ư�4���Ʋ���
#define HMI_ADDR_W_CB5_PARA   	0x0300//���ÿ��ư�5���Ʋ���
#define HMI_ADDR_W_MB_RTC   	0x0380//?????????


typedef struct{
	u16 ACinVoltUnderW;				
	u16 ACinVoltOverW;	
	
	u16 busVoltW;
	u16 busVoltUnderW;				
	u16 busVoltOverW;
	u16 CH1chargeVoltOverW;
	u16 CH2chargeVoltOverW;
	u16 CH3chargeVoltOverW;
	u16 CH4chargeVoltOverW;
	u16 CH5chargeVoltOverW;
	u16 ACinCurrUnderW;				
	u16 ACinCurrOverW;	
	u16 LxTemprOver;
	u16 CapxTemprOver;
}MB_Para_STYP;

//typedef struct{
//	u16 inVoltUnderW;				
//	u16 inVoltOverW;					
//	u16 busVoltW;					
//	u16 busVoltUnderW;				
//	u16 busVoltOverW;				
//	u16 chargeVoltOverW;			
//	u16 inCurrOverW;				
//	u16 chargeCurrOverW;			
//	u16 DxTemprOver;				
//	u16 LxTemprOver;				
//}MB_Para_STYP1;

typedef struct{
	u16 res01:  				3;
	u16 fanOnN:  				1;			//??????
	u16 lowLoadN:  			1;			//????
	u16 igbt1OverTemprN: 1;			//IGBT1????
	u16 igbt2OverTemprN: 1;			//IGBT2????
	u16 capVoltFailN:		1;			//?????????
	u16 gridCapVolFailN:	1;			//?????????
	u16 flyCapBalanceN:	1;			//????????
	u16 capVoltLowN:		1;			//??????
	u16 res02:					4;
	u16 sysFailN:				1;	
	u16 chargeOnN:			1;			//????
	u16 floatChargeN:		1;			//????(??)
	u16 chargeIFailN:		1;			//??I?????		
	u16 chargeQFailN:		1;			//??Q?????
	u16 dischargeOnN:		1;			//????
	u16 floatDischargeN:	1;			//????(??)
	u16 dischargeIFailN:	1;			//??I?????
	u16 dischargeQFailN:	1;			//??Q?????
	u16 currDirectN:			1;			//????
	u16 swOverCurrN:		1;			//???			
	u16 hwOverCurrN:		1;			//???
	u16 swGridOverVoltN:	1;			//?????		
	u16 hwGridOverVoltN:	1;			//?????
	u16 swCapOverVoltN:	1;			//?????
	u16 hwCapOverVoltN:	1;			//?????
	u16 syncFailN:			1;
}CB_Flags_STYP;

typedef struct{
	u8 CMD;
	u8 Rate;
	u8 res[6];
}Charge_Cmd_STYP, *PCharge_Cmd_STYP;

typedef struct{
	u8 res01[2];
	CB_Flags_STYP flags;
	s16 currW;								//?????
	u16 flyingCapvoltW;				//?????
	u8 igbt1Tempr;						
	u8 igbt2Tempr;
	u16 gridCapvoltW;					//?????
	u16 capvoltW;						//?????
	u8 res02[8];
}CAN_CB_Status_STYP, *PCAN_CB_Status_STYP;

typedef struct{
	u16 chargeVoltW;
	u16 chargeCurrW;
	u16 chargeVoltOverW;
	u16 chargeCurrOverW;
	u16 dischargeVoltW;
	u16 dischargeCurrW;
	u16 dischargeVoltOverW;		
	u16 dischargeCurrOverW;		
	u16 flyingCapVoltOverW;
	u8 IGBT1TemprOver;
	u8 IGBT2TemprOver;
	u8 res[4];
}CB_Para_STYP, *PCB_Para_STYP;

typedef struct{
	u16 CMD1;
	u16 CMD2;
}ChargeCmd_STYP;

typedef struct{
	u16 CMD1;
	u16 CMD2;
}ChargeEn_STYP;

typedef struct{
	ChargeEn_STYP	ChargeEn;
	ChargeCmd_STYP  ChargeCmd;
	u16				DevTestCmd;
	u16				SleepCmd;
	u16				RestartCmd;
	u16				RestoreParCmd;
}CtrCmd_STYP;

typedef struct{
	u16 year;//offset 1900
	u16 mon;
	u16 mday;
	u16 hour;
	u16 min;
	u16 sec;
}TIME_STYP;

typedef struct _CAN_AN_VAL_       //������Դ��AD��
{
	uint16_t		Ch1ChargeVolt;		//1#�����ѹ
	uint16_t		Ch2ChargeVolt;		//2#�����ѹ
	uint16_t		Ch3ChargeVolt;		//3#�����ѹ
	uint16_t		Ch4ChargeVolt;		//4#�����ѹ
	uint16_t		Ch5ChargeVolt;		//5#�����ѹ
	uint16_t		res[3];

}DS_CAN_AN_VAL,*PDS_CAN_AN_VAL;

typedef struct _mb_statu_
{
/* 0x000 */	uint16_t		sys_mode;
/* 0x001 */	uint16_t		dcdc1_mode;
			uint16_t		dcdc1_step;
			uint16_t		dcdc2_mode;
			uint16_t		dcdc2_step;
			uint16_t		dcdc3_mode;
			uint16_t		dcdc3_step;
			uint16_t		dcdc4_mode;
			uint16_t		dcdc4_step;
			uint16_t		dcdc5_mode;
			uint16_t		dcdc5_step;
/* 0x002 */	In_Flags_STYP	In_Flags;      
/* 0x003 */	Run_Flags_STYP	Run_Flags;
/* 0x004 */	uint16_t  		In1_ACVolt;
/* 0x005 */ uint16_t  		In2_ACVolt;
/* 0x006 */	uint16_t		BusVolt;
/* 0x007 */	uint16_t		DC1_OutVolt;
/* 0x008 */	uint16_t		DC2_OutVolt;	
/* 0x009 */	uint16_t		DC3_OutVolt;
/* 0x00A */ uint16_t		DC4_OutVolt;
/* 0x00B */ uint16_t		DC5_OutVolt;
/* 0x00C */	uint16_t		In1_Curr;
/* 0x00D */	uint16_t		In2_Curr;
/* 0x00E */	uint16_t		Modue1_Temp;
/* 0x00F */	uint16_t		Modue2_Temp;
/* 0x010 */	uint16_t		FanIn_Temp;
/* 0x011 */	uint16_t		FanOut_Temp;
/* 0x012 */	uint16_t		Cap1_Temp;
/* 0x013 */	uint16_t		Cap2_Temp;
/* 0x014-0x016 */	TIME_TYPE	Time;
/* 0x017 */ uint16_t		Warn1;
/* 0x018 */ uint16_t		Warn2;
/* 0x019 */ uint16_t		Fault1;
/* 0x01A */ uint16_t		Fault2;
/* 0x01B */ uint16_t		Fault3;
/* 0x01C */ uint16_t		Event;
/* 0x01D */ uint16_t		signalCnt;
/* 0x01E */ uint16_t		chargeCntW;
/* 0x01F */ uint16_t		logNumW;
/* 0x020~0x021 */ RUN_TIME_STYP	RunTime;
/* 0x022~0x028 */ uint16_t		res1[7];
			CAN_CB_Status_STYP cb1Status;
			CAN_CB_Status_STYP cb2Status;
			CAN_CB_Status_STYP cb3Status;
			CAN_CB_Status_STYP cb4Status;
			CAN_CB_Status_STYP cb5Status;
}HMI_Status_STYP;

typedef struct _HmiBuffApp_
{
//--------------------------------------------------------
//Monitor���������
//--------------------------------------------------------
	HMI_Status_STYP	mbStatus;
	MB_Para_STYP    mbRdPara;
	CB_Para_STYP	Modue1_Para;
	CB_Para_STYP	Modue2_Para;
	CB_Para_STYP	Modue3_Para;
	CB_Para_STYP	Modue4_Para;
	CB_Para_STYP	Modue5_Para;
	Version_STYP    version;
//--------------------------------------------------------
// ��������Monitor���
//--------------------------------------------------------
	uint8_t 		HMI_WAddr_flag[HMI_ADDR_W_NUM];
	CtrCmd_STYP     CtrCmd;
	MB_Para_STYP    mbWrPara;
	CB_Para_STYP	Modue1_WPara;
	CB_Para_STYP	Modue2_WPara;
	CB_Para_STYP	Modue3_WPara;
	CB_Para_STYP	Modue4_WPara;
	CB_Para_STYP	Modue5_WPara;
	TIME_STYP       Time;
}HMI_TYPE;

typedef struct _mb_RegData
{
	
		    HMI_Status_STYP	mbStatus;
			uint16_t			res1[146];
			//uint16_t        res1[256];
	
			MB_Para_STYP    mbRdPara;
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
// ��������DSP���
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
*                       �������ݼ�  (Drive Layer)                              *
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
*                       �������ݼ�: '����'�궨��                               *
*                                                                              *
*                                                                              *
********************************************************************************/
/*=============================================================================*/
#define PDHMI(name)             (&(theDHMI.theDS_##name))
#define SDHMI(name)             (sizeof(##name))

/*=============================================================================*/
/*******************************************************************************
*                                                                              *
*                       �������ݼ�: �ṹ���������                             *
*                                                                              *
*                                                                              *
********************************************************************************/
/*=============================================================================*/

#ifdef DSA_HMI
DS_HMI	theDHMI = { 0 };
HMI_TYPE HMI = { 0 };
#else
extern HMI_TYPE HMI;
extern	DS_HMI	theDHMI;
#endif



#endif



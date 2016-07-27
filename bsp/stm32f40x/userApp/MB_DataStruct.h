#ifndef	 __MB_DATASTRUCT_H__
#define	 __MB_DATASTRUCT_H__
//#include "stm32f4xx.h"
#include "stm32f4xx.h"

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

typedef struct{
	u16 res01:  			3;
	u16 fanOnN:  			1;			
	u16 lowLoadN:  			1;			
	u16 igbt1OverTemprN: 	1;	
	u16 igbt2OverTemprN: 	1;	
	u16 capVoltFailN:		1;	
	u16 gridCapVolFailN:	1;	
	u16 flyCapBalanceN:		1;	
	u16 capVoltLowN:		1;	
	u16 res02:				4;
	u16 sysFailN:			1;	
	u16 chargeOnN:			1;	
	u16 floatChargeN:		1;	
	u16 chargeIFailN:		1;	
	u16 chargeQFailN:		1;	
	u16 dischargeOnN:		1;	
	u16 floatDischargeN:	1;	
	u16 dischargeIFailN:	1;	
	u16 dischargeQFailN:	1;	
	u16 currDirectN:		1;	
	u16 swOverCurrN:		1;	
	u16 hwOverCurrN:		1;	
	u16 swGridOverVoltN:	1;
	u16 hwGridOverVoltN:	1;
	u16 swCapOverVoltN:		1;
	u16 hwCapOverVoltN:		1;
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
	s16 currW;
	u16 flyingCapvoltW;
	u8 igbt1Tempr;						
	u8 igbt2Tempr;
	u16 gridCapvoltW;
	u16 capvoltW;
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

typedef struct _CAN_AN_VAL_       //数据来源于AD板
{
	uint16_t		Ch1ChargeVolt;		//1#输出电压
	uint16_t		Ch2ChargeVolt;		//2#输出电压
	uint16_t		Ch3ChargeVolt;		//3#输出电压
	uint16_t		Ch4ChargeVolt;		//4#输出电压
	uint16_t		Ch5ChargeVolt;		//5#输出电压
	uint16_t		res[3];

}DS_CAN_AN_VAL,*PDS_CAN_AN_VAL;

//------------------------------------------------------
// 系统信息
//------------------------------------------------------
typedef struct _MB_SYS_INFO_
{
	uint16_t 	SystemState;
	uint16_t	OutputMode;
	uint16_t    SysModeSet;
	
	uint8_t		wFault				: 1 ; //警告故障
	uint8_t		sFault				: 1 ; //严重故障
	uint8_t		busConnect			: 1 ;
	uint8_t		busVoltOK			: 1 ; //母线电压OK
	uint8_t		PreFinsh			: 1 ; //预充电完成状态位
	uint8_t		Charging			: 1 ;
	uint8_t		CanFault			: 1 ; //CAN掉线
	uint8_t		HmiFault			: 1 ; //显示屏通信标志位 0：通讯正常 1：异常
	uint8_t		AdFault				: 1 ; //AD板通信标志位 0：通讯正常 1：异常
	uint8_t		wParFlag			: 1 ;
	uint8_t		rParFlag			: 1 ;
	uint8_t		wFaultFlg			: 1 ;
	uint8_t		rFaultFlg			: 1 ;
	
}MB_LGA_INFO;

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
}HMI_Status_STYP;

#endif



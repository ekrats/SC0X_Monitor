
#ifndef __CAN_APP_DEF__H__
#define __CAN_APP_DEF__H__

#include "stm32f4xx.h"
#include "MB_DataStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct _Can_Data_Ram_
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

typedef struct _Can_Tx_Ram_
{
	CAN_DATA_RAM parent;
	CanTxMsg     data;

}CAN_TX_DATA_RAM, *PCAN_TX_DATA_RAM;


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
	
typedef union{
	u32 extIDDW;
	struct{
		u16 classID:			4;	
		u16 packetID:			5;
		u16 sourceID:			5;
		u16 res:					2;
		u16 sinkID:				5;
		u16 func:					5;
		u16 prio:					3;
		u16 dummy:				3;
	}st;
}EXTID_UTYP, *PEXTID_UTYP;

//=======================================
// can口
//=======================================
#define PORT1                  (1)
#define PORT2                  (2)
#define PORTx				   (3)

//=======================================
// 帧类别数目
//=======================================
#define CAN_STD_FRAME_NUM      (42)


//=======================================
//   数据帧类型
//=======================================
#define CAN_ZX_DIRC            (3)//触发发送帧
#define CAN_RX_DIRC            (2)//接收帧
#define CAN_TX_DIRC            (1)//周期发送帧

//=======================================
//   CAN2数据帧 配置结构体
//=======================================
typedef struct _std_msg_config
{
	uint8_t  canPort    :  4 ;
	uint8_t  direction  :  4 ;
	uint8_t  Dest       :  5 ;
	uint8_t  Src        :  5 ;
	uint8_t  FuncID     :  5 ;
	uint8_t  len;
	uint16_t clock;
	uint16_t sendTick;
	uint8_t  update;
	uint8_t  *CanBuffData;
	uint8_t  *AppBuffData;
	void (*callback)(CAN_RX_DATA_RAM*, EXTID_UTYP*, uint8_t);
}STD_MSG_CON_TB;

typedef struct
{
	Charge_Cmd_STYP Cb1ChargeCmd;
	Charge_Cmd_STYP Cb2ChargeCmd;
	Charge_Cmd_STYP Cb3ChargeCmd;
	Charge_Cmd_STYP Cb4ChargeCmd;
	Charge_Cmd_STYP Cb5ChargeCmd;
	CAN_CB_Status_STYP	Cb1Status;
	CAN_CB_Status_STYP	Cb2Status;
	CAN_CB_Status_STYP	Cb3Status;
	CAN_CB_Status_STYP	Cb4Status;
	CAN_CB_Status_STYP	Cb5Status;
	CB_Para_STYP	Cb1Para;
	CB_Para_STYP	Cb2Para;
	CB_Para_STYP	Cb3Para;
	CB_Para_STYP	Cb4Para;
	CB_Para_STYP	Cb5Para;
	CB_Para_STYP	Cb1WPara;
	CB_Para_STYP	Cb2WPara;
	CB_Para_STYP	Cb3WPara;
	CB_Para_STYP	Cb4WPara;
	CB_Para_STYP	Cb5WPara;
	DS_CAN_AN_VAL   AD_RxChnn; 
	uint8_t	reBoot[8];
	uint8_t null[8];
}CanBuf_config;

typedef struct
{
	Charge_Cmd_STYP Cb1ChargeCmd;
	Charge_Cmd_STYP Cb2ChargeCmd;
	Charge_Cmd_STYP Cb3ChargeCmd;
	Charge_Cmd_STYP Cb4ChargeCmd;
	Charge_Cmd_STYP Cb5ChargeCmd;
	CAN_CB_Status_STYP	Cb1Status;
	CAN_CB_Status_STYP	Cb2Status;
	CAN_CB_Status_STYP	Cb3Status;
	CAN_CB_Status_STYP	Cb4Status;
	CAN_CB_Status_STYP	Cb5Status;
	DS_CAN_AN_VAL   AD_RxChnn; 
	uint8_t	reBoot[8];
	uint8_t null[8];
}canAppBuf_config;

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2016 TongYe **********END OF FILE****/




/*@}*/



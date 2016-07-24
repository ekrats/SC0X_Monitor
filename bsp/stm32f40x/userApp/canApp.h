#ifndef _CAN_APP_H_
#define _CAN_APP_H_

#include "stm32f4xx.h"
#include <rtthread.h>
//#include "canLinker.h"
#include "MB_DataStruct.h"

typedef union{
	u32 extIDDW;
	struct{
		u16 classID:				4;	//??
		u16 packetID:				5;
		u16 sourceID:				5;
		u16 res:						2;
		u16 sinkID:				5;
		u16 func:					5;
		u16 prio:					3;
		u16 dummy:				3;
	}st;
}EXTID_UTYP, *PEXTID_UTYP;

//=======================================
// can��
//=======================================
#define PORT1                  (1)
#define PORT2                  (2)
#define PORTx				   (3)

//=======================================
// ֡�����Ŀ
//=======================================
#define CAN_STD_FRAME_NUM      (42)


//=======================================
//   ����֡����
//=======================================
#define CAN_ZX_DIRC            (3)//��������֡
#define CAN_RX_DIRC            (2)//����֡
#define CAN_TX_DIRC            (1)//���ڷ���֡

//=======================================
//   CAN2����֡ ���ýṹ��
//=======================================
typedef struct _std_msg_config
{
	uint8_t  canPort    :  4 ;
	uint8_t  direction  :  4 ;
	uint8_t  Dest       :  5 ; //Txer ID
	uint8_t  Src        :  5 ; //Rxer ID
	uint8_t  FuncID     :  5 ; //function ID
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
}AppBuf_config;

void CycleMsgUpdate_data_sch(void);
void CycleMsgPush_sch(void);
void TriggerMsgPush_sch(void);
void MsgPop_cb_sch(CAN_RX_DATA_RAM* pbuf, uint32_t _tId);
void TriggerMsgUpdate_data_sch(uint8_t frame);

class CanApp {
private:
	CanTxMsg _tCyc;									// CAN���ͻ�����
	STD_MSG_CON_TB *_std_msg;
protected:
	
	
public:
	CanApp(void);
	CanBuf_config CanBuf;
	AppBuf_config AppBuf;
	uint16_t    CanCnt;
	uint16_t	CanFltCnt[6];
	uint16_t    CanStateWord;

	void SendCan(uint8_t frame);					//CANż��֡���ͺ���
	void CycleMsgUpdate_data(void);
	void CycleMsgPush(void);
	void TriggerMsgUpdate_data(uint8_t frame);
	void TriggerMsgPush(void);
	void MsgRx_Manage(CAN_RX_DATA_RAM* pbuf, uint32_t _tId);
	static void MsgRx_Deal(CAN_RX_DATA_RAM* _p, EXTID_UTYP* _tRecId, uint8_t frame);
	uint32_t MakeCanMsgExtID(uint8_t classID, uint8_t func,  uint8_t frame, uint8_t dest, uint8_t src);
	void CanApp_MakeTxAckMsg(uint32_t extID, uint8_t len, uint8_t* data, CanTxMsg* msg);
};

extern CanApp can;

#endif


#ifndef _CAN_APP_H_
#define _CAN_APP_H_

#include "stm32f4xx.h"
#include <rtthread.h>
#include "MB_DataStruct.h"
#include "can_app_def.h"
#include "sc.h"

class CanApp {
private:
	CanTxMsg _tCyc;									// CAN·¢ËÍ»º³åÇø
	STD_MSG_CON_TB *_std_msg;
public:
	ScData * scData;

	CanApp(void);
	CanBuf_config CanBuf;
	uint16_t    CanCnt;
	uint16_t	CanFltCnt[6];
	uint16_t    CanStateWord;

	void CycleMsgUpdate_data(void);
	void CycleMsgPush(void);
	void TriggerMsgUpdate_data(uint8_t frame);
	void TriggerMsgPush(void);
	void MsgRx_Manage(CAN_RX_DATA_RAM* pbuf, uint32_t _tId);
	static void MsgRx_Deal(CAN_RX_DATA_RAM* _p, EXTID_UTYP* _tRecId, uint8_t frame);
	uint32_t MakeCanMsgExtID(uint8_t classID, uint8_t func,  uint8_t frame, uint8_t dest, uint8_t src);
	void CanApp_MakeTxAckMsg(uint32_t extID, uint8_t len, uint8_t* data, CanTxMsg* msg);
};

#endif


#include "canApp.h"
#include "canTask.h"
#include "stm32f4xx.h"
#include <rtthread.h>
#include "string.h"
#include "can.h"
#include "can_app_def.h"
#include "ScManagerExtern.h"
#include "ScManager.h"
#include "DataStruct.h"
extern CanApp can;

/****************************************************************
* Description    : STD CAN数据帧 配置表
*****************************************************************/
STD_MSG_CON_TB _std_msg_table[CAN_STD_FRAME_NUM] = 
{ 
	/*port     type          dest         src       func                  len    clock,   tick  update   candata               appdata  */
	{PORT1, CAN_TX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_CHARGE, 	8,     0,	   10,    0, 	(uint8_t *)&can.CanBuf.Cb1ChargeCmd,    (uint8_t *)&can.sCan.canAppBuf.Cb1ChargeCmd,    	RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_CHARGE, 	8,     0,	   10,    0, 	(uint8_t *)&can.CanBuf.Cb2ChargeCmd,    (uint8_t *)&can.sCan.canAppBuf.Cb2ChargeCmd,    	RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_CHARGE, 	8,     0,	   10,    0, 	(uint8_t *)&can.CanBuf.Cb3ChargeCmd,    (uint8_t *)&can.sCan.canAppBuf.Cb3ChargeCmd,    	RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_CHARGE, 	8,     0,	   10,    0, 	(uint8_t *)&can.CanBuf.Cb4ChargeCmd,    (uint8_t *)&can.sCan.canAppBuf.Cb4ChargeCmd,    	RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_CHARGE, 	8,     0,	   10,    0, 	(uint8_t *)&can.CanBuf.Cb5ChargeCmd,    (uint8_t *)&can.sCan.canAppBuf.Cb5ChargeCmd,    	RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_S_POLL,     8,     0,	   12,    0, 	can.CanBuf.null,    (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_S_POLL,     8,     0,	   12,    0, 	can.CanBuf.null,    (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_S_POLL,     8,     0,	   12,    0, 	can.CanBuf.null,    (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_S_POLL,     8,     0,	   12,    0, 	can.CanBuf.null,    (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_S_POLL,     8,     0,	   12,    0, 	can.CanBuf.null,    (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_P_POLL, 	8,     0,	   300,   0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_P_POLL, 	8,     0,	   300,   0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_P_POLL, 	8,     0,	   300,   0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_P_POLL, 	8,     0,	   300,   0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	{PORT1, CAN_TX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_P_POLL, 	8,     0,	   300,   0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    			RT_NULL},
	
	{PORT1, CAN_ZX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_SET_PARA,   24,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb1WPara,   (uint8_t *)&can.sCan.Cb1WPara,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_SET_PARA,   24,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb2WPara,   (uint8_t *)&can.sCan.Cb2WPara,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_SET_PARA,   24,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb3WPara,   (uint8_t *)&can.sCan.Cb3WPara,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_SET_PARA,   24,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb4WPara,   (uint8_t *)&can.sCan.Cb4WPara,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_SET_PARA,   24,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb5WPara,   (uint8_t *)&can.sCan.Cb5WPara,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_CHARGE,    8,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb1ChargeCmd,   (uint8_t *)&can.sCan.canAppBuf.Cb1ChargeCmd,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_CHARGE,    8,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb2ChargeCmd,   (uint8_t *)&can.sCan.canAppBuf.Cb2ChargeCmd,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_CHARGE,    8,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb3ChargeCmd,   (uint8_t *)&can.sCan.canAppBuf.Cb3ChargeCmd,    	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_CHARGE,    8,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb4ChargeCmd,   (uint8_t *)&can.sCan.canAppBuf.Cb4ChargeCmd,   	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_CHARGE,    8,     0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb5ChargeCmd,   (uint8_t *)&can.sCan.canAppBuf.Cb5ChargeCmd,   	RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C1,    CAN_ID_M1,  CAN_FUNC_P_POLL,	   8,    0,	   0,      0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    		RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C2,    CAN_ID_M1,  CAN_FUNC_P_POLL,	   8,    0,	   0,      0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    		RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C3,    CAN_ID_M1,  CAN_FUNC_P_POLL,	   8,    0,	   0,      0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    		RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C4,    CAN_ID_M1,  CAN_FUNC_P_POLL,	   8,    0,	   0,      0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    		RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_C5,    CAN_ID_M1,  CAN_FUNC_P_POLL,	   8,    0,	   0,      0, 	can.CanBuf.null,   (uint8_t *)&can.sCan.canAppBuf.null,    		RT_NULL},
	{PORT1, CAN_ZX_DIRC, CAN_ID_Cx,    CAN_ID_M1,  CAN_FUNC_REBOOT,	   8,     0,	   0,      0, 	can.CanBuf.reBoot,   (uint8_t *)&can.sCan.canAppBuf.reBoot,    		RT_NULL},
	
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C1,  CAN_FUNC_S_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb1Status,   (uint8_t *)&can.sCan.cb1Status,    	can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C2,  CAN_FUNC_S_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb2Status,   (uint8_t *)&can.sCan.cb2Status,    	can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C3,  CAN_FUNC_S_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb3Status,   (uint8_t *)&can.sCan.cb3Status,    	can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C4,  CAN_FUNC_S_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb4Status,   (uint8_t *)&can.sCan.cb4Status,    	can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C5,  CAN_FUNC_S_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb5Status,   (uint8_t *)&can.sCan.cb5Status,    	can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C1,  CAN_FUNC_P_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb1Para,   (uint8_t *)&can.sCan.Cb1Para,    		can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C2,  CAN_FUNC_P_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb2Para,   (uint8_t *)&can.sCan.Cb2Para,    		can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C3,  CAN_FUNC_P_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb3Para,   (uint8_t *)&can.sCan.Cb3Para,    		can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C4,  CAN_FUNC_P_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb4Para,   (uint8_t *)&can.sCan.Cb4Para,    		can.MsgRx_Deal},
	{PORT1, CAN_RX_DIRC, CAN_ID_M1CX,    CAN_ID_C5,  CAN_FUNC_P_POLL,    24,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.Cb5Para,   (uint8_t *)&can.sCan.Cb5Para,    		can.MsgRx_Deal},
		
	{PORT2, CAN_RX_DIRC, CAN_ID_M1,      CAN_ID_AD,  CAN_FUNC_AD_POLL,   16,    0,	   0,      0, 	(uint8_t *)&can.CanBuf.AD_RxChnn,   (uint8_t *)&can.sCan.canAppBuf.AD_RxChnn,    		can.MsgRx_Deal},	
		
};

//static __IO STD_MSG_CON_TB *_std_msg = _std_msg_table;

CanApp::CanApp(ScData & scCan):sCan(scCan)                                                                                                                                                   
{
	_std_msg = _std_msg_table;
	
	CanStateWord = 0x000F;
	
	canOffTime = 200;
	
}

/****************************************************************
* Function Name  : StdMsgRx_Common_cb
* Description    : 接收控制板状态数据处理 
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::MsgRx_Deal(CAN_RX_DATA_RAM* _p, EXTID_UTYP* _tRecId, uint8_t frame)
{
	static uint16_t DataLen = 0;
	//------------------------------------------------------------------
	// 收到首帧
	//------------------------------------------------------------------
	if(_tRecId->st.packetID == 0)  DataLen = 0;
	//------------------------------------------------------------------
	// 接收数据
	//------------------------------------------------------------------
	rt_memcpy((uint8_t*)(can._std_msg[frame].CanBuffData + _tRecId->st.packetID * 8),
		_p->data.Data,
		_p->data.DLC);
	//------------------------------------------------------------------
	// 统计收到帧长
	//------------------------------------------------------------------
	DataLen += _p->data.DLC;
	//------------------------------------------------------------------
	// 收到尾帧
	//------------------------------------------------------------------
	if(_tRecId->st.packetID == ((can._std_msg[frame].len - 1) / 8))
	{
		//----------------------------------------------------------------
		// 帧长正确,更新数据
		//----------------------------------------------------------------
		if(DataLen == can._std_msg[frame].len)
		{
			can._std_msg[frame].update = 1;
		}
		//----------------------------------------------------------------
		// 清0帧长
		//----------------------------------------------------------------
		DataLen = 0;
	}
}

/****************************************************************
* Function Name  : StdMsgPush_sch
* Description    : 发送数据帧
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::CycleMsgPush(void)
{
	uint32_t ExtId = 0;
	uint16_t frameLen = 0;
	uint8_t Sendlen = 0;
	uint8_t ScanFrame = 0; 
	uint8_t frameCnt = 0;
	//-----------------------------------------------------------------
	// 扫描端口信息
	//------------------------------------------------------------------
	for(ScanFrame = 0; ScanFrame < CAN_STD_FRAME_NUM; ScanFrame++)
	{
		if(_std_msg[ScanFrame].direction == CAN_TX_DIRC)
		{
			if(++_std_msg[ScanFrame].clock < _std_msg[ScanFrame].sendTick)
				continue;
			else _std_msg[ScanFrame].clock = 0;
			
			if(_std_msg[ScanFrame].CanBuffData == RT_NULL)
				continue;
			//-----------------------------------------------------------------
			// 获取要发送端口数据长度
			//------------------------------------------------------------------
			frameLen = _std_msg[ScanFrame].len;
			//-----------------------------------------------------------------
			// 首帧帧编号
			//------------------------------------------------------------------
			frameCnt = 0;
			//-----------------------------------------------------------------
			// 拆包发送
			//------------------------------------------------------------------
			while (frameLen > 0)
			{
				//-----------------------------------------------------------
				// 计算本包数据长度
				//-----------------------------------------------------------
				if(frameLen > 8)
				{
					Sendlen = 8;
					frameLen -= 8;
				}
				else
				{
					Sendlen = frameLen;
					frameLen = 0;
				}

				ExtId = MakeCanMsgExtID(_std_msg[ScanFrame].direction,
					_std_msg[ScanFrame].FuncID,                           //功能号
					frameCnt,                                             //帧号
					_std_msg[ScanFrame].Dest,                             //宿端
					_std_msg[ScanFrame].Src                              //源端
					);

				CanApp_MakeTxAckMsg(ExtId,					                   	//扩展ID
					Sendlen,                                              //发送数据字节长度
					&_std_msg[ScanFrame].CanBuffData[frameCnt*8],         //要发送数据
					&_tCyc);                                              //发送缓冲区

				can_send_buffer(_std_msg[ScanFrame].canPort , &_tCyc);

				//-----------------------------------------------------------------
				// 维护帧编号
				//------------------------------------------------------------------
				frameCnt++;
			}
		}
	}
}


/****************************************************************
* Function Name  : StdTriggerMsgPush_sch
* Description    : 发送数据帧
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::TriggerMsgPush(void)
{
	uint32_t ExtId = 0;
	uint16_t frameLen = 0;
	uint8_t Sendlen = 0;
	uint8_t ScanFrame = 0; 
	uint8_t frameCnt = 0;

	//-----------------------------------------------------------------
	// 扫描端口信息
	//------------------------------------------------------------------
	for(ScanFrame = 0; ScanFrame < CAN_STD_FRAME_NUM; ScanFrame++)
	{
		if(_std_msg[ScanFrame].direction == CAN_ZX_DIRC)
		{			
			if(_std_msg[ScanFrame].update  == 0)
				continue;

			_std_msg[ScanFrame].update = 0;

			if((_std_msg[ScanFrame].CanBuffData == RT_NULL) && (_std_msg[ScanFrame].len > 0))
				continue;
			//-----------------------------------------------------------------
			// 获取要发送端口数据长度
			//------------------------------------------------------------------
			frameLen = _std_msg[ScanFrame].len;
			//-----------------------------------------------------------------
			// 首帧帧编号
			//------------------------------------------------------------------
			frameCnt = 0;
			//-----------------------------------------------------------------
			// 拆包发送
			//------------------------------------------------------------------
			while(frameLen > 0)
			{
				//-----------------------------------------------------------
				// 计算本包数据长度
				//-----------------------------------------------------------
				if(frameLen > 8)
				{
					Sendlen = 8;
					frameLen -= 8;
				}
				else
				{
					Sendlen = frameLen;
					frameLen = 0;
				}

				ExtId = MakeCanMsgExtID(_std_msg[ScanFrame].direction, //优先级
					_std_msg[ScanFrame].FuncID,                          //功能号
					frameCnt,                                            //帧号
					_std_msg[ScanFrame].Dest,                            //宿端
					_std_msg[ScanFrame].Src);                             //源端

				CanApp_MakeTxAckMsg(ExtId,						           //扩展ID
					Sendlen,                                       //发送数据字节长度
					&_std_msg[ScanFrame].CanBuffData[frameCnt*8],  //要发送数据
					&_tCyc);                                       //发送缓冲区

				can_send_buffer(_std_msg[ScanFrame].canPort , &_tCyc);

				//-----------------------------------------------------------------
				// 维护帧编号
				//------------------------------------------------------------------
				frameCnt++;
			}
		}
	}
}

/****************************************************************
* Function Name  : CanStateWord
* Description    : 接收数据帧
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::MsgRx_Manage(CAN_RX_DATA_RAM* pbuf, uint32_t _tId)
{
	CAN_RX_DATA_RAM *_p  = pbuf;
	PEXTID_UTYP _tRecStdId = (PEXTID_UTYP)&_tId;
	uint8_t ScanFrame = 0; 

	if(_p->parent.CanPort == PORT1)
	{
		for(ScanFrame = 0; ScanFrame < CAN_STD_FRAME_NUM; ScanFrame++)
		{
			if((_std_msg[ScanFrame].direction == CAN_RX_DIRC) 
				&& (_std_msg[ScanFrame].canPort == _p->parent.CanPort)
				&& (_std_msg[ScanFrame].Src == _tRecStdId->st.sourceID)
				&& (_std_msg[ScanFrame].Dest == _tRecStdId->st.sinkID)
				&& (_std_msg[ScanFrame].FuncID == _tRecStdId->st.func))
			{
				if(_std_msg[ScanFrame].callback == RT_NULL)
					continue;
				
				_std_msg[ScanFrame].callback(_p, _tRecStdId, ScanFrame);
				
				if (can.CanCnt > 0)
				{
					can.CanCnt = 0;
				}
				
				if(_std_msg[ScanFrame].Src == CAN_ID_C1)
				{
					CanFltCnt[0] = 0;
				}
				
				if(_std_msg[ScanFrame].Src == CAN_ID_C2)
				{
					CanFltCnt[1] = 0;
				}
				
				if(_std_msg[ScanFrame].Src == CAN_ID_C3)
				{
					CanFltCnt[2] = 0;
				}

				if(_std_msg[ScanFrame].Src == CAN_ID_C4)
				{
					CanFltCnt[3] = 0;
				}
				
				if(_std_msg[ScanFrame].Src == CAN_ID_C5)
				{
					CanFltCnt[4] = 0;
				}

			}
		}
	}
	else if(_p->parent.CanPort == PORT2)
	{
		for(ScanFrame = CAN_STD_FRAME_NUM -1; ScanFrame < CAN_STD_FRAME_NUM; ScanFrame++)
		{
			if((_std_msg[ScanFrame].direction == CAN_RX_DIRC) 
				&& (_std_msg[ScanFrame].canPort == _p->parent.CanPort)
				&& (_std_msg[ScanFrame].Src == _tRecStdId->st.sourceID)
				&& (_std_msg[ScanFrame].Dest == _tRecStdId->st.sinkID)
				&& (_std_msg[ScanFrame].FuncID == _tRecStdId->st.func))
			{
				if(_std_msg[ScanFrame].callback == RT_NULL)
					continue;
				
				_std_msg[ScanFrame].callback(_p, _tRecStdId, ScanFrame);
				
				if(_std_msg[ScanFrame].Src == CAN_ID_AD)
				{
					CanFltCnt[5] = 0;
				}
			}
		}
	}
	else
	{
		/*  do some warning*/
	}
}

/****************************************************************
* Function Name  : StdMsgUpdate_data_sch
* Description    : 更新发送接收数据
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::CycleMsgUpdate_data(void)
{
	uint8_t  ScanFrame = 0;
	//-----------------------------------------------------------------
	// 扫描端口信息
	//------------------------------------------------------------------
	for(ScanFrame = 0; ScanFrame < CAN_STD_FRAME_NUM; ScanFrame++)
	{
		if(_std_msg[ScanFrame].direction == CAN_RX_DIRC)
		{
			if(_std_msg[ScanFrame].update == 1)
			{
				memcpy(_std_msg[ScanFrame].AppBuffData, _std_msg[ScanFrame].CanBuffData, _std_msg[ScanFrame].len);
				_std_msg[ScanFrame].update = 0;
			}
		}
		else if(_std_msg[ScanFrame].direction == CAN_TX_DIRC)
		{				
			rt_memcpy(_std_msg[ScanFrame].CanBuffData, _std_msg[ScanFrame].AppBuffData, _std_msg[ScanFrame].len);
		}
	}
}

/****************************************************************
* Function Name  : StdTriggerMsgUpdate_data_sch
* Description    : 更新发送接收数据
*                   
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
void CanApp::TriggerMsgUpdate_data(uint8_t frame)
{
	//-----------------------------------------------------------------
	// 更新端口信息
	//------------------------------------------------------------------
	if(_std_msg[frame].direction == CAN_ZX_DIRC)
	{
		if((_std_msg[frame].CanBuffData != RT_NULL) && (_std_msg[frame].AppBuffData != RT_NULL))
		{
			rt_memcpy(_std_msg[frame].CanBuffData, _std_msg[frame].AppBuffData, _std_msg[frame].len);
		}
		_std_msg[frame].update = 1;
	}
}


/*******************************************************************************
* Function Name  : void CanApp_MakeTxAckMsg(uint32_t extID, uint8_t len, uint8_t* data, CanTxMsg* msg)
* Description    :
*                   
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CanApp::CanApp_MakeTxAckMsg(uint32_t extID, uint8_t len, uint8_t* data, CanTxMsg* msg)
{
	if(len >= 8)
	{
		len = 8;
	}

	msg->ExtId   = extID;
	msg->IDE     = CAN_ID_EXT;
	msg->RTR     = 0;
	msg->DLC     = len;

	if((data != RT_NULL) && (len != 0))
	{
		msg->Data[0] = *data;
		msg->Data[1] = *(data + 1);
		msg->Data[2] = *(data + 2);
		msg->Data[3] = *(data + 3);
		msg->Data[4] = *(data + 4);
		msg->Data[5] = *(data + 5);
		msg->Data[6] = *(data + 6);
		msg->Data[7] = *(data + 7);
	}
}

/*******************************************************************************
* Function Name  : static uint32_t MakeCanStdMsgExtID(uint8_t priority, uint8_t func,  uint8_t frame,
uint8_t dest, uint8_t src, uint8_t checksum)
* Description    :
*                   
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t CanApp::MakeCanMsgExtID(uint8_t classID, uint8_t func,  uint8_t frame,
								 uint8_t dest, uint8_t src)
{
	EXTID_UTYP id;

	id.st.classID  = classID;
	id.st.packetID = frame;
	id.st.sourceID   = src;
	id.st.sinkID   = dest;
	id.st.func    = func;

	return (*(uint32_t*)&id & 0x1FFFFFFF);
}

void can_rx_interface(uint8_t port, CanRxMsg* msg)
{
	CAN_RX_DATA_RAM * rx_buffer = RT_NULL;
    uint8_t * tmp = msg->Data;
    
    if(tmp != RT_NULL)
    {
        rx_buffer = (CAN_RX_DATA_RAM *)rt_malloc(sizeof(CAN_RX_DATA_RAM));
        if(rx_buffer != RT_NULL)
        {
            rx_buffer->parent.CanPort = port;
			rx_buffer->data.StdId = msg->StdId;
			rx_buffer->data.ExtId = msg->ExtId;
			rx_buffer->data.IDE = msg->IDE;
			rx_buffer->data.RTR = msg->RTR;
			rx_buffer->data.DLC = msg->DLC;
            rx_buffer->data.Data[0] = tmp[0];
            rx_buffer->data.Data[1] = tmp[1];
            rx_buffer->data.Data[2] = tmp[2];
            rx_buffer->data.Data[3] = tmp[3];
            rx_buffer->data.Data[4] = tmp[4];
            rx_buffer->data.Data[5] = tmp[5];
            rx_buffer->data.Data[6] = tmp[6];
            rx_buffer->data.Data[7] = tmp[7];
            can.MsgRx_Manage(rx_buffer, msg->ExtId);
        }
		rt_free(rx_buffer);
    }
	
	can.CanCnt++;
	
}

/*******************************************************************************
* Function Name  : void CanApp_CycleStream_Server(void)
* Description    : 负责 应用层与链路层 数据的定时更新
*                   
* Input          : None
* Output         : None
* Return         : None   xiangchuanyu
*******************************************************************************/
void CanApp_CycleStream_Server(void)
{
	static uint8_t TimeCnt = 0;
	
	//-----------------------------------------------------------
	// 更新CAN数据发送接收缓冲区
	//-----------------------------------------------------------
	can.CycleMsgUpdate_data();
	if(++TimeCnt >= 10)
	{
		TimeCnt = 0;
	}
	//-----------------------------------------------------------
	// 管理发送CAN数据帧
	//-----------------------------------------------------------
	can.CycleMsgPush();
}

/*******************************************************************************
* Function Name  : void CanApp_TriggerStream_Server(void)
* Description    : 负责 应用层与链路层 数据的定时更新
*                   
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CanApp_TriggerStream_Server(void)
{
	can.TriggerMsgPush();
}

/*******************************************************************************
* Function Name  : void cantx(uint8_t frame)
* Description    :
*                   
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SendCan(uint8_t frame)
{
	if(frame < CAN_STD_FRAME_NUM)
	{
		can.TriggerMsgUpdate_data(frame);
		Bsp_can_send_trigger_event();
	}
}

//================================================================
//Function Name: 
//Description  :BCH通讯初始化
//Input        : 
//Output       : 
//Return       : 
//================================================================
void gbch_init(void)
{
    can_services_init();
    can_rx_thread_init();
	can_thread_init();

	//---------------------------------------------------------------
	// 打开CAN控制器中断
	//---------------------------------------------------------------
#if(BSP_USE_CAN1 == 1)
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
#endif

#if(BSP_USE_CAN2 == 1)
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
#endif
}

void can_led(void)
{
	if(can.CanStateWord > 0)
	{
		stm32_hw_io_toggle(1);
	}
	else
	{
		stm32_hw_io_off(1);
	}
}

/*******************************************************************************
* Function Name  :  
* Description    :
*
*
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void can_fault(void)
{
	ScData * p = (ScData *)GetShareDataPtr();
	uint8_t portScan = 0;
	//------------------------------------------------------
	// 持续没有CAN没有接收到数据，判断CAN通讯丢失
	//------------------------------------------------------
	for(portScan = 0; portScan < 6; portScan++)
	{
		can.CanFltCnt[portScan]++;

		if(can.CanFltCnt[portScan] >= can.canOffTime)
		{
			can.CanFltCnt[portScan] = can.canOffTime;
			//-----------------------------------------------------
			// CAN接收1异常
			//-----------------------------------------------------
			can.CanStateWord &= ~(uint16_t)(0x0001 << portScan);
		}
		else
		{
			//-----------------------------------------------------
			// CAN接收1正常
			//-----------------------------------------------------
			can.CanStateWord |= (uint16_t)(0x0001 << portScan);
		}
	}
	
	p->status.status_bit.AdFault = (~can.CanStateWord) & 0x0020;
	can.CanCnt ++;
	
	if (can.CanCnt >= can.canOffTime)
	{
		can.CanCnt = can.canOffTime;
		p->status.status_bit.CanFault = 1; 
	}
	else
	{
		p->status.status_bit.CanFault = 0;
	}
}

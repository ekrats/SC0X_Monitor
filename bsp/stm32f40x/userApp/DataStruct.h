#ifndef _DataStruct_h_
#define _DataStruct_h_

#include "stdint.h"
#include "hmi_def.h"
#include "can_app_def.h"

enum _io_input_index_{
	cabinetN,
	inFuse1N,
	inFuse2N,
	outFuse1N,
	outFuse2N,
	outFuse3N,
	outFuse4N,
	outFuse5N,
	preConN = 13,
	mainCon1N,
	mainCon2N,
	outCon1N = 18,
	outCon2N,
	outCon3N,
	outCon4N,
	outCon5N,
};

enum _io_output_index_{
	outCon1,
	outCon2,
	outCon3,
	outCon4,
	outCon5,
	outCon6,
	preCon,
	mainCon1,
	mainCon2,
};

typedef union _io_output_{
	int out[16];
	struct{
		int outCon1;
		int outCon2;
		int outCon3;
		int outCon4;
		int outCon5;
		int outCon6;
		int preCon;
		int mainCon1;
		int mainCon2;
		int res[7];
	}out_32;
}io_output_type;

typedef union _io_input_{
	int in[16];
	struct{
		int cabinet;
		int inFuse1;
		int inFuse2;
		int outFuse1;
		int outFuse2;
		int outFuse3;
		int outFuse4;
		int outFuse5;
		int preCon;
		int mainCon1;
		int mainCon2;
		int outCon1;
		int outCon2;
		int outCon3;
		int outCon4;
		int outCon5;
	}in_32;
}io_input_type;

typedef struct{
	uint16_t i_in1;
	uint16_t i_in2;
	uint16_t temp_module1;
	uint16_t temp_module2;
	uint16_t temp_in;
	uint16_t temp_out;
	uint16_t temp_cap1;
	uint16_t temp_cap2;
	uint16_t u_ac1;
	uint16_t u_ac2;
	uint16_t u_bus;
}ad_data_type;

typedef struct{
	io_input_type 	io;
	ad_data_type	ad;
}DataInput;

typedef union _sc_warn_t
{
    struct 
    {
        uint32_t can_lost		  :1;
        uint32_t ad_lost		  :1;
        uint32_t in_temp_over     :1;
        uint32_t u_in_max_fast   :1;
		
        uint32_t u_in_min_fast   :1;
        uint32_t i_out_max_fast  :1;
        uint32_t i_out_min_fast  :1;
        uint32_t u_out_max_hw    :1;
        
        uint32_t i_out_max_slow  :1;
        uint32_t i_out_min_slow  :1; 
        uint32_t u_in_max_slow   :1;
        uint32_t u_in_min_slow   :1;
        uint32_t short_bc        :1;
        
        uint32_t u_out_max_slow  :1;
        uint32_t u_out_min_slow  :1;
        uint32_t res26           :1;
		
        uint32_t res27           :1;
        uint32_t temp_igbt1      :1;
		uint32_t temp_igbt2      :1;
        uint32_t temp_voltage    :1;
    }warn_bit;
    struct
    {
        uint16_t l_low;
        uint16_t l_high;
    }warn_u16;
    uint32_t warn_u32;
}sc_warn_t;

typedef union _sc_fault_t
{
    struct 
    {
        uint32_t u_out_max_fast  :1;
        uint32_t u_out_min_fast  :1;
        uint32_t i_out_max_hw    :1;
        uint32_t u_in_max_fast   :1;
		
        uint32_t u_in_min_fast   :1;
        uint32_t i_out_max_fast  :1;
        uint32_t i_out_min_fast  :1;
        uint32_t u_out_max_hw    :1;
        
        uint32_t i_out_max_slow  :1;
        uint32_t i_out_min_slow  :1; 
        uint32_t u_in_max_slow   :1;
        uint32_t u_in_min_slow   :1;
        uint32_t short_bc        :1;
        
        uint32_t u_out_max_slow  :1;
        uint32_t u_out_min_slow  :1;
        uint32_t res26           :1;
		
        uint32_t res27           :1;
        uint32_t temp_igbt1      :1;
		uint32_t temp_igbt2      :1;
        uint32_t temp_voltage    :1;
    }fault_bit;
    struct
    {
        uint32_t monitor		: 12;
        uint32_t dcdc1			: 4 ;
        uint32_t dcdc2			: 4 ;
        uint32_t dcdc3			: 4 ;
		uint32_t dcdc4			: 4 ;
		uint32_t dcdc5			: 4 ;
    }fault_u8;
	struct
    {
        uint16_t l_low;
        uint16_t l_high;
    }fault_u16;
    uint32_t fault_u32;
}sc_fault_t;

//---------------------------------------------------------------------------------- 
//-----bch status struct(union)
typedef union _sc_status_t
{
    struct _status_bit
    {
        uint32_t		wFault				: 1 ; //警告故障
		uint32_t		sFault				: 1 ; //严重故障
		uint32_t		dcdc1Fault			: 1 ;
		uint32_t		dcdc2Fault			: 1 ;
		uint32_t		dcdc3Fault			: 1 ;
		uint32_t		dcdc4Fault			: 1 ;
		uint32_t		dcdc5Fault			: 1 ;
		uint32_t		busConnect			: 1 ;
		uint32_t		busVoltOK			: 1 ; //母线电压OK
		uint32_t		PreFinsh			: 1 ; //预充电完成状态位
		uint32_t		Charging			: 1 ;
		uint32_t		CanFault			: 1 ; //CAN掉线
		uint32_t		HmiFault			: 1 ; //显示屏通信标志位 0：通讯正常 1：异常
		uint32_t		AdFault				: 1 ; //AD板通信标志位 0：通讯正常 1：异常
		uint32_t		wParFlag			: 1 ;
		uint32_t		rParFlag			: 1 ;
		uint32_t		wFaultFlg			: 1 ;
		uint32_t		rFaultFlg			: 1 ;
    }status_bit;
    struct _status_u16
    {
        uint16_t low;
        uint16_t high;
    }status_u16;
    uint32_t status_u32;
}sc_status_t;

typedef struct{
	io_output_type  io;
	sc_fault_t fault;
	sc_warn_t	warn;
}DataOutput;

typedef struct{
	DataInput 	input;
	DataOutput	output;
	sc_status_t status;
	CAN_CB_Status_STYP cb1Status;
	CAN_CB_Status_STYP cb2Status;
	CAN_CB_Status_STYP cb3Status;
	CAN_CB_Status_STYP cb4Status;
	CAN_CB_Status_STYP cb5Status;
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
	HMI_TYPE 	hmi;
	canAppBuf_config canAppBuf;
}ScData;

#endif


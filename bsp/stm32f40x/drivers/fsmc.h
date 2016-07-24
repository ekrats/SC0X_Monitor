/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   9:04
	filename: 	f:\work\STM32-CM80A-Slave\startup\fsmc.h
	file path:	f:\work\STM32-CM80A-Slave\startup
	file base:	fsmc
	file ext:	h
	author:		Coase Dahl
	
	purpose:	
*********************************************************************/
#ifndef PROJECT_CM80A_SLAVE_FSMC_H
#define PROJECT_CM80A_SLAVE_FSMC_H

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_CHANEL_MAX			 (32)
#define	OUTPUT_CHANEL_MAX			 (16)

#define FPGA_BEGIN_ADDR        (0x68000000)
#define FPGA_END_ADDR          (0x6C000000)

#define FPGA_INPUT_OFFSET      (1024)
#define FPGA_OUTPUT_OFFSET     (512)

int System_fsmc_init(void);
void io_update(void);
int * get_io_input_address(void);
void io_write_output(void* buffer);
void io_read_input(void* buffer);

#ifdef __cplusplus
}
#endif
	
#endif
//////////////////////////////////////////////////////////////////////////

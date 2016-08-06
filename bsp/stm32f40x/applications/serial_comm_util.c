/**
*************************************************************************
* This file is part of CM80A
* COPYRIGHT (C) 1999-2013, TongYe Inverter Development Team
* @file    serial_comm_util.c
* @brief   This file provides all the serial comm util firmware functions.
* Change Logs:
* Date           Author       Notes
* 2013/10/31     Coase        the first version
* 2014/5         hepj         for cm80a v1.5
*************************************************************************
*/

#include "serial_comm_util.h"
#include "flash_storage_at45dbxx.h"
#include "crc16.h"
#include "string.h"
#include "iap_service.h"
#include "ScManagerExtern.h"
#include "DataStruct.h"

serial_protocol protocol = { 0 };
int cmd_code = 0;
static uint8_t usart_tx_data[TX_BUFFER_SIZE - 1];//4224+1
uint16_t tx_length = 0;
static int file_write_index = 0;

void check_file_call_back(int state_code)
{
    usart_tx_data[0] = state_code;
    tx_length = 0;
    
    tx_length = protocol.get_output_data(&protocol, usart_tx_data, tx_length + 1);
    mem_printf((char*)protocol.tx_buffer, tx_length);
}

static void call_back(void * buffer, int length)
{
    ScData * p = (ScData *)GetShareDataPtr();
	uint8_t * data = (uint8_t*)buffer;
    int rx_file_index = 0;
    switch (data[0])
    {
    case 0xcc:
        {
			file_write_index = 0;
			iap_send(IAP_CMD_CHECK_FILE, 7);
        }
        return;

    case 'u':
        {
            file_write_index = 0;
			rt_memcpy(p->canAppBuf.iap_info, (uint8_t *)data + 2, length - 2);
			iap_send(IAP_CMD_SET_INFO, length - 2);
        }
        return;

    case 'f':
        rx_file_index = (data[2] + (data[3] << 8));
		if (p->canAppBuf.iap_index == file_write_index)
		{
			usart_tx_data[0] = 0x00;
			rt_memcpy(p->canAppBuf.iap_file, (uint8_t *)data + 4, length - 4);
			iap_send(IAP_CMD_WRITE_FILE, length - 4);
		}
        else if (rx_file_index == file_write_index)
        {
            usart_tx_data[0] = 0x00;
			rt_memcpy(p->canAppBuf.iap_file, (uint8_t *)data + 4, length - 4);
            file_write_index++;
			iap_send(IAP_CMD_WRITE_FILE, length - 4);
        }
        else if (rx_file_index < file_write_index)
        {
            usart_tx_data[0] = 0x0;
        }
        else
        {
            usart_tx_data[0] = 0x81;
        }
        tx_length = 0;
        return;

    default://其它情况，不响应，直接返回
        return;
    }
    tx_length = protocol.get_output_data(&protocol, usart_tx_data, tx_length + 1);
    mem_printf((char*)protocol.tx_buffer, tx_length);
}

/*
static void call_back(void * buffer, int length)
{
    uint8_t * data = (uint8_t*)buffer;
    int rx_file_index = 0;
    switch (data[0])
    {
    case 0xcc:
        {
            extern struct rt_semaphore sem_reset_cpu;
            iap_message * msg = (iap_message *)rt_malloc(sizeof(iap_message));
            msg->cmd = IAP_CMD_CHECK_FILE;
            msg->length = 0;
            *(u32*)&msg->data = (u32)check_file_call_back;
            *(u32*)&msg->data[4] = (u32)&sem_reset_cpu;
            file_write_index = 0;
            rt_mb_send((rt_mailbox_t)get_iap_mailbox(), (rt_uint32_t)msg);
        }
        return;

    case 'u':
        {
            iap_message * msg = (iap_message *)rt_malloc(sizeof(iap_message));
            msg->cmd = IAP_CMD_SET_INFO;
            msg->length = length - 2;
            rt_memcpy(msg->data, (uint8_t *)data + 2, length - 2);
            usart_tx_data[0] = 0x00;
            file_write_index = 0;
            tx_length = 0;
            rt_mb_send((rt_mailbox_t)get_iap_mailbox(), (rt_uint32_t)msg);
        }
        break;

    case 'f':
        rx_file_index = (data[2] + (data[3] << 8));
        if (rx_file_index == file_write_index)
        {
            iap_message * msg = (iap_message *)rt_malloc(sizeof(iap_message));
            msg->cmd = IAP_CMD_WRITE_FILE;
            msg->length = length - 4;
            rt_memcpy(msg->data, (uint8_t *)data + 4, length - 4);
            usart_tx_data[0] = 0x00;
            file_write_index++;
            rt_mb_send((rt_mailbox_t)get_iap_mailbox(), (rt_uint32_t)msg);
        }
        else if (rx_file_index < file_write_index)
        {
            usart_tx_data[0] = 0x0;
        }
        else
        {
            usart_tx_data[0] = 0x81;
        }
        tx_length = 0;
        break;

    default://其它情况，不响应，直接返回
        return;
    }
    tx_length = protocol.get_output_data(&protocol, usart_tx_data, tx_length + 1);
    mem_printf((char*)protocol.tx_buffer, tx_length);
}
*/
static void except(serial_protocol_exception exception)
{
    switch (exception)
    {
    case illegal_length:
        usart_tx_data[0] = 0x81;
        break;
    case checksum_failure:
        usart_tx_data[0] = 0x82;
        break;
    default:
        break;
    }
}

void serial_comm_init(void)
{
    init_serial_protocol(&protocol);
    protocol.call_back = call_back;
    protocol.except = except;
}


/******************** cmd request ********************************************/


debug_control_t debug_instruction;


#include "version.h"
#include <stdio.h>
#include <rtdef.h>
static char version_info[192] = { 0 };

char * get_board_info()
{
    sprintf(version_info, "%d.%d.%d.%d build at %s by %s use RTT v%d.%d.%d and HD v%d.%d for %s\r\n",
        MAJOR_VERSION_NUMBER, MINOR_VERSION_NUMBER,
        REVISION_NUMBER, BUILD_NUMBER, BUILD_TIME,
        BUILDER_NAME,
        (int)RT_VERSION, (int)RT_SUBVERSION, (int)RT_REVISION,
        1, 0, PROJECT_NAME);
    return version_info;
}

char * get_short_version()
{
    sprintf(version_info, "%d.%02d", MAJOR_VERSION_NUMBER, REVISION_NUMBER);
    return version_info;
}
#include "stm32f4xx.h"

void reset_device()
{
    //关闭所有中断相应
    __set_FAULTMASK(1);
    //系统复位
    NVIC_SystemReset();

}

void full_version()
{
    rt_kprintf(get_board_info());
}

#include "finsh.h"
FINSH_FUNCTION_EXPORT(full_version, show full version information);
FINSH_FUNCTION_EXPORT(reset_device, reset device);


/******************** (C) COPYRIGHT 2013 TongYe ***********END OF FILE****/


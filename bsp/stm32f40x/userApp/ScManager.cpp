#include "ScManager.h"
#include "ScManagerExtern.h"
#include "io.h"
#include "ad.h"
#include "fsmc.h"


ScManager sc;
CanApp can;
System_Mode SysMode;

void ScManager::RelayRun(void)
{
    relays.Refresh();
	ContactRelayRun();
}

int * buffer = NULL;
void ad_init(void)
{
	buffer = get_ad_data_buffer();
	sc.SetCan(can);
	can.scData = &sc.shareData;
	
	sc.input1Current.Init(&buffer[i_in1_index], 4500, 95);
	sc.input2Current.Init(&buffer[i_in2_index], 4500, 95);
	sc.inputAc1Voltage.Init(&buffer[u_ac1_index], 13330, 95);
	sc.inputAc2Voltage.Init(&buffer[u_ac2_index], 13330, 95);
	sc.inputBusVoltage.Init(&buffer[u_bus_index], 13330, 95);
	sc.module1Temp.Init(&buffer[temp_module1_index], 0, 5);
	sc.module2Temp.Init(&buffer[temp_module2_index], 0, 5);
	sc.fanInTemp.Init(&buffer[temp_in_index], 0, 5);
	sc.fanOutTemp.Init(&buffer[temp_out_index], 0, 5);
	sc.cap1Temp.Init(&buffer[temp_cap1_index], 0, 5);
	sc.cap2Temp.Init(&buffer[temp_cap2_index], 0, 5);
}

int *io_buffer = NULL;
int *io_out_buffer = NULL;
void io_init(void)
{
	io_buffer = get_io_input_address();
	io_out_buffer = sc.shareData.output.io.out;
	
	sc.inFuse1.Init(&io_buffer[inFuse1N]);
	sc.inFuse2.Init(&io_buffer[inFuse2N]);
	sc.outFuse1.Init(&io_buffer[outFuse1N]);
	sc.outFuse2.Init(&io_buffer[outFuse2N]);
	sc.outFuse3.Init(&io_buffer[outFuse3N]);
	sc.outFuse4.Init(&io_buffer[outFuse4N]);
	sc.outFuse5.Init(&io_buffer[outFuse5N]);
	
	sc.mainCon1.Init(&io_buffer[mainCon1N], &io_out_buffer[mainCon1], 10);
	sc.mainCon2.Init(&io_buffer[mainCon2N], &io_out_buffer[mainCon2], 10);
	sc.preCon.Init(&io_buffer[preConN], &io_out_buffer[preCon], 10);
	sc.outCon1.Init(&io_buffer[outCon1N], &io_out_buffer[outCon1], 10);
	sc.outCon2.Init(&io_buffer[outCon2N], &io_out_buffer[outCon2], 10);
	sc.outCon3.Init(&io_buffer[outCon3N], &io_out_buffer[outCon3], 10);
	sc.outCon4.Init(&io_buffer[outCon4N], &io_out_buffer[outCon4], 10);
	sc.outCon5.Init(&io_buffer[outCon5N], &io_out_buffer[outCon5], 10);
}

void ScManager::RefreshAdData(void)
{
    sensorList.Begin();
    ITransducer * tmp = NULL;
    while ((tmp = sensorList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshPt100Data(void)
{
	pt100List.Begin();
	PT100 * tmp = NULL;
	while ((tmp = pt100List.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshIoData(void)
{
	ioList.Begin();
	ITransducer * tmp = NULL;
	while ((tmp = ioList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::RefreshConData(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Update();
    }
}

void ScManager::ContactRelayRun(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Refresh();
    }
}

void ScManager::ContactCheck(void)
{
	ContactList.Begin();
	Contactor * tmp = NULL;
	while ((tmp = ContactList.Next()) != NULL)
    {
        tmp->Check();
    }
}

void ScManager::SetCan(CanApp & pCan)
{
	this->can = pCan;
}

void data_deal(void)
{
	sc.RefreshAdData();
	sc.RefreshIoData();
	sc.RefreshConData();
	sc.RefreshPt100Data();
	sc.ContactCheck();
}

void io_output(void)
{
	io_write_output(sc.shareData.output.io.out);
}

void UpdateData(void)
{
	sc.shareData.input.ad.i_in1 = sc.input1Current.GetAverageRealValue();
	sc.shareData.input.ad.i_in2 = sc.input2Current.GetAverageRealValue();
	sc.shareData.input.ad.u_ac1 = sc.inputAc1Voltage.GetAverageRealValue();
	sc.shareData.input.ad.u_ac2 = sc.inputAc2Voltage.GetAverageRealValue();
	sc.shareData.input.ad.u_bus = sc.inputBusVoltage.GetAverageRealValue();
	sc.shareData.input.ad.temp_cap1 = sc.cap1Temp.GetRealValue();
	sc.shareData.input.ad.temp_cap2 = sc.cap2Temp.GetRealValue();
	sc.shareData.input.ad.temp_in = sc.fanInTemp.GetRealValue();
	sc.shareData.input.ad.temp_out = sc.fanOutTemp.GetRealValue();
	sc.shareData.input.ad.temp_module1 = sc.module1Temp.GetRealValue();
	sc.shareData.input.ad.temp_module2 = sc.module2Temp.GetRealValue();
}

void slow_check(void)
{
	sc.SlowCheck();
	
	UpdateData();
}

void relays_refresh(void)
{
	sc.RelayRun();
    //faultKeeping.Refresh();
}

void * GetShareDataPtr(void)
{
	ScData * p = &(sc.shareData);
	return p;
}

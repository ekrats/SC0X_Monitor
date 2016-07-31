#include "ScManager.h"
#include "ScManagerExtern.h"
#include "io.h"
#include "ad.h"
#include "fsmc.h"


ScManager sc;
CanApp can;
System_Mode SysMode;
CbMode	Cb1Mode;
CbMode	Cb2Mode;
CbMode	Cb3Mode;
CbMode	Cb4Mode;
CbMode	Cb5Mode;

static Relay	preChargeRelay(60000);
static Relay	preCharge2Relay(500);
static Relay	dcdc1StartRelay(2000);
static Relay	dcdc1FloatRelay(5000);
static Relay	dcdc2StartRelay(2000);
static Relay	dcdc2FloatRelay(5000);
static Relay	dcdc3StartRelay(2000);
static Relay	dcdc3FloatRelay(5000);
static Relay	dcdc4StartRelay(2000);
static Relay	dcdc4FloatRelay(5000);
static Relay	dcdc5StartRelay(2000);
static Relay	dcdc5FloatRelay(5000);

void ScManager::RelayRun(void)
{
    relays.Refresh();
	WarnRelayRun();
	FaultRelayRun();
	ContactRelayRun();
}

void module_init(void)
{
	SysMode.Init(&sc.shareData.input.io.in[cabinetN]);
	Cb1Mode.Init(7, CB_STATE_IDLE, (int *)&sc.shareData.canAppBuf.Cb1ChargeCmd);
	Cb2Mode.Init(8, CB_STATE_IDLE, (int *)&sc.shareData.canAppBuf.Cb2ChargeCmd);
	Cb3Mode.Init(9, CB_STATE_IDLE, (int *)&sc.shareData.canAppBuf.Cb3ChargeCmd);
	Cb4Mode.Init(10, CB_STATE_IDLE, (int *)&sc.shareData.canAppBuf.Cb4ChargeCmd);
	Cb5Mode.Init(11, CB_STATE_IDLE, (int *)&sc.shareData.canAppBuf.Cb5ChargeCmd);
}

void ScManager::Init(void)
{
	FaultCheckModuleInit();
	
	module_init();
	
	sc.sysMode = &SysMode;
	sc.cb1Mode = &Cb1Mode;
	sc.cb2Mode = &Cb2Mode;
	sc.cb3Mode = &Cb3Mode;
	sc.cb4Mode = &Cb4Mode;
	sc.cb5Mode = &Cb5Mode;
	
	cbModelist.Add(&Cb1Mode);
	cbModelist.Add(&Cb2Mode);
	cbModelist.Add(&Cb3Mode);
	cbModelist.Add(&Cb4Mode);
	cbModelist.Add(&Cb5Mode);
	
	relays.Register(&preChargeRelay);
	relays.Register(&preCharge2Relay);
	relays.Register(&dcdc1StartRelay);
	relays.Register(&dcdc1FloatRelay);
	relays.Register(&dcdc2StartRelay);
	relays.Register(&dcdc2FloatRelay);
	relays.Register(&dcdc3StartRelay);
	relays.Register(&dcdc3FloatRelay);
	relays.Register(&dcdc4StartRelay);
	relays.Register(&dcdc4FloatRelay);
	relays.Register(&dcdc5StartRelay);
	relays.Register(&dcdc5FloatRelay);
}

int * buffer = NULL;
void ad_init(void)
{
	buffer = get_ad_data_buffer();
	
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
	
	sc.cabinet.Init(&io_buffer[cabinetN]);
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

void sc_init(void)
{
	sc.SetCan(&can);
	can.scData = &sc.shareData;
	SysMode.scData = &sc.shareData;
	SysMode.preStep1Relay = &preChargeRelay;
	SysMode.preStep2Relay = &preCharge2Relay;
	Cb1Mode.startDelay = &dcdc1StartRelay;
	Cb1Mode.floatDelay = &dcdc1FloatRelay;
	Cb2Mode.startDelay = &dcdc2StartRelay;
	Cb2Mode.floatDelay = &dcdc2FloatRelay;
	Cb3Mode.startDelay = &dcdc3StartRelay;
	Cb3Mode.floatDelay = &dcdc3FloatRelay;
	Cb4Mode.startDelay = &dcdc4StartRelay;
	Cb4Mode.floatDelay = &dcdc4FloatRelay;
	Cb5Mode.startDelay = &dcdc5StartRelay;
	Cb5Mode.floatDelay = &dcdc5FloatRelay;
	
	ad_init();
	io_init();
	sc.Init();
}

void ScManager::MonitorStatusUpdata(void)
{
	HMI_Status_STYP *p = &sc.shareData.hmi.mbStatus;
	
	p->sys_mode = sysMode->GetMode();
	p->dcdc1_mode = cb1Mode->GetMode();
	p->dcdc2_mode = cb2Mode->GetMode();
	p->dcdc3_mode = cb3Mode->GetMode();
	p->dcdc4_mode = cb4Mode->GetMode();
	p->dcdc5_mode = cb5Mode->GetMode();
	
	p->dcdc1_step = sc.shareData.cb1Status.flags.chargeOnN + sc.shareData.cb1Status.flags.floatChargeN;
	p->dcdc2_step = sc.shareData.cb2Status.flags.chargeOnN + sc.shareData.cb2Status.flags.floatChargeN;
	p->dcdc3_step = sc.shareData.cb3Status.flags.chargeOnN + sc.shareData.cb3Status.flags.floatChargeN;
	p->dcdc4_step = sc.shareData.cb4Status.flags.chargeOnN + sc.shareData.cb4Status.flags.floatChargeN;
	p->dcdc5_step = sc.shareData.cb5Status.flags.chargeOnN + sc.shareData.cb5Status.flags.floatChargeN;
	
	p->In_Flags.cabinetEnN = sc.shareData.input.io.in_32.cabinet;
	p->In_Flags.inFuse1N = sc.shareData.input.io.in_32.inFuse1;
	p->In_Flags.inFuse2N = sc.shareData.input.io.in_32.inFuse2;
	p->In_Flags.mainCon1N = sc.shareData.input.io.in_32.mainCon1;
	p->In_Flags.mainCon2N = sc.shareData.input.io.in_32.mainCon2;
	p->In_Flags.outCon1N = sc.shareData.input.io.in_32.outCon1;
	p->In_Flags.outCon2N = sc.shareData.input.io.in_32.outCon2;
	p->In_Flags.outCon3N = sc.shareData.input.io.in_32.outCon3;
	p->In_Flags.outCon4N = sc.shareData.input.io.in_32.outCon4;
	p->In_Flags.outCon5N = sc.shareData.input.io.in_32.outCon5;
	p->In_Flags.outFuse1N = sc.shareData.input.io.in_32.outFuse1;
	p->In_Flags.outFuse2N = sc.shareData.input.io.in_32.outFuse2;
	p->In_Flags.outFuse3N = sc.shareData.input.io.in_32.outFuse3;
	p->In_Flags.outFuse4N = sc.shareData.input.io.in_32.outFuse4;
	p->In_Flags.outFuse5N = sc.shareData.input.io.in_32.outFuse5;
	
}

void ScManager::UpdateCbState(void)
{
	cbModelist.Begin();
	CbMode * tmp = NULL;
	while ((tmp = cbModelist.Next()) != NULL)
    {
        tmp->Run();
    }
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

void ScManager::WarnRelayRun(void)
{
	warnList.Begin();
	ScFailure * tmp = NULL;
	while ((tmp = warnList.Next()) != NULL)
    {
        tmp->RefreshRelays();
    }
}

void ScManager::FaultRelayRun(void)
{
	failureList.Begin();
	ScFailure * tmp = NULL;
	while ((tmp = failureList.Next()) != NULL)
    {
        tmp->RefreshRelays();
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

void ScManager::SetCan(CanApp* pCan)
{
	this->can = pCan;
}

void ScManager::Run(void)
{
	sc.sysMode->Run();
	if (sc.sysMode->GetMode() == SYS_STATE_STANDBY)
	{
		sc.cb1Mode->SetCondition(true);
		sc.cb2Mode->SetCondition(true);
		sc.cb3Mode->SetCondition(true); 
		sc.cb4Mode->SetCondition(true); 
		sc.cb5Mode->SetCondition(true);
	}
	else
	{
		sc.cb1Mode->SetCondition(false);
		sc.cb2Mode->SetCondition(false);
		sc.cb3Mode->SetCondition(false); 
		sc.cb4Mode->SetCondition(false); 
		sc.cb5Mode->SetCondition(false);
	}
	sc.UpdateCbState();
}

void ScManager::FaultDeal(void)
{
	shareData.status.status_bit.sFault = shareData.output.fault.fault_u8.monitor > 0;
	shareData.status.status_bit.dcdc1Fault = shareData.output.fault.fault_u8.dcdc1 > 0;
	shareData.status.status_bit.dcdc2Fault = shareData.output.fault.fault_u8.dcdc2 > 0;
	shareData.status.status_bit.dcdc3Fault = shareData.output.fault.fault_u8.dcdc3 > 0;
	shareData.status.status_bit.dcdc4Fault = shareData.output.fault.fault_u8.dcdc4 > 0;
	shareData.status.status_bit.dcdc5Fault = shareData.output.fault.fault_u8.dcdc5 > 0;
	
	sysMode->SetFaultState(shareData.status.status_bit.sFault);
	cb1Mode->SetFaultState(shareData.status.status_bit.dcdc1Fault);
	cb2Mode->SetFaultState(shareData.status.status_bit.dcdc2Fault);
	cb3Mode->SetFaultState(shareData.status.status_bit.dcdc3Fault);
	cb4Mode->SetFaultState(shareData.status.status_bit.dcdc4Fault);
	cb5Mode->SetFaultState(shareData.status.status_bit.dcdc5Fault);
}

void data_refresh(void)
{
	sc.RefreshAdData();
	sc.RefreshIoData();
	sc.RefreshConData();
	sc.RefreshPt100Data();
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
	
	sc.shareData.input.io.in_32.cabinet = sc.cabinet.GetRealValue();
	sc.shareData.input.io.in_32.inFuse1 = sc.inFuse1.GetRealValue();
	sc.shareData.input.io.in_32.inFuse2 = sc.inFuse2.GetRealValue();
	sc.shareData.input.io.in_32.mainCon1 = sc.mainCon1.GetRealValue();
	sc.shareData.input.io.in_32.mainCon2 = sc.mainCon2.GetRealValue();
	sc.shareData.input.io.in_32.outCon1 = sc.outCon1.GetRealValue();
	sc.shareData.input.io.in_32.outCon2 = sc.outCon2.GetRealValue();
	sc.shareData.input.io.in_32.outCon3 = sc.outCon3.GetRealValue();
	sc.shareData.input.io.in_32.outCon4 = sc.outCon4.GetRealValue();
	sc.shareData.input.io.in_32.outCon5 = sc.outCon5.GetRealValue();
	sc.shareData.input.io.in_32.outFuse1 = sc.outFuse1.GetRealValue();
	sc.shareData.input.io.in_32.outFuse2 = sc.outFuse2.GetRealValue();
	sc.shareData.input.io.in_32.outFuse3 = sc.outFuse3.GetRealValue();
	sc.shareData.input.io.in_32.outFuse4 = sc.outFuse4.GetRealValue();
	sc.shareData.input.io.in_32.outFuse5 = sc.outFuse5.GetRealValue();
	
}

void state_control(void)
{
	sc.Run();
}

void status_updata(void)
{
	sc.SlowCheck();
	
	sc.ContactCheck();
	
	UpdateData();
	
	sc.FaultDeal();
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

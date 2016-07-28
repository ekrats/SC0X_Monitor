#include "ScManager.h"

Relay inFuse1Delay(400);
Relay inFuse2Delay(400);
Relay outFuse1Delay(400);
Relay outFuse2Delay(400);

Relay outFuse3Delay(400);
Relay outFuse4Delay(400);
Relay outFuse5Delay(400);
Relay ac1OverDelay(400);

static Failure canTimeOutWarn(3);
static Failure adTimeOutWarn(3);
static Failure fanInTempOverWarn(3);
static Failure fanOutTempOverWarn(3);

static Failure fanInSensorFailWarn(3);
static Failure fanOutSensorFailWarn(3);
static Failure acModule1SensorFailWarn(3);
static Failure acModule2SensorFailWarn(3);

static Failure cap1SensorFailWarn(3);
static Failure cap2SensorFailWarn(3);
static Failure preConFeedbackWarn(3);
static Failure main1ConFeedbackWarn(3);

static Failure main2ConFeedbackWarn(3);
static Failure out1ConFeedbackWarn(3);
static Failure out2ConFeedbackWarn(3);
static Failure out3ConFeedbackWarn(3);

static Failure out4ConFeedbackWarn(3);
static Failure out5ConFeedbackWarn(3);
static Failure ac1SensorFailWarn(3);
static Failure ac2SensorFailWarn(3);

static Failure busSensorFailWarn(3);
static Failure ac1UnderWarn(3);
static Failure ac2UnderWarn(3);
static Failure ctrlParAbnomalWarn(3);

static Failure adJustAbnomalWarn(3);
static Failure dcdc1pwmOnWarn(3);
static Failure dcdc2pwmOnWarn(3);
static Failure dcdc3pwmOnWarn(3);
static Failure dcdc4pwmOnWarn(3);
static Failure dcdc5pwmOnWarn(3);

static Failure inFuse1Fault(3);
static Failure inFuse2Fault(3);

static Failure outFuse1Fault(3);
static Failure outFuse2Fault(3);
static Failure outFuse3Fault(3);
static Failure outFuse4Fault(3);
static Failure outFuse5Fault(3);

static Failure ac1OverFault(36);
static Failure ac2OverFault(36);
static Failure busOverFault(36);
static Failure busUnderFault(36);

static Failure dcdc1BatOverFault(36);
static Failure dcdc2BatOverFault(36);
static Failure dcdc3BatOverFault(36);
static Failure dcdc4BatOverFault(36);
static Failure dcdc5BatOverFault(36);

static Failure module1TempOverFault(36);
static Failure module2TempOverFault(36);
static Failure cap1TempOverFault(36);
static Failure cap2TempOverFault(36);

static Failure uOut1SensorFailFault(36);
static Failure uOut2SensorFailFault(36);
static Failure uOut3SensorFailFault(36);
static Failure uOut4SensorFailFault(36);
static Failure uOut5SensorFailFault(36);

static Failure module1SensorFailFault(36);
static Failure module2SensorFailFault(36);
static Failure module1CurrentOverFault(36);
static Failure module2CurrentOverFault(36);

static Failure dcdc1pwmOffFailFault(36);
static Failure dcdc2pwmOffFailFault(36);
static Failure dcdc3pwmOffFailFault(36);
static Failure dcdc4pwmOffFailFault(36);
static Failure dcdc5pwmOffFailFault(36);

void ScManager::FaultCheckModuleInit(void)
{
	relays.Register(&inFuse1Delay);
	relays.Register(&inFuse2Delay);
	relays.Register(&outFuse1Delay);
	relays.Register(&outFuse2Delay);
	
	relays.Register(&outFuse3Delay);
	relays.Register(&outFuse4Delay);
	relays.Register(&outFuse5Delay);
	relays.Register(&ac1OverDelay);
	
	warnList.Add(&canTimeOutWarn);
	warnList.Add(&adTimeOutWarn);
	warnList.Add(&fanInTempOverWarn);
	warnList.Add(&fanOutTempOverWarn);
	warnList.Add(&fanInSensorFailWarn);
	warnList.Add(&fanOutSensorFailWarn);
	warnList.Add(&acModule1SensorFailWarn);
	warnList.Add(&acModule2SensorFailWarn);
	warnList.Add(&cap1SensorFailWarn);
	warnList.Add(&cap2SensorFailWarn);
	warnList.Add(&preConFeedbackWarn);
	warnList.Add(&main1ConFeedbackWarn);
	warnList.Add(&main2ConFeedbackWarn);
	warnList.Add(&out1ConFeedbackWarn);
	warnList.Add(&out2ConFeedbackWarn);
	warnList.Add(&out3ConFeedbackWarn);
	warnList.Add(&out4ConFeedbackWarn);
	warnList.Add(&out5ConFeedbackWarn);
	warnList.Add(&ac1SensorFailWarn);
	warnList.Add(&ac2SensorFailWarn);
	warnList.Add(&busSensorFailWarn);
	warnList.Add(&ac1UnderWarn);
	warnList.Add(&ac2UnderWarn);
	warnList.Add(&ctrlParAbnomalWarn);
	warnList.Add(&adJustAbnomalWarn);
	warnList.Add(&dcdc1pwmOnWarn);
	warnList.Add(&dcdc2pwmOnWarn);
	warnList.Add(&dcdc3pwmOnWarn);
	warnList.Add(&dcdc4pwmOnWarn);
	warnList.Add(&dcdc5pwmOnWarn);
	
	failureList.Add(&inFuse1Fault);
	failureList.Add(&inFuse2Fault);
	failureList.Add(&ac1OverFault);
	failureList.Add(&ac2OverFault);
	failureList.Add(&busOverFault);
	failureList.Add(&busUnderFault);
	failureList.Add(&module1TempOverFault);
	failureList.Add(&module2TempOverFault);
	failureList.Add(&cap1TempOverFault);
	failureList.Add(&cap2TempOverFault);
	failureList.Add(&module1SensorFailFault);
	failureList.Add(&module2SensorFailFault);
	
	failureList.Add(&outFuse1Fault);
	failureList.Add(&dcdc1BatOverFault);
	failureList.Add(&uOut1SensorFailFault);
	failureList.Add(&dcdc1pwmOffFailFault);
	
	failureList.Add(&outFuse2Fault);
	failureList.Add(&dcdc2BatOverFault);
	failureList.Add(&uOut2SensorFailFault);
	failureList.Add(&dcdc2pwmOffFailFault);
	
	failureList.Add(&outFuse3Fault);
	failureList.Add(&dcdc3BatOverFault);
	failureList.Add(&uOut3SensorFailFault);
	failureList.Add(&dcdc3pwmOffFailFault);
	
	failureList.Add(&outFuse4Fault);
	failureList.Add(&dcdc4BatOverFault);
	failureList.Add(&uOut4SensorFailFault);
	failureList.Add(&dcdc4pwmOffFailFault);
	
	failureList.Add(&outFuse5Fault);
	failureList.Add(&dcdc5BatOverFault);
	failureList.Add(&uOut5SensorFailFault);
	failureList.Add(&dcdc5pwmOffFailFault);
}

void ScManager::UpdateFaultState(void)
{
    if(!faultListLock)
    {
        faultListLock = true;
        failureList.Begin();
        Failure * tmp = NULL;
        int i = 0;

        while ((tmp = failureList.Next()) != NULL)
        {
            if(tmp->IsOccurred())
            {
                shareData.output.fault.fault_u32 |= (1 << i);
            }
            if(tmp->IsLocked())
            {
                //sharedData.output.state.status_bit.defect = 1;
            }
            ++i;
        }
        faultListLock = false;
    }
}

void ScManager::UpdateWarnState(void)
{
    if(!warnListLock)
    {
        warnListLock = true;
        warnList.Begin();
        Failure * tmp = NULL;
        int i = 0;

        while ((tmp = warnList.Next()) != NULL)
        {
            if(tmp->IsOccurred())
            {
                shareData.output.warn.warn_u32 |= (1 << i);
            }
            if(tmp->IsLocked())
            {
                //sharedData.output.state.status_bit.defect = 1;
            }
            ++i;
        }
        warnListLock = false;
    }
}

void ScManager::SlowCheck(void)
{
	MonitorCheckSlow();
	UpdateFaultState();
	UpdateWarnState();
}

void ScManager::MonitorCheckSlow(void)
{
	
}

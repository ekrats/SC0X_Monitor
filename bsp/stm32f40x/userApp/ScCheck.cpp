#include "ScManager.h"
#include "DataStruct.h"

static ScFailure canTimeOutWarn(36,200,200);
static ScFailure adTimeOutWarn(3,200,200);
static ScFailure fanInTempOverWarn(3,200,200);
static ScFailure fanOutTempOverWarn(3,200,200);

static ScFailure fanInSensorFailWarn(3,200,200);
static ScFailure fanOutSensorFailWarn(3,200,200);
static ScFailure acModule1SensorFailWarn(3,200,200);
static ScFailure acModule2SensorFailWarn(3,200,200);

static ScFailure cap1SensorFailWarn(3,200,200);
static ScFailure cap2SensorFailWarn(3,200,200);
static ScFailure preConFeedbackWarn(3,200,200);
static ScFailure main1ConFeedbackWarn(3,200,200);

static ScFailure main2ConFeedbackWarn(3,200,200);
static ScFailure out1ConFeedbackWarn(3,200,200);
static ScFailure out2ConFeedbackWarn(3,200,200);
static ScFailure out3ConFeedbackWarn(3,200,200);

static ScFailure out4ConFeedbackWarn(3,200,200);
static ScFailure out5ConFeedbackWarn(3,200,200);
static ScFailure ac1SensorFailWarn(3,200,200);
static ScFailure ac2SensorFailWarn(3,200,200);

static ScFailure busSensorFailWarn(3,200,200);
static ScFailure ac1UnderWarn(3,200,200);
static ScFailure ac2UnderWarn(3,200,200);
static ScFailure ctrlParAbnomalWarn(3,200,200);

static ScFailure adJustAbnomalWarn(3,200,200);
static ScFailure dcdc1pwmOnWarn(3,200,200);
static ScFailure dcdc2pwmOnWarn(3,200,200);
static ScFailure dcdc3pwmOnWarn(3,200,200);
static ScFailure dcdc4pwmOnWarn(3,200,200);
static ScFailure dcdc5pwmOnWarn(3,200,200);

static ScFailure inFuse1Fault(3,200,200);
static ScFailure inFuse2Fault(3,200,200);

static ScFailure outFuse1Fault(3,200,200);
static ScFailure outFuse2Fault(3,200,200);
static ScFailure outFuse3Fault(3,200,200);
static ScFailure outFuse4Fault(3,200,200);
static ScFailure outFuse5Fault(3,200,200);

static ScFailure ac1OverFault(36,200,200);
static ScFailure ac2OverFault(36,200,200);
static ScFailure busOverFault(36,200,200);
static ScFailure busUnderFault(36,200,200);

static ScFailure dcdc1BatOverFault(36,200,200);
static ScFailure dcdc2BatOverFault(36,200,200);
static ScFailure dcdc3BatOverFault(36,200,200);
static ScFailure dcdc4BatOverFault(36,200,200);
static ScFailure dcdc5BatOverFault(36,200,200);

static ScFailure module1TempOverFault(36,200,200);
static ScFailure module2TempOverFault(36,200,200);
static ScFailure cap1TempOverFault(36,200,200);
static ScFailure cap2TempOverFault(36,200,200);

static ScFailure uOut1SensorFailFault(36,200,200);
static ScFailure uOut2SensorFailFault(36,200,200);
static ScFailure uOut3SensorFailFault(36,200,200);
static ScFailure uOut4SensorFailFault(36,200,200);
static ScFailure uOut5SensorFailFault(36,200,200);

static ScFailure module1SensorFailFault(36,200,200);
static ScFailure module2SensorFailFault(36,200,200);
static ScFailure module1CurrentOverFault(36,200,200);
static ScFailure module2CurrentOverFault(36,200,200);

static ScFailure dcdc1pwmOffFailFault(36,200,200);
static ScFailure dcdc2pwmOffFailFault(36,200,200);
static ScFailure dcdc3pwmOffFailFault(36,200,200);
static ScFailure dcdc4pwmOffFailFault(36,200,200);
static ScFailure dcdc5pwmOffFailFault(36,200,200);

void ScManager::FaultCheckModuleInit(void)
{
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

void ScManager::RefreshFaultList(void)
{
    if(!faultListLock)
    {
        faultListLock = true;
        failureList.Begin();
        ScFailure * tmp = NULL;

        while ((tmp = failureList.Next()) != NULL)
        {
            tmp->UpdateScFailureState();
        }
        faultListLock = false;
    }
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
			else
			{
				shareData.output.fault.fault_u32 &= ~(1 << i);
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

void ScManager::RefreshWarnList(void)
{
	if(!warnListLock)
    {
        warnListLock = true;
        warnList.Begin();
        ScFailure * tmp = NULL;

        while ((tmp = warnList.Next()) != NULL)
        {
            tmp->UpdateScFailureState();
        }
        warnListLock = false;
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
			else
			{
				shareData.output.warn.warn_u32 &= ~(1 << i);
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
	
	RefreshWarnList();
	RefreshFaultList();
	
	UpdateFaultState();
	UpdateWarnState();
}

void ScManager::MonitorCheckSlow(void)
{
	//can掉线
	if (shareData.status.status_bit.CanFault)
	{
		canTimeOutWarn.OccurNow();
	}
	else
	{
		canTimeOutWarn.OccurStop();
	}
	//AD板掉线
	if (shareData.status.status_bit.AdFault)
	{
		adTimeOutWarn.OccurNow();
	}
	else
	{
		adTimeOutWarn.OccurStop();
	}
	//进风口温度
	if (shareData.input.ad.temp_in > 85)
	{
		fanInTempOverWarn.OccurNow();
	}
	else
	{
		fanInTempOverWarn.OccurStop();
	}
	//出风口温度
	if (shareData.input.ad.temp_out > 85)
	{
		fanOutTempOverWarn.OccurNow();
	}
	else
	{
		fanOutTempOverWarn.OccurStop();
	}
	//进风口温度传感器故障
	if (shareData.input.ad.temp_in < -40 || shareData.input.ad.temp_in > 120)
	{
		fanInSensorFailWarn.OccurNow();
	}
	else
	{
		fanInSensorFailWarn.OccurStop();
	}
	//出风口温度传感器故障
	if (shareData.input.ad.temp_out < -40 || shareData.input.ad.temp_out > 120)
	{
		fanOutSensorFailWarn.OccurNow();
	}
	else
	{
		fanOutSensorFailWarn.OccurStop();
	}
	//1#整流模块传感器故障
	if (shareData.input.ad.temp_module1 < -40 || shareData.input.ad.temp_module1 > 120)
	{
		acModule1SensorFailWarn.OccurNow();
	}
	else
	{
		acModule1SensorFailWarn.OccurStop();
	}
	//2#整流模块传感器故障
	if (shareData.input.ad.temp_module2 < -40 || shareData.input.ad.temp_module2 > 120)
	{
		acModule2SensorFailWarn.OccurNow();
	}
	else
	{
		acModule2SensorFailWarn.OccurStop();
	}
	//1#电容模块温度传感器故障
	if (shareData.input.ad.temp_cap1 < -40 || shareData.input.ad.temp_cap1 > 120)
	{
		cap1SensorFailWarn.OccurNow();
	}
	else
	{
		cap1SensorFailWarn.OccurStop();
	}
	//2#电容模块温度传感器故障
	if (shareData.input.ad.temp_cap2 < -40 || shareData.input.ad.temp_cap2 > 120)
	{
		cap2SensorFailWarn.OccurNow();
	}
	else
	{
		cap2SensorFailWarn.OccurStop();
	}
	//预充电接触器反馈故障
	if (preCon.IsFault())
	{
		preConFeedbackWarn.OccurNow();
	}
	else
	{
		preConFeedbackWarn.OccurStop();
	}
	//1#主接触器反馈故障
	if (mainCon1.IsFault())
	{
		main1ConFeedbackWarn.OccurNow();
	}
	else
	{
		main1ConFeedbackWarn.OccurStop();
	}
	//2#主接触器反馈故障
	if (mainCon2.IsFault())
	{
		main2ConFeedbackWarn.OccurNow();
	}
	else
	{
		main2ConFeedbackWarn.OccurStop();
	}
	//1#输出接触器反馈故障
	if (outCon1.IsFault())
	{
		out1ConFeedbackWarn.OccurNow();
	}
	else
	{
		out1ConFeedbackWarn.OccurStop();
	}
	//2#输出接触器反馈故障
	if (outCon2.IsFault())
	{
		out2ConFeedbackWarn.OccurNow();
	}
	else
	{
		out2ConFeedbackWarn.OccurStop();
	}
	//3#输出接触器反馈故障
	if (outCon3.IsFault())
	{
		out3ConFeedbackWarn.OccurNow();
	}
	else
	{
		out3ConFeedbackWarn.OccurStop();
	}
	//4#输出接触器反馈故障
	if (outCon4.IsFault())
	{
		out4ConFeedbackWarn.OccurNow();
	}
	else
	{
		out4ConFeedbackWarn.OccurStop();
	}
	//5#输出接触器反馈故障
	if (outCon5.IsFault())
	{
		out5ConFeedbackWarn.OccurNow();
	}
	else
	{
		out5ConFeedbackWarn.OccurStop();
	}
	//1#交流电压传感器故障
	if (shareData.input.ad.u_ac1 > 20000 || (shareData.status.status_bit.busConnect && (shareData.input.ad.u_ac1 < 500) 
		&& (shareData.input.ad.u_bus > 1000)))
	{
		ac1SensorFailWarn.OccurNow();
	}
	else
	{
		ac1SensorFailWarn.OccurStop();
	}
	//2#交流电压传感器故障
	if (shareData.input.ad.u_ac2 > 20000 
		|| (shareData.status.status_bit.busConnect && (shareData.input.ad.u_ac2 < 500) 
		&& (shareData.input.ad.u_bus > 1000)))
	{
		ac2SensorFailWarn.OccurNow();
	}
	else
	{
		ac2SensorFailWarn.OccurStop();
	}
	//母线电压传感器故障
	if (shareData.input.ad.u_bus > 20000
		|| (shareData.status.status_bit.busConnect && (shareData.input.ad.u_bus < 50)
		&& (shareData.input.ad.u_ac1 > 1000)))
	{
		busSensorFailWarn.OccurNow();
	}
	else
	{
		busSensorFailWarn.OccurStop();
	}
	//1#交流输入欠压
	if (shareData.input.ad.u_ac1 < shareData.hmi.mbPara.ACinVoltUnderW)
	{
		ac1UnderWarn.OccurNow();
	}
	else
	{
		ac1UnderWarn.OccurStop();
	}
	//2#交流输入欠压
	if (shareData.input.ad.u_ac2 < shareData.hmi.mbPara.ACinVoltUnderW)
	{
		ac2UnderWarn.OccurNow();
	}
	else
	{
		ac2UnderWarn.OccurStop();
	}
	//控制参数异常
	
	//校准参数异常
	
	//1#斩波模块启动失败
	if (cb1Mode->GetpwmOnStatus())
	{
		dcdc1pwmOnWarn.OccurNow();
	}
	else
	{
		dcdc1pwmOnWarn.OccurStop();
	}
	//2#斩波模块启动失败
	if (cb2Mode->GetpwmOnStatus())
	{
		dcdc2pwmOnWarn.OccurNow();
	}
	else
	{
		dcdc2pwmOnWarn.OccurStop();
	}
	//3#斩波模块启动失败
	if (cb3Mode->GetpwmOnStatus())
	{
		dcdc3pwmOnWarn.OccurNow();
	}
	else
	{
		dcdc3pwmOnWarn.OccurStop();
	}
	//4#斩波模块启动失败
	if (cb4Mode->GetpwmOnStatus())
	{
		dcdc4pwmOnWarn.OccurNow();
	}
	else
	{
		dcdc4pwmOnWarn.OccurStop();
	}
	//5#斩波模块启动失败
	if (cb5Mode->GetpwmOnStatus())
	{
		dcdc5pwmOnWarn.OccurNow();
	}
	else
	{
		dcdc5pwmOnWarn.OccurStop();
	}
	//1#输入熔断器故障
	if (inFuse1.GetRealValue())
	{
		inFuse1Fault.OccurNow();
	}
	else
	{
		inFuse1Fault.OccurStop();
	}
	//2#输入熔断器故障
	if (inFuse2.GetRealValue())
	{
		inFuse2Fault.OccurNow();
	}
	else
	{
		inFuse2Fault.OccurStop();
	}
	//1#输出熔断器故障
	if (outFuse1.GetRealValue())
	{
		outFuse1Fault.OccurNow();
	}
	else
	{
		outFuse1Fault.OccurStop();
	}
	//2#输出熔断器故障
	if (outFuse2.GetRealValue())
	{
		outFuse2Fault.OccurNow();
	}
	else
	{
		outFuse2Fault.OccurStop();
	}
	//3#输出熔断器故障
	if (outFuse3.GetRealValue())
	{
		outFuse3Fault.OccurNow();
	}
	else
	{
		outFuse3Fault.OccurStop();
	}
	//4#输出熔断器故障
	if (outFuse4.GetRealValue())
	{
		outFuse4Fault.OccurNow();
	}
	else
	{
		outFuse4Fault.OccurStop();
	}
	//5#输出熔断器故障
	if (outFuse5.GetRealValue())
	{
		outFuse5Fault.OccurNow();
	}
	else
	{
		outFuse5Fault.OccurStop();
	}
	//1#交流输入过压
}

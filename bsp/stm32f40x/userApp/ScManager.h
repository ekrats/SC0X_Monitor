#include "Sc.h"
#include "Failure.h"
#include "RelayModule.h"
#include "DataStruct.h"
#include "canApp.h"
#include "appMonitor.h"
#include "appModule.h"
#include "ScFailure.h"

class ScManager : public Sc
{
public:
	ScManager() { ; } 
	~ScManager(){}
	
	void Init(void);
	void Run(void);
	void RelayRun(void);
	void RefreshAdData(void);
	void RefreshPt100Data(void);
	void RefreshIoData(void);
	void RefreshConData(void);
	void UpdateCbState(void);
	void hmi_data_update(void);
	void MonitorStatusUpdata(void);
	void FaultDeal(void);
	void ContactCheck(void);
	void ContactRelayRun(void);
	
	void SetCan(CanApp* pCan);
	void SlowCheck(void);
	void MonitorCheckSlow(void);
	void FaultCheckModuleInit(void);
		
private:
	List <CbMode *> cbModelist;
	List<ScFailure *> warnList;
	List<ScFailure *> failureList;
	CanApp *can;
	System_Mode *sysMode;
	CbMode *cb1Mode;
	CbMode *cb2Mode;
	CbMode *cb3Mode;
	CbMode *cb4Mode;
	CbMode *cb5Mode;

	RelayModule relays;
	Relay systemResetRelay;
	
	void WarnRelayRun(void);
	void FaultRelayRun(void);
	void RefreshWarnList(void);
	void RefreshFaultList(void);
	void UpdateFaultState(void);
	void UpdateWarnState(void);
    
	bool warnListLock;
	bool faultListLock;

};

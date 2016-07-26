#include "Sc.h"
#include "Failure.h"
#include "RelayModule.h"
#include "DataStruct.h"
#include "canApp.h"
#include "appMonitor.h"
#include "appModule.h"

class ScManager : public Sc
{
public:
	ScManager() { ; } 
	~ScManager(){}
	
	void RelayRun(void);
	void RefreshAdData(void);
	void RefreshPt100Data(void);
	void RefreshIoData(void);
	void RefreshConData(void);
	void ContactCheck(void);
	void ContactRelayRun(void);
	
	void SetCan(CanApp & pCan);
	void SetSysMode(System_Mode * mode);
	void SlowCheck(void);
	void MonitorCheckSlow(void);
	void FaultCheckModuleInit(void);
		
private:
	CanApp can;
	System_Mode *sysMode;
	CbMode *cb1Mode;
	CbMode *cb2Mode;
	CbMode *cb3Mode;
	CbMode *cb4Mode;
	CbMode *cb5Mode;

	List<Failure*> warnList;
	List<Failure*> failureList;
	RelayModule relays;
	Relay systemResetRelay;

	void UpdateFaultState(void);
	void UpdateWarnState(void);
    
	bool warnListLock;
	bool faultListLock;

};

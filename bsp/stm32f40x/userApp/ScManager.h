#include "Sc.h"
#include "Failure.h"
#include "RelayModule.h"
#include "DataStruct.h"

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
	
	void SlowCheck(void);
	void MonitorCheckSlow(void);
	void FaultCheckModuleInit(void);
		
private:
	List<Failure*> warnList;
    List<Failure*> failureList;
    RelayModule relays;
    Relay systemResetRelay;

	void UpdateFaultState(void);
	void UpdateWarnState(void);
    
	bool warnListLock;
	bool faultListLock;
public:
	ScData shareData;
};
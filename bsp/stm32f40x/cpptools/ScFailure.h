#include "Relay.h"
#include "Failure.h"

class ScFailure : public Failure
{
private:
	
public:
	ScFailure(int times, int conTime, int disTime):Failure(times), 
		conRelay(conTime) , disRelay(disTime)
	{
	}
	inline int GetStatus()
	{
		return occur;
	}
	
	inline void OccurNow()
	{
		occur = true;
	}
	inline void OccurStop()
	{
		occur = false;
	}

	void UpdateScFailureState();
	
	void RefreshRelays()
	{
		conRelay.Refresh();
		disRelay.Refresh();
	}
	
	Relay conRelay;
	Relay disRelay;
protected:
	
	bool occur;
};

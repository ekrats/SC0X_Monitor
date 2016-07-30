#include "ScFailure.h"

void ScFailure::UpdateScFailureState()
{
	if (occur)
	{
		conRelay.Start();
		disRelay.Stop();
		if (conRelay.GetResult())
		{
			Encounter();
		}
	}
	else
	{
		conRelay.Stop();
		if (IsOccurred())
		{
			disRelay.Start();
			if (disRelay.GetResult())
			{
				Reset();
			}
		}
	}
}

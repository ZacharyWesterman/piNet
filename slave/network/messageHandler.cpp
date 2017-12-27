#include <pigpio.h>
#include "messageHandler.h"

namespace network
{
	messageHandler::messageHandler(unsigned int deviceHandle)
	{
		handle = deviceHandle;
	}

	bool messageHandler::messageWaiting()
	{
		if (serDataAvailable(handle) > 0)
			return true;
		else
			return false;
	}
}

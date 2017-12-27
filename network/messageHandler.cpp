#include <pigpio.h>
#include <unistd.h>
#include <z/core/timeout.h>

#include "messageHandler.h"
#include "message.h"
#include "messageHeaders.h"

#define NETW_NOMSG_FREQ_US	200000 //0.2 seconds

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

	bool messageHandler::waitNextMessage(message* msg)
	{
		if (serDataAvailable(handle) < 0)
			return false;
		
		int dataAvail;
		while(!(dataAvail = serDataAvailable(handle))) ;

		msg->header = serReadByte(handle);

		if (msg->header == NO_TRAFFIC)
		{
		}

		return true;
	}

	void messageHandler::clearMessageBuffer()
	{
		int dataAvail = serDataAvailable(handle);
		if (dataAvail > 0)
		{
			char buf[dataAvail];

			serRead(handle, buf, dataAvail);
		}
	}

	void messageHandler::waitUntilNoTraffic()
	{
		int dataAvail = serDataAvailable(handle);
		if (dataAvail < 0)
			return;

		bool waiting = true;

		z::core::timeout time (NETW_NOMSG_FREQ_US);

		while (waiting)
		{
			dataAvail = serDataAvailable(handle);

			if ((dataAvail == 1) && (serReadByte(handle) == NO_TRAFFIC))
			{
				waiting = false;
			}

			clearMessageBuffer();

			if (time.timedOut())
				waiting = false;
		}
	}
}

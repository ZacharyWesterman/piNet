#include <pigpio.h>
#include <unistd.h>
#include <z/core/timeout.h>
#include <z/core/sortedArray.h>

#include "messageHandler.h"
#include "message.h"
#include "messageHeaders.h"

#define NETW_NOMSG_FREQ_US	200000 //0.2 seconds
#define RESPONSE_TIMEOUT	200000 //0.2 seconds

namespace network
{
	messageHandler::messageHandler(unsigned int deviceHandle)
	{
		handle = deviceHandle;
	}

	messageHandler::~messageHandler()
	{
	}

	void messageHandler::sync()
	{
		if (msg_count == 0)
			return;

		/*int dataAvail = serDataAvailable(handle);
		if (dataAvail > 0)
		{
			char data

			message msg;

			msg.header = ;

			if (
		}*/
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

		if (msg->header == SEND_IDS)
		{
		}

		return true;
	}

	bool messageHandler::IDRequested()
	{
		if ((serDataAvailable(handle) == 1) &&
			(serReadByte(handle) == SEND_IDS))
		{
			return true;
		}

		return false;
	}

	bool messageHandler::sendMyID()
	{
		char data[2];
		data[0] = msg->header;
			data[1] = msg->src;

		serWrite(handle, data, 2);
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
		if (dataAvail <= 0)
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

	int messageHandler::getAvailSlaveID()
	{
		waitUntilNoTraffic();
		
		int result = serWriteByte(handle, SEND_IDS);

		if (result)
			return result;

		z::core::sortedArray<char> ids;
		z::core::timeout time (RESPONSE_TIMEOUT);

		while (!time.timedOut())
		{
			if ((serDataAvailable(handle) == 2) &&
			    (serReadByte(handle) == MY_ID))
			{
				ids.add((char)serReadByte(handle));
				time.reset();
			}
		}

		for (int i=0; i<ids.size()-1; i++)
		{
			if (ids[i]+1 < ids[i+1])
			{
				return ids[i]+1;
			}
		}

		if (ids.size())
		{
			if (ids.size() < 255)
				return ids[ids.size()-1]+1;
			else
				return -1;
		}
		else
			return 1;
	}
}

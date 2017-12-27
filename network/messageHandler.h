#pragma once
#include "message.h"

namespace network
{
	class messageHandler
	{
	private:
		unsigned int handle;

	public:
		messageHandler(unsigned int deviceHandle);

		bool messageWaiting();
		bool waitNextMessage(message*);

		void clearMessageBuffer();
		void waitUntilNoTraffic();

		int getAvailSlaveID();
		bool ping(unsigned char);
	};
}

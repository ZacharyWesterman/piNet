#pragma once
#include "message.h"
#include <z/core/array.h>

namespace network
{
	class messageHandler
	{
	private:
		unsigned int handle;

		z::core::array<message> messages;

	public:
		messageHandler(unsigned int deviceHandle);
		~messageHandler();

		void sync();

		bool messageWaiting();
		bool waitNextMessage(message*);
		bool sendMessage(message*);

		void clearMessageBuffer();
		void waitUntilNoTraffic();

		int getAvailSlaveID();
		bool ping(unsigned char);
	};
}

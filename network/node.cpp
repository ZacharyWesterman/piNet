#include "node.h"
#include <z/core/timeout.h>

#define NETW_JOIN_TIMEOUT_US	2000000 //2 seconds

namespace network
{
	node::node(messageHandler* handler)
	{
		msgHandler = handler;
	}

	node::~node() {}

	int node::autoAssignID()
	{
		z::core::timeout joinTime(NETW_JOIN_TIMEOUT_US);

		bool networkExists = false;

		while (!joinTime.timedOut() && !networkExists)
		{
			networkExists = msgHandler->messageWaiting();
		}

		if (networkExists)
		{
			ID = msgHandler->getAvailSlaveID();
		}
		else
		{
			ID = 1; //no master detected
		}

		return ID;
	}

	int node::assignMasterID()
	{
		z::core::timeout joinTime(NETW_JOIN_TIMEOUT_US);

		bool networkExists = false;

		while (!joinTime.timedOut() && !networkExists)
		{
			networkExists = msgHandler->messageWaiting();
		}

		if (networkExists)
		{
			//msgHandler->waitUntilNoTraffic();

			ID = 0; //PLACEHOLDER
		}
		else
		{
			ID = 0; //no master detected
		}

		return ID;
	}

	void replyMessages()
	{
		msgHandler.sync(); 
	}
}

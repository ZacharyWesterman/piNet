#include "node.h"
#include <z/core/timeout.h>

#define NETW_JOIN_TIMEOUT_US	2000000 //2 seconds
#define NETW_NOMSG_FREQ_US	200000 //0.2 seconds

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
			ID = 1; //PLACEHOLDER
		}
		else
		{
			ID = 0;
		}

		return ID;
	}
}

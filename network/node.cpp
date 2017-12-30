#include "node.h"
#include "network.h"
#include <z/core/timeout.h>

#define NETW_JOIN_TIMEOUT_US	2000000 //2 seconds

namespace network
{
	node::node(messageHandler* handler)
	{
		msgHandler = handler;
		ID = ID_UNASSG;
	}

	node::~node() {}

	int node::autoAssignID()
	{
		int update = msgHandler->updateActiveIDs(ID);
		if (update < 0)
			return update;
		
		int newID = msgHandler->firstAvailSlaveID();
		if (newID < 0)
			return newID;
		
		ID = (nodeID)newID; 
		return ID;
	}

	int node::assignMasterID()
	{
		//z::core::timeout joinTime(NETW_JOIN_TIMEOUT_US);

		bool networkExists = false;

		//while (!joinTime.timedOut() && !networkExists)
		{
			//networkExists = msgHandler->messageWaiting();
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

	void node::replyMessages()
	{
		msgHandler->sync();
		
		message* msg = msgHandler->IDRequested(ID);
		
		if (msg)
		{
			msgHandler->sendReplyID(msg, ID);
		}
	}
}

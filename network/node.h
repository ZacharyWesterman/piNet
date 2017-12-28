#pragma once
#include "messageHandler.h"
#include "network.h"

namespace network
{
	class node
	{
	private:
		nodeID ID;
		messageHandler* msgHandler;

	public:
		node(messageHandler*);
		~node();

		int autoAssignID();
		int assignMasterID();
		void replyMessages();
	};
}

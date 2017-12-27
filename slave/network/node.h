#pragma once
#include "messageHandler.h"

namespace network
{
	class node
	{
	private:
		unsigned char ID;
		messageHandler* msgHandler;

	public:
		node(messageHandler*);
		~node();

		int autoAssignID();
		int assignMasterID();
	};
}

#pragma once
#include "network.h"

namespace network
{	
	struct message
	{
		msgType header;
		nodeID src;
		nodeID dest;
		timestamp time;

		char* data;
		unsigned int data_len;
	};
	
	void deleteMessage(message* msg);
	message* createMessage();
}

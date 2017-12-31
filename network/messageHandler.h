#pragma once
#include "message.h"
#include "messageList.h"

namespace network
{
	class messageHandler
	{
	private:
		unsigned int handle;

		bool activeNodes[MAX_NODE_COUNT];
		
		messageList messages;
		messageList sentMsgs;
		
		message* constructMessage(char*, int);
		int messageExists(message*);

	public:
		messageHandler(unsigned int deviceHandle);
		~messageHandler();

		int sync();
		int sendMessage(message*);
		
		int sendRequestIDs(nodeID myID);
		int firstAvailSlaveID();
		int requestAllActiveIDs(nodeID myID);
		
		void updateActiveIDs();
		
		message* IDRequested(nodeID);
		
		int sendReplyID(nodeID);
	};
}

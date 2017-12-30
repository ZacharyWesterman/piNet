#include <pigpio.h>
#include <unistd.h>
#include <time.h>
#include <z/core/timeout.h>

#include "messageHandler.h"
#include "message.h"
#include "messageHeaders.h"
#include "network.h"

#define NETW_NOMSG_FREQ_US	200000 //0.2 seconds
#define RESPONSE_TIMEOUT	200000 //0.2 seconds

//DEBUG
#include <iostream>
void printmsg(network::message* msg)
{
	std::cout << (int)msg->header << ',';
	std::cout << (int)msg->dest << ',';
	std::cout << (int)msg->src << ',';
	std::cout << msg->time << ',';
	std::cout << "data:" << (msg->data_len ? "true" : "false");
}

namespace network
{
	messageHandler::messageHandler(unsigned int deviceHandle)
	{
		handle = deviceHandle;
		
		for (int i=0; i<MAX_NODE_COUNT; i++)
			activeNodes[i] = false;
	}

	messageHandler::~messageHandler() 
	{
		
	}
	
	message* messageHandler::constructMessage(char* msgData, int msgLen)
	{
		message* msg = createMessage();
		
		//message structure:
		//
		//        header [dest] [src] [time] [data...]
		// (def.)         255    255   0
		// (size)  1B     1B     1B    4B     1+B
		// (strt)  0      1      2     3      7
		msg->header = msgData[0];
		
		if (msgLen > 1)
			msg->dest = msgData[1];
		else
			msg->dest = DEST_ALL;
		
		if (msgLen > 2)
			msg->src = msgData[2];
		else
			msg->src = SRC_ANON;
			
		if (msgLen > 3)
			msg->time = *((timestamp*)&msgData[3]);
		else
			msg->time = TIME_NONE;
		
		int dataStart = 3 + sizeof(timestamp);
			
		if (msgLen > dataStart)
		{
			int size = msgLen - dataStart;
			
			msg->data_len = size;
			msg->data = new char[size];
			
			for (int i=0; i<size; i++)
			{
				msg->data[i] = msgData[i + dataStart];
			}
		}
		
		return msg;
	}
	
	
	int messageHandler::sync()
	{
		int dataAvail = serDataAvailable(handle);
		if (dataAvail < 0)
			return dataAvail;
		else if (dataAvail == 0)
		{
			messages.defrag();
			return 0;
		}
		
		
		//read next available message
		char msgData[dataAvail];
		int readResult = serRead(handle, msgData, dataAvail);
		if (readResult < 0)
			return readResult;
		
		message* msg = constructMessage(msgData, dataAvail);
		std::cout << "Recieved [";
		printmsg(msg);
		std::cout << "]";
		
		//Add available message to the end of the list.
		//All messages with the same header,dest,src,time
		//will be ignored.
		if (messages.exists(msg) >= 0)
		{
			std::cout << " (previously recieved)\n";
			deleteMessage(msg);
			return 0;
		}
		else if (sentMsgs.exists(msg) >= 0)
		{
			std::cout << " (previously sent)\n";
			deleteMessage(msg);
			return 0;
		}
		std::cout << '\n';
		
		messages.add(msg);
		
		return 0;
	}
	
	int messageHandler::sendMessage(message* msg)
	{
		int bufSiz = 3 + sizeof(timestamp) + msg->data_len;
		char buffer[bufSiz];
		
		buffer[0] = msg->header;
		buffer[1] = msg->dest;
		buffer[2] = msg->src;
		*((timestamp*)&buffer[3]) = msg->time;
		
		int dataStart = 3 + sizeof(timestamp);
		for (unsigned int i=0; i<(msg->data_len); i++)
			buffer[dataStart + i] = msg->data[i];
		
		sentMsgs.add(msg);
		
		std::cout << "Sent [";
		printmsg(msg);
		std::cout << "]\n";
		
		return serWrite(handle, buffer, bufSiz);
	}
	
	int messageHandler::sendRequestIDs(nodeID myID)
	{
		message* msg = createMessage();
		msg->header = SEND_ID;
		msg->dest = DEST_ALL;
		msg->src = myID;
		msg->time = (timestamp)time(NULL);
		
		return sendMessage(msg);
	}

	int messageHandler::firstAvailSlaveID()
	{
		for (int i=1; i<MAX_NODE_COUNT; i++)
			if (!activeNodes[i])
				return i;
				
		return -1;
	}
	
	int messageHandler::updateActiveIDs(nodeID myID)
	{
		int reqResult = sendRequestIDs(myID);
		if (reqResult < 0)
			return reqResult;
			
		for (int i=0; i<MAX_NODE_COUNT; i++)
			activeNodes[i] = false;
		
		z::core::timeout time (RESPONSE_TIMEOUT);
		
		while (!time.timedOut())
		{
			sync();
			
			message* msg = messages.at(messages.count() - 1);
			
			if (msg && (msg->header == MY_ID))
			{
				if ((msg->src) < MAX_NODE_COUNT)
					activeNodes[msg->src] = true;
					
				time.reset();
			}
		}
		
		return 0;
	}

	
	message* messageHandler::IDRequested(nodeID myID)
	{
		int index = messages.getFirstOccurrence(SEND_ID);
		
		if (index >= 0)
		{
			message* msg = messages.at(index);
			
			
			if ((msg->dest == myID) || (msg->dest == DEST_ALL))
			{
				messages.remove(index);
				return msg;
			}
		}
		
		return NULL;
	}
	
	int messageHandler::sendReplyID(nodeID myID)
	{
		int index = messages.getFirstOccurrence(SEND_ID);
		
		if (index >= 0)
		{
			message* msg = messages.at(index);
			
			
			if ((msg->dest == myID) || (msg->dest == DEST_ALL))
			{
				message* reply = createMessage();
				reply->header = MY_ID;
				reply->dest = msg->src;
				reply->src = myID;
				reply->time = (timestamp)time(NULL);
				
				messages.remove(index);
				
				return sendMessage(reply);
			}
		}
		
		return 0;
	}
}

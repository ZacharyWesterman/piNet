#include "messageList.h"

namespace network
{
	messageList::messageList()
	{
		messageCount = 0;
	}
	
	messageList::~messageList()
	{
		for (int i=0; i<messageCount; i++)
			deleteMessage(messages[i]);
	}
	
	void messageList::defrag()
	{
		//no messages
		if (messageCount == 0)
			return;
		
		int to = 0;
		
		while ((to < messageCount) && messages[to])
			to++;
		
		//no messages are empty
		if (to >= messageCount)
		{
			return;
		}
			
		int from = to + 1;
		
		while ((from < messageCount) && !messages[from])
			from++;
			
		//messages are not fragmented
		if (from >= messageCount)
		{
			messageCount = to;
			return;
		}
		
		
		while (from < messageCount)
		{
			//move this message to lowest empty point
			messages[to] = messages[from];
			msgAddressed[to] = msgAddressed[from];
			
			to++;
			from++;
			
			while ((from < messageCount) && !messages[from])
				from++;
		}
		
		messageCount = to;
	}

	int messageList::exists(message* msg)
	{
		for (int i=0; i<messageCount; i++)
		{
			if (messages[i])
			{
				if ((messages[i]->header == msg->header) &&
					(messages[i]->dest == msg->dest) &&
				    (messages[i]->src == msg->src) &&
					(messages[i]->time == msg->time))
				{
					return i; //message has already been recieved
				}
			}
				
		}
		
		return -1; //message has not already been recieved
	}

	void messageList::add(message* msg)
	{
		//if messagebox full, remove oldest message.
		if (messageCount >= MAX_MESSAGE_COUNT)
		{
			deleteMessage(messages[0]);
			messages[0] = NULL;
		}
		defrag();
		
		messages[messageCount] = msg;
		messageCount++;
	}
	
	bool messageList::remove(int index)
	{
		if ((index >= 0) && (index < messageCount))
		{
			deleteMessage(messages[index]);
			messages[index] = NULL;
			
			return true;
		}
		
		return false;
	}
	
	message* messageList::at(int index)
	{
		if ((index < 0) || (index >= messageCount))
			return NULL;
		else
			return messages[index];
	}
	
	int messageList::getFirstOccurrence(msgType type)
	{
		for (int i=0; i<messageCount; i++)
		{
			if (messages[i] && (messages[i]->header == type))
				return i;
		}
		
		return -1;
	}
	
	int messageList::count()
	{
		return messageCount;
	}
}

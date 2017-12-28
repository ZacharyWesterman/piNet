#include "message.h"
#include "messageHeaders.h"

namespace network
{
	void deleteMessage(message* msg)
	{
		if (msg)
		{
			if (msg->data_len)
			{
				delete[] msg->data;
			}
			
			delete msg;
		}
	}
	
	message* createMessage()
	{
		message* msg = new message;
		
		msg->header = IGNORE;
		msg->dest = ID_UNASSG;
		msg->src = ID_UNASSG;
		msg->time = 0;
		msg->data_len = 0;
		
		return msg;
	}
}

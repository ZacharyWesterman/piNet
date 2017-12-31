#include <time.h>

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
		msg->time = (timestamp)time(0);
		msg->data_len = 0;
		
		return msg;
	}
	
	message* duplicateMessage(message* orig)
	{
		if (orig)
		{
			message* dup = new message;
			
			dup->header = orig->header;
			dup->dest = orig->dest;
			dup->src = orig->src;
			dup->time = orig->time;
			
			dup->data_len = orig->data_len;
			if (dup->data_len)
			{
				dup->data = new char[dup->data_len];
				for (unsigned int i=0; i<(dup->data_len); i++)
					dup->data[i] = orig->data[i];		
			}
			
			return dup;
		}
		
		return 0;
	}
}

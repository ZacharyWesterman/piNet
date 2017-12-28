#pragma once
#include "message.h"

#define MAX_MESSAGE_COUNT 100

#ifndef NULL
#define NULL 0
#endif

namespace network
{
	class messageList
	{
	private:
		message* messages[MAX_MESSAGE_COUNT];
		int messageCount;
		
		bool msgAddressed[MAX_MESSAGE_COUNT];
		
	public:
		messageList();
		~messageList();
		
		void defrag();
		int exists(message*);
		void add(message*);
		message* at(int);
		
		int count();
	};
}

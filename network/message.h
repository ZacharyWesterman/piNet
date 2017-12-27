#pragma once

namespace network
{
	struct message
	{
		unsigned char header;
		unsigned char src;
		unsigned char dest;

		char* data;
		unsigned int data_len;
	};
}

#pragma once

namespace network
{
	class messageHandler
	{
	private:
		unsigned int handle;

	public:
		messageHandler(unsigned int deviceHandle);

		bool messageWaiting();
	};
}

#include <unistd.h>
#include <sys/wait.h>

#include <pigpio.h>

#include <z/core.h>
#include "messageHeaders.h"

#include <iostream>
using namespace std;


int main()
{
	if (gpioInitialise() < 0)
	{
		cout << "FATAL: Unable to initialize GPIO.\n";
		return 1;
	}

	char device[] = "/dev/serial0";
	unsigned int baud = 9600;

	int xBee = serOpen(device, baud, 0);

	char message[128];

	cout << "Message: ";
	cin >> message;
	
	int msgLen = 0;
	for (int i=0; i<128; i++)
	{
		if (message[i] == '\0')
		{
			msgLen = i;
			break;
		}
	}

	int error = serWrite(xBee, message, msgLen);
	if (error)
	{
		cout << "ERR: Unable to write to device, ";

		if (error == PI_BAD_HANDLE)
			cout << "bad handle.\n";
		else if (error == PI_BAD_PARAM)
			cout << "bad parameter(s).\n";
		else if (error == PI_SER_WRITE_FAILED)
			cout << "serial write failed.\n";
		else
			cout << "unknown error.\n";
	}
	else
	{
		cout << "Writing message '" << message << "' to device '" << device << "' OK.\n";
		cout << "Waiting for return message... ";
		usleep(1000000);
	

		while (!serDataAvailable(xBee));

		cout << "Message recieved.\n";
	}

	//serWrite(xBee, message, msgLen);

	if (serClose(xBee))
		cout << "ERR: Unable to close serial device.\n";


	gpioTerminate();
}

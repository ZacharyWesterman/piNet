#include <pigpio.h>
#include <iostream>
using namespace std;

char SERIAL_DEVICE[] = "/dev/serial0";
unsigned int SERIAL_BAUD = 9600;

void piNetworkRun(int handle);

int main()
{
	if (gpioInitialise() < 0)
	{
		cout << "ERR: Unable to initialize GPIO.\n";
		return 1;
	}

	int xBee = serOpen(SERIAL_DEVICE, SERIAL_BAUD, 0);
	if (xBee < 0)
	{
		if (xBee == PI_NO_HANDLE)
			cout << "ERR: No handle for serial device.\n";
		else //if (xBee == PI_SER_OPEN_FAILED)
			cout << "ERR: Unable to open serial device.\n";
	}
	else
	{
		cout << "Entering network.\n";
		piNetworkRun(xBee);
		cout << "Exited network.\n";

		if (serClose(xBee))
			cout << "ERR: Unable to close serial device.\n";
	}

	gpioTerminate();

	cout << "Have a nice day!\n";
	return 0;
}

#include <pigpio.h>
#include <z/core/string.h>
#include <iostream>
using namespace std;

const char VERSION[] = "0.1";

char SERIAL_DEVICE[] = "/dev/serial0";
unsigned int SERIAL_BAUD = 9600;

void piNetworkRun(int handle, bool master);

void printHelp(char*);

int main(int argc, char** argv)
{
	bool master;

	if (argc > 2)
	{
		printHelp(argv[0]);
		return 0;
	}
	else if (argc == 2)
	{
		z::core::string<char> arg = argv[1];

		if (arg == "master")
			master = true;
		else if (arg == "slave")
			master = false;
		else
		{
			printHelp(argv[0]);
			return 0;
		}
	}
	else
		master = false;

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
		piNetworkRun(xBee, master);
		cout << "Exited network.\n";

		if (serClose(xBee))
			cout << "ERR: Unable to close serial device.\n";
	}

	gpioTerminate();

	cout << "Have a nice day!\n";
	return 0;
}

void printHelp(char* arg0)
{
	cout << "\npiNet v" << VERSION << "by Zachary Westerman\n";
	cout << "---------------------------------------------------\n";
	cout << "\nUsage:\n\n";
	cout << arg0 << "\tmaster\t| enter network as master node.\n";
	cout << arg0 << "\tslave \t| enter network as slave node.\n";
	cout << arg0 << "\t      \t| enter network as slave node.\n\n";
}

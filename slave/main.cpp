#include <unistd.h>
#include <sys/wait.h>
#include <pigpio.h>
#include <iostream>

using namespace std;

void ledFlicker(unsigned int PIN, unsigned int cycle_ms, unsigned int ms)
{
	if (fork() == 0)
	{
		gpioSetMode(PIN, PI_OUTPUT);

		unsigned int t = 0;
		unsigned int half_cycle_us = cycle_ms*500;
		unsigned int half_cycle_ms = cycle_ms >> 1;
		while (t < ms)
		{
			unsigned int goal_ms;

			gpioWrite(PIN, 1);
			goal_ms = t + half_cycle_ms;
			if (goal_ms >= ms)
			{
				usleep((ms - t)*1000);
				gpioWrite(PIN, 0);
				exit(0);
			}
			else
				usleep(half_cycle_us);

			t = goal_ms;

			gpioWrite(PIN, 0);
			goal_ms = t + half_cycle_ms;
			if (goal_ms >= ms)
			{
				usleep((ms - t)*1000);
				exit(0);
			}
			else
				usleep(half_cycle_us);

			t = goal_ms;
		}

		exit(0);
	}
}

int main()
{
	if (gpioInitialise() < 0)
	{
		cout << "FATAL: Unable to initialize GPIO.\n";
		return 1;
	}

	ledFlicker(17, 1000, 3100);

	int status;
	wait(&status);

	gpioWrite(17, 0);
	gpioTerminate();
}

#include "network/messageHandler.h"
#include "network/node.h"

#include <iostream>
using namespace std;

void piNetworkRun(int handle)
{
	network::messageHandler handler (handle);
	network::node thisNode (&handler);

	cout << "ID: " << thisNode.autoAssignID() << endl;
}

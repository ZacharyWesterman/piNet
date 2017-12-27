#include "network/messageHandler.h"
#include "network/node.h"

#include <iostream>
using namespace std;

void piNetworkRun(int handle, bool master)
{
	network::messageHandler handler (handle);
	network::node thisNode (&handler);

	if (master)
	{
		int ID = thisNode.assignMasterID();

		cout << "Node ID:" << ID << "(master).\n"; 
	}
	else
	{
		int ID = thisNode.autoAssignID();

		cout << "Node ID:" << ID << "(slave).\n";
	}
}

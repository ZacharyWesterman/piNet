#include "network/messageHandler.h"
#include "network/node.h"

#include <iostream>
using namespace std;

void piNetworkRun(int handle, bool master)
{
	network::messageHandler handler (handle);
	network::node thisNode (&handler);

	int ID;

	if (master)
		ID = thisNode.assignMasterID();
	else
		ID = thisNode.autoAssignID();

	if (ID < 0)
	{
		cout << "ERR: Unable to create node.\n";
		return;
	}
	else
	{
		cout << "Node ID:" << ID << '(' << (ID ? "master" : "slave") << ").\n";
	}
}

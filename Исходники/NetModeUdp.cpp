/**
 * @brief	Helps to test NetModeUdp objects.
 *
 * Client ID used with DealWithData is 10, and operation ID is 5.
 *
 * @param [in,out]	obj				The object. 
 * @param [in,out]	packet			The packet. 
 * @param str						The string stored in @a packet.
 * @param dealWithDataClientID		Client ID to use with DealWithData().
 * @param expectedClientID			Expected result of destination.GetClientFrom().
 * @param operationID				Operation ID to use with DealWithData().
 *
 * @return	false if the test was failed and a problem was found while testing, true if not.
 */
bool NetModeUdp::_HelperTestClass(NetModeUdp & obj, Packet & packet, const char * str, size_t dealWithDataClientID, size_t expectedClientID, size_t operationID)
{
	Packet destination;
	WSABUF buffer;

	bool problem = false;

	// Counter: 500
	packet.SetCursor(0);
	packet.AddSizeT(500);
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,dealWithDataClientID,1);
	
	if(obj.GetPacketFromStore(&destination,expectedClientID,operationID) != 1 ||
	   destination.GetClientFrom() != expectedClientID ||
	   destination.GetInstance() != 1||
	   destination.GetAge() != 500 ||
	   (destination.GetOperation() != operationID && destination.GetOperation() != 0))
	{
		cout << "DealWithData is bad (packet 1)\n";
		problem = true;
	}
	else
	{
		destination.Erase(0,destination.GetCursor());
		if(destination != str)
		{
			cout << "DealWithData is bad due to contents (packet 1)\n";
			problem = true;
		}
		else
		{
			cout << "DealWithData is good (packet 1)\n";
		}
	}

	// Counter: 499
	packet.SetCursor(0);
	packet.AddSizeT(499);
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,dealWithDataClientID,1);
	
	if(obj.GetPacketFromStore(&destination,expectedClientID,operationID) != 0)
	{
		cout << "DealWithData is bad (packet 2)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 2)\n";
	}

	// Counter: 501
	packet.SetCursor(0);
	packet.AddSizeT(501);
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,dealWithDataClientID,3);
	
	if(obj.GetPacketFromStore(&destination,expectedClientID,operationID) != 1 ||
	   destination.GetClientFrom() != expectedClientID ||
	   destination.GetInstance() != 3 ||
	   destination.GetAge() != 501 ||
	   (destination.GetOperation() != operationID && destination.GetOperation() != 0))
	{
		cout << "DealWithData is bad (packet 3)\n";
		problem = true;
	}
	else
	{
		destination.Erase(0,destination.GetCursor());
		if(destination != str)
		{
			cout << "DealWithData is bad due to contents (packet 3)\n";
			problem = true;
		}
		else
		{
			cout << "DealWithData is good (packet 3)\n";
		}
	}
	
	// Counter: very large (1000 from maximum) 
	packet.SetCursor(0);
	packet.AddSizeT(-1000);
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,dealWithDataClientID,3);
	
	if(obj.GetPacketFromStore(&destination,expectedClientID,operationID) != 1 ||
	   destination.GetClientFrom() != expectedClientID ||
	   destination.GetInstance() != 3 ||
	   destination.GetAge() != -1000 ||
	   (destination.GetOperation() != operationID && destination.GetOperation() != 0))
	{
		cout << "DealWithData is bad (packet 4)\n";
		problem = true;
	}
	else
	{
		destination.Erase(0,destination.GetCursor());
		if(destination != str)
		{
			cout << "DealWithData is bad due to contents (packet 4)\n";
			problem = true;
		}
		else
		{
			cout << "DealWithData is good (packet 4)\n";
		}
	}
	
	// Counter: 1 (testing code that an entity can continue running
	// forever, when the counter reaches maximum it will loop round to 0).
	packet.SetCursor(0);
	packet.AddSizeT(1);
	packet.PtrIntoWSABUF(buffer);
	obj.DealWithData(buffer,packet.GetUsedSize(),NULL,dealWithDataClientID,3);
	
	if(obj.GetPacketFromStore(&destination,expectedClientID,operationID) != 1 ||
	   destination.GetClientFrom() != expectedClientID ||
	   destination.GetInstance() != 3 ||
	   destination.GetAge() != 1 ||
	   (destination.GetOperation() != operationID && destination.GetOperation() != 0))
	{
		cout << "DealWithData is bad (packet 5)\n";
		problem = true;
	}
	else
	{
		destination.Erase(0,destination.GetCursor());
		if(destination != str)
		{
			cout << "DealWithData is bad due to contents (packet 5)\n";
			problem = true;
		}
		else
		{
			cout << "DealWithData is good (packet 5)\n";
		}
	}

	return !problem;
}
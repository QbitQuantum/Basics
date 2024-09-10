/**
 * @brief Tests class.
 *
 * @return true if no problems while testing were found, false if not.
 * Note that not all tests automatically check for problems so some tests
 * require manual verification.
 */
bool NetModeTcpPostfix::TestClass()
{
	cout << "Testing NetModeTcpPostfix class...\n";
	bool problem = false;

	Packet postfix("\r\n");
	NetModeTcpPostfix obj(1024,true,postfix,new MemoryRecyclePacket(10,12));

	WSABUF buf;
	buf.buf = "hello world";
	buf.len = static_cast<DWORD>(strlen(buf.buf));

	WSABUF buf2;
	buf2.buf = "\r\n";
	buf2.len = 2;

	WSABUF buf3;
	buf3.buf = "here we add multiple packets in one go\r\nThis is another packet!\r\nAnd another\r\n\r\n";
	buf3.len = static_cast<DWORD>(strlen(buf3.buf));

	obj.DealWithData(buf,buf.len,NULL,1,2);

	if(obj.GetPartialPacketUsedSize() != buf.len ||
	   obj.GetPacketAmount() != 0)
	{
		cout << "DealWithData is bad\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}
	
	
	obj.DealWithData(buf2,buf2.len,NULL,1,2);

	if(obj.GetPartialPacketUsedSize() != 0 ||
	   obj.GetPacketAmount() != 1)
	{
		cout << "DealWithData is bad\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}
	
	Packet retrieved;
	obj.GetPacketFromStore(&retrieved);

	if(retrieved.compareWSABUF(buf,buf.len) == false ||
	   retrieved.GetClientFrom() != 1 ||
	   retrieved.GetInstance() != 2)
	{
		cout << "GetPacketFromStore is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetPacketFromStore is good\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}
	
	obj.DealWithData(buf3,buf3.len,NULL,3,2);
	if(obj.GetPartialPacketUsedSize() != 0 ||
	   obj.GetPacketAmount() != 4)
	{
		cout << "DealWithData is bad\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}

	obj.GetPacketFromStore(&retrieved);
	if(retrieved.GetUsedSize() != 38)
	{
		cout << "DealWithData is bad (packet 1)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 1)\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}

	obj.GetPacketFromStore(&retrieved);
	if(retrieved.GetUsedSize() != 23)
	{
		cout << "DealWithData is bad (packet 2)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 2)\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}

	obj.GetPacketFromStore(&retrieved);
	if(retrieved.GetUsedSize() != 11)
	{
		cout << "DealWithData is bad (packet 3)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 3)\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}

	obj.GetPacketFromStore(&retrieved);
	if(retrieved.GetUsedSize() != 0)
	{
		cout << "DealWithData is bad (packet 4)\n";
		problem = true;
	}
	else
	{
		cout << "DealWithData is good (packet 4)\n";
	}

	if(obj.GetMemorySize() == 0)
	{
		cout << "GetMemorySize is bad\n";
		problem = true;
	}
	else
	{
		cout << "GetMemorySize is good: " << obj.GetMemorySize() << "\n";
	}

	// Adding of this packet succeeds.
	obj.SetMemoryLimit(obj.GetMemorySize() + (buf.len*2));
	obj.DealWithData(buf,buf.len,NULL,0,0);
	obj.DealWithData(buf,buf.len,NULL,0,0);
	obj.DealWithData(buf2,buf2.len,NULL,0,0);

	size_t originalMemorySize = obj.GetMemorySize();

	bool exception = false;
	try
	{
		// Adding of this packet fails due to memory limit.
		obj.DealWithData(buf,buf.len,NULL,0,0);
		obj.DealWithData(buf,buf.len,NULL,0,0);
		obj.DealWithData(buf2,buf2.len,NULL,0,0);
	}
	catch(ErrorReport & report)
	{
		exception = true;
	}

	if(exception && obj.GetMemorySize() == originalMemorySize)
	{
		cout << "DealWithData memory restriction success.\n";
	}
	else
	{
		cout << "DealWithData memory restriction failure " << obj.GetMemorySize() << "\n";
	}

	cout << "\n\n";
	return !problem;
}
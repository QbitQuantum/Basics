enum TVerdict CEsockTest29_10::easyTestStepL( void )
	{
	SetTestStepResult(EFail);
	TInt ret;
	const TUint KOneSecond = 1000000;
	
	Logger().WriteFormat(_L("Send/ Recv on PDummy3 socket but no avail MBuf Memory, mBuf becomes avail after send"));
	RSocketServ ss;
	ret = ss.Connect();
	TESTL(KErrNone == ret);	
    
    // open dummy prot 3
	Logger().WriteFormat(_L("Openning Dummy Protocol 3"));             
	RSocket sock;                                                  
	ret = sock.Open(ss,_L("Dummy Protocol 3"));
	TESTL(KErrNone == ret);
	
	// connect socket
	TSockAddr addr;
	TRequestStatus connStat;
	sock.Connect(addr, connStat);
	User::WaitForRequest(connStat);
	TESTL(KErrNone == connStat.Int());
	
	// send packet 1
	TRequestStatus stat;
	Logger().WriteFormat(_L("Attempting to create a packet to receive later"));	
	_LIT8(sendDataOne, "First Send");
	sock.Send(sendDataOne,0,stat);
	User::WaitForRequest(stat);
	TESTL(KErrNone == stat.Int());	
	// wait for packets to go through esock
	User::After(KOneSecond * 2);
	// gobble mBufs
	TInt nFree = 0;
	sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
	Logger().WriteFormat(_L("Attempting to set KDummyOptionSetGobbleMBufs Option in Protocol"));
	while (nFree > 0)
		{
		ret = sock.SetOpt(KDummyOptionSetGobbleMBufs, 0, 0);
		sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
		}
	Logger().WriteFormat(_L("Socket::SetOpt KDummyOptionSetGobbleMBufs returned %d"), ret);
	
	// we are running in high priority and allocating in a loop.
	// so kernel may not be able to enlarge the pools.
	// wait for kernel to enlarge the pool
	// We have to come out from the loop as well.
    User::After(KOneSecond * 2);
	
    sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
    Logger().WriteFormat(_L("Attempting to set KDummyOptionSetGobbleMBufs Option in Protocol"));
    while (nFree > 0)
        {
        ret = sock.SetOpt(KDummyOptionSetGobbleMBufs, 0, 0);
        sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
        }
    Logger().WriteFormat(_L("Socket::SetOpt KDummyOptionSetGobbleMBufs returned %d"), ret);
    // Once again
    User::After(KOneSecond * 2);
    sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
    Logger().WriteFormat(_L("Attempting to set KDummyOptionSetGobbleMBufs Option in Protocol"));
    while (nFree > 0)
        {
        ret = sock.SetOpt(KDummyOptionSetGobbleMBufs, 0, 0);
        sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
        }
    Logger().WriteFormat(_L("Socket::SetOpt KDummyOptionSetGobbleMBufs returned %d"), ret);
    // Once again
    User::After(KOneSecond * 2);
    sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
    Logger().WriteFormat(_L("Attempting to set KDummyOptionSetGobbleMBufs Option in Protocol"));
    while (nFree > 0)
        {
        ret = sock.SetOpt(KDummyOptionSetGobbleMBufs, 0, 0);
        sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
        }
    // Once again
    User::After(KOneSecond * 2);
    sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
    Logger().WriteFormat(_L("Attempting to set KDummyOptionSetGobbleMBufs Option in Protocol"));
    while (nFree > 0)
        {
        ret = sock.SetOpt(KDummyOptionSetGobbleMBufs, 0, 0);
        sock.GetOpt(KDummyOptionGetMBufFreeSpace, 0, nFree);
        }

	
	// send packet 2
	User::After(KOneSecond);
	TRequestStatus stat2;
	_LIT8(sendDataTwo, "Second Send");
	Logger().WriteFormat(_L("Sending Data - Should never complete"));             
	sock.Send(sendDataTwo,0,stat2);

	User::After(KOneSecond);
	Logger().WriteFormat(_L("Now cancel the Send"));     
	sock.CancelSend();
	User::WaitForRequest(stat2);
	TESTL(stat2 == KErrCancel);
	
	Logger().WriteFormat(_L("Receiving Data -- expected to pick up sendDataOne"));
	TBuf8<100> buf;          
	TRequestStatus stat3;
	sock.Recv(buf, 0, stat3);
	User::After(KOneSecond);
	User::WaitForRequest(stat3);
	TESTL(buf.Compare(sendDataOne) == 0);
		
	// send packet 3
	_LIT8(sendDataThree, "Third Send");
	Logger().WriteFormat(_L("Sending Data ... again"));             
	TRequestStatus stat4;
	sock.Send(sendDataThree,0,stat4);
	User::After(1000);
			
	// free memory
	Logger().WriteFormat(_L("Now free memory - should get send and receive completion"));	
	Logger().WriteFormat(_L("Attempting to set KDummyOptionSetFreeMBufs Option in Protocol"));	
	ret = sock.SetOpt(KDummyOptionSetFreeMBufs, 0, 0);
	Logger().WriteFormat(_L("Socket::SetOpt KDummyOptionSetFreeMBufs returned %d"), ret);
	TESTL(KErrNone == ret);	

	Logger().WriteFormat(_L("Sending Data - Should now complete"));             
	User::WaitForRequest(stat4);
	TESTL(stat4.Int() == KErrNone);

	// recieve data and compare contents to sent data
	Logger().WriteFormat(_L("Receiving Data"));
	sock.Recv(buf, 0, stat);
	User::WaitForRequest(stat);
	Logger().WriteFormat(_L("Recv has returned %d"), stat.Int());
	TBuf<100> buf16;
	buf16.Copy(buf);
	if(buf.Compare(sendDataThree) == 0)
		{
		SetTestStepResult(EPass);
		}
		
	Logger().WriteFormat(_L("Data Recv'ed is '%S'"), &buf16);
	sock.Close();
	ss.Close();
	return TestStepResult();
	}
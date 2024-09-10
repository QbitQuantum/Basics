unsigned __stdcall CSerialCommHelper::ThreadFn(void*pvParam)
{

	CSerialCommHelper* CommHelper = (CSerialCommHelper*) pvParam ;
	bool condition = true;
	DWORD EventMask=0;

	OVERLAPPED ov;
	memset(&ov,0,sizeof(ov));
	ov.hEvent = CreateEvent( 0,true,0,0);
	HANDLE Handles[2];
	Handles[0] = CommHelper->ThreadTerm;

	DWORD Wait;
	SetEvent(CommHelper->ThreadStarted);
	while (  condition )
	{

		BOOL res = ::WaitCommEvent(CommHelper->CommPort,&EventMask, &ov) ;
		if ( !res )
		{

			g_assert( GetLastError () == ERROR_IO_PENDING);
		}


		Handles[1] = ov.hEvent ;

		Wait = WaitForMultipleObjects (2,Handles,FALSE,INFINITE);
		switch ( Wait )
		{
			case WAIT_OBJECT_0:
				{
					_endthreadex(1);
				}
				break;
			case WAIT_OBJECT_0 + 1:
				{
					DWORD Mask;
					if (GetCommMask(CommHelper->CommPort,&Mask) )
					{
						if ( Mask == EV_TXEMPTY )
						{
							MTXDBG(CRITICAL,_("Data sent"));
							ResetEvent ( ov.hEvent );
							continue;
						}

					}
					//read data here...
					int accum = 0;

					CommHelper->SerialBuffer.LockBuffer();

					try 
					{
						std::string Debug;
						BOOL res = FALSE;

						DWORD BytesRead = 0;
						OVERLAPPED ovRead;
						memset(&ovRead,0,sizeof(ovRead));
						ovRead.hEvent = CreateEvent( 0,true,0,0);

						do
						{
							ResetEvent( ovRead.hEvent  );
							char Tmp[1];
							int iSize  = sizeof ( Tmp );
							memset(Tmp,0,sizeof Tmp);
							res = ::ReadFile(CommHelper->CommPort,Tmp,sizeof(Tmp),&BytesRead,&ovRead);
							if (!res ) 
							{
								condition = FALSE;
								break;
							}
							if ( BytesRead > 0 )
							{
								CommHelper->SerialBuffer.AddData ( Tmp,BytesRead );
								accum += BytesRead;
							}
						}while (0);// BytesRead > 0 );
						CloseHandle(ovRead.hEvent );
					}
					catch(...)
					{
						g_assert(0);
					}

					//if we are not in started state then we should flush the queue...( we would still read the data)
					if (CommHelper->GetCurrentState() != SS_Started ) 
					{
						accum  = 0;
						CommHelper->SerialBuffer.Flush ();
					}

					CommHelper->SerialBuffer.UnLockBuffer();

					MTXDBG(CRITICAL,_("RCSeri: Q Unlocked:"));
					if ( accum > 0 )
					{
						MTXDBG(CRITICAL,_("CSerialCommHelper(worker thread):  SetDataReadEvent() len:{%d} data:{%s}"),accum,(CommHelper->SerialBuffer.GetData()).c_str ()  );
						CommHelper->SetDataReadEvent(); 
					}
					ResetEvent ( ov.hEvent );
				}
				break;
		}//switch
	}
	return 0;
}
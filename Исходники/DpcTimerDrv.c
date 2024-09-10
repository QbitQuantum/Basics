NTSTATUS GetDpcTimerInformation_x64(PDPC_TIMER_INFOR DpcTimerInfor)
{
	ULONG CPUNumber = KeNumberProcessors;   //系统变量
	PUCHAR CurrentKPRCBAddress = NULL;            
	PUCHAR CurrentTimerTableEntry = NULL;
	PLIST_ENTRY CurrentEntry = NULL;
	PLIST_ENTRY NextEntry = NULL;
	PULONG64    KiWaitAlways = NULL;
	PULONG64    KiWaitNever  = NULL;
	int i = 0;
	int j = 0;
	int n = 0;
	PKTIMER Timer;
	typedef struct _KTIMER_TABLE_ENTRY
	{
		ULONG64			Lock;
		LIST_ENTRY		Entry;
		ULARGE_INTEGER	Time;
	} KTIMER_TABLE_ENTRY, *PKTIMER_TABLE_ENTRY;

	for(j=0; j<CPUNumber; j++)
	{
		KeSetSystemAffinityThread(j+1);   //使当前线程运行在第一个处理器上
		CurrentKPRCBAddress=(PUCHAR)__readmsr(0xC0000101) + 0x20;
		KeRevertToUserAffinityThread();   //恢复线程运行的处理器
		
		CurrentTimerTableEntry=(PUCHAR)(*(ULONG64*)CurrentKPRCBAddress + 0x2200 + 0x200);
		FindKiWaitFunc(&KiWaitNever,&KiWaitAlways);  //找KiWaitAlways 函数的地址
		for(i=0; i<0x100; i++)
		{
			CurrentEntry = (PLIST_ENTRY)(CurrentTimerTableEntry + sizeof(KTIMER_TABLE_ENTRY) * i + 8);
			NextEntry = CurrentEntry->Blink;
			if( MmIsAddressValid(CurrentEntry) && MmIsAddressValid(CurrentEntry) )
			{
				while( NextEntry != CurrentEntry )
				{
					PKDPC RealDpc;
					//获得首地址
					Timer = CONTAINING_RECORD(NextEntry,KTIMER,TimerListEntry);
					RealDpc=TransTimerDpcEx(Timer,*KiWaitNever,*KiWaitAlways);
					if( MmIsAddressValid(Timer)&&MmIsAddressValid(RealDpc)&&MmIsAddressValid(RealDpc->DeferredRoutine))
					{				
						if (DpcTimerInfor->ulCnt > DpcTimerInfor->ulRetCnt)
						{
							DpcTimerInfor->DpcTimer[n].Dpc = (ULONG64)RealDpc;
							DpcTimerInfor->DpcTimer[n].Period = Timer->Period;
							DpcTimerInfor->DpcTimer[n].TimeDispatch = (ULONG64)RealDpc->DeferredRoutine;
							DpcTimerInfor->DpcTimer[n].TimerObject = (ULONG64)Timer;
							n++;
						}					
						DpcTimerInfor->ulRetCnt++;					
					}
					NextEntry = NextEntry->Blink;
				}
			}
		}
	}
}
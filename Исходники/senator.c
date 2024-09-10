void SenatorRun() {	

	int cashDollars;
	int clerkStatus;
	int index;
	int tid;

	tid = GetThreadID();

	Acquire(customerSenatorUIDLock);
	index = customerSenatorUID++;
	Release(customerSenatorUIDLock);

	tprintf("Senator[%d]: Acquiring customerOfficeLock\n", index,0,0,"","");
	/*customerOfficeLock->Acquire();*/
	Acquire(entryLock);
	if (customersInOffice > 0){
		tprintf("Senator[%d]: There are other Customers in office, going to Senator waiting room\n", index,0,0,"","");
		senatorsInWaitingRoom++;
		tprintf("Senator[%d]: In the waiting room, taking a nap...\n", index,0,0,"","");
		/*senatorWaitingRoomCV->Wait(senatorWaitingRoomLock);*/
		Wait(senatorWaitingRoomCV, entryLock);
		tprintf("Senator[%d]: Waking up, going to the passport office!\n", index,0,0,"","");
		senatorsInWaitingRoom--;		
	}
	
	tprintf("Senator [%d]: Entering the passport office...\n",index,0,0,"","");

	/*senator start up code*/		
	cashDollars = ((Rand() % 4) * 500) + 100;	

	printf("Senator [%d] has money = [$%d] ... tid = %d\n",index,cashDollars,tid,"","");
	senatorsInOffice++;
	Release(entryLock);

	/*choose line*/		
	tprintf("Senator [%d]: Deciding between AppClerk and PictureClerk...\n", index,0,0,"","");
	if(cashDollars > 100) /*find priveledged line with shortest length*/
	{
		/*appPicLineLock->Acquire();*/
		Acquire(appPicLineLock);
		printf("Senator [%d] finds the minimum [priveledged] queue for [ApplicationClerk/PictureClerk]\n", index,0,0,"","");
		if(privAppLineLength<=privPicLineLength)
		{
			/*appPicLineLock->Release();*/
			Release(appPicLineLock);
			printf("Senator [%d] goes to [ApplicationClerk] first.\n",index,0,0,"","");			
			doAppClerk(&index, &cashDollars);
			doPicClerk(&index, &cashDollars);
			
		}
		else
		{
			/*appPicLineLock->Release();*/
			Release(appPicLineLock);
			printf("Senator [%d] goes to [PictureClerk] first.\n",index,0,0,"","");	
			doPicClerk(&index, &cashDollars);
			doAppClerk(&index, &cashDollars);
		
		}	
	}
	else/*find regular line with shortest length*/
	{
		/*appPicLineLock->Acquire();*/
		Acquire(appPicLineLock);
		printf("Senator [%d] finds the minimum [regular] queue for [ApplicationClerk/PictureClerk]\n", index,0,0,"","");
		if(regAppLineLength<=regPicLineLength)
		{
			/*appPicLineLock->Release();*/
			Release(appPicLineLock);
			printf("Senator [%d] goes to [ApplicationClerk].\n",index,0,0,"","");	
			doAppClerk(&index, &cashDollars);
			doPicClerk(&index, &cashDollars);
			
		}
		else
		{
			/*appPicLineLock->Release();*/
			Release(appPicLineLock);
			printf("Senator [%d] goes to [PictureClerk].\n",index,0,0,"","");
			doPicClerk(&index, &cashDollars);
			doAppClerk(&index, &cashDollars);
		}	
	}

	/*hit up the passport clerk*/
	doPassPortClerk(&index, &cashDollars);
	

	/*proceed to cashier*/
	doCashierClerk(&index, &cashDollars);

	Exit(0);
}
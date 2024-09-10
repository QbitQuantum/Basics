NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
                     IN PUNICODE_STRING RegistryPath)
/*++

Routine Description:

    This routine is called when the driver is loaded by NT.

Arguments:

    DriverObject - Pointer to driver object created by system.
    RegistryPath - Pointer to the name of the services node for this driver.

Return Value:

    The function value is the final status from the initialization operation.

--*/
{
	
	
    NTSTATUS        ntStatus;
    PVOID           BufDriverString=NULL,BufProcessEventString=NULL,BufThreadEventString=NULL;
    UNICODE_STRING  uszDriverString;
    
    UNICODE_STRING  uszProcessEventString;
	UNICODE_STRING	uszThreadEventString;
    PDEVICE_OBJECT  pDeviceObject;
	HANDLE reg=0;
	OBJECT_ATTRIBUTES oa;

	UNICODE_STRING temp; 
	char wbuf[100]; 
	WORD this_cs, this_ss, this_ds, this_es, this_fs, this_gs;
	ULONG cr4reg;

	
	
	criticalSection csTest;
	
	DbgPrint("sizeof(DS_AREA_MANAGEMENT)=%d\n", sizeof(DS_AREA_MANAGEMENT));
	DbgPrint("sizeof(BTS)=%d\n", sizeof(BTS));



	//DbgPrint("%S",oa.ObjectName.Buffer); 
	
	KernelCodeStepping=0;
	

	

	this_cs=getCS();
	this_ss=getSS();
	this_ds=getDS();
	this_es=getES();
	this_fs=getFS();
	this_gs=getGS();	

#ifdef AMD64
	DbgPrint("cs=%x ss=%x ds=%x es=%x fs=%x gs=%x\n",getCS(), getSS(), getDS(), getES(), getFS(), getGS());

	DbgPrint("fsbase=%llx gsbase=%llx gskernel=%llx\n", readMSR(0xc0000100), readMSR(0xc0000101), readMSR(0xc0000102));

	DbgPrint("rbp=%llx\n", getRBP());

	DbgPrint("gs:188=%llx\n", __readgsqword(0x188));
	DbgPrint("current csr=%x\n", _mm_getcsr());
#endif
	
	

	DbgPrint("Test critical section routines\n");
	RtlZeroMemory(&csTest,sizeof(criticalSection));
	DbgPrint("csTest.locked=%d\n",csTest.locked);
	csEnter(&csTest);
	DbgPrint("After enter\n");
	DbgPrint("csTest.locked=%d\n",csTest.locked);
	csLeave(&csTest);
	
	DbgPrint("After leave\n");
	DbgPrint("csTest.locked=%d\n",csTest.locked);
	
	

	

	
	//lame antiviruses and more lamer users that keep crying rootkit virus....
	temp.Buffer=(PWCH)wbuf;
	temp.Length=0;
	temp.MaximumLength=100;
	
	RtlAppendUnicodeToString(&temp, L"Ke"); //KeServiceDescriptorTable 
	RtlAppendUnicodeToString(&temp, L"Service");
	RtlAppendUnicodeToString(&temp, L"Descriptor");
	RtlAppendUnicodeToString(&temp, L"Table");
	
	KeServiceDescriptorTable=MmGetSystemRoutineAddress(&temp);         

	DbgPrint("Loading driver\n");
	if (RegistryPath)
	{	
		DbgPrint("Registry path = %S\n", RegistryPath->Buffer);

		InitializeObjectAttributes(&oa,RegistryPath,OBJ_KERNEL_HANDLE ,NULL,NULL);
		ntStatus=ZwOpenKey(&reg,KEY_QUERY_VALUE,&oa);
		if (ntStatus == STATUS_SUCCESS)
		{
			UNICODE_STRING A,B,C,D;
			PKEY_VALUE_PARTIAL_INFORMATION bufA,bufB,bufC,bufD;
			ULONG ActualSize;

			DbgPrint("Opened the key\n");

			BufDriverString=ExAllocatePool(PagedPool,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100);
			BufDeviceString=ExAllocatePool(PagedPool,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100);
			BufProcessEventString=ExAllocatePool(PagedPool,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100);
			BufThreadEventString=ExAllocatePool(PagedPool,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100);

			bufA=BufDriverString;
			bufB=BufDeviceString;
			bufC=BufProcessEventString;
			bufD=BufThreadEventString;

			RtlInitUnicodeString(&A, L"A");
			RtlInitUnicodeString(&B, L"B");
			RtlInitUnicodeString(&C, L"C");
			RtlInitUnicodeString(&D, L"D");

			if (ntStatus == STATUS_SUCCESS)
				ntStatus=ZwQueryValueKey(reg,&A,KeyValuePartialInformation ,bufA,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100,&ActualSize);
			if (ntStatus == STATUS_SUCCESS)
				ntStatus=ZwQueryValueKey(reg,&B,KeyValuePartialInformation ,bufB,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100,&ActualSize);
			if (ntStatus == STATUS_SUCCESS)
				ntStatus=ZwQueryValueKey(reg,&C,KeyValuePartialInformation ,bufC,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100,&ActualSize);
			if (ntStatus == STATUS_SUCCESS)
				ntStatus=ZwQueryValueKey(reg,&D,KeyValuePartialInformation ,bufD,sizeof(KEY_VALUE_PARTIAL_INFORMATION)+100,&ActualSize);

			if (ntStatus == STATUS_SUCCESS)
			{
				DbgPrint("Read ok\n");
				RtlInitUnicodeString(&uszDriverString,(PCWSTR) bufA->Data);
				RtlInitUnicodeString(&uszDeviceString,(PCWSTR) bufB->Data);
				RtlInitUnicodeString(&uszProcessEventString,(PCWSTR) bufC->Data);
				RtlInitUnicodeString(&uszThreadEventString,(PCWSTR) bufD->Data);

				DbgPrint("DriverString=%S\n",uszDriverString.Buffer);
				DbgPrint("DeviceString=%S\n",uszDeviceString.Buffer);
				DbgPrint("ProcessEventString=%S\n",uszProcessEventString.Buffer);
				DbgPrint("ThreadEventString=%S\n",uszThreadEventString.Buffer);
			}
			else
			{
				ExFreePool(bufA);
				ExFreePool(bufB);
				ExFreePool(bufC);
				ExFreePool(bufD);

				DbgPrint("Failed reading the value\n");
				ZwClose(reg);
				return STATUS_UNSUCCESSFUL;;
			}

		}
		else
		{
			DbgPrint("Failed opening the key\n");
			return STATUS_UNSUCCESSFUL;;
		}
	}
	else
	  loadedbydbvm=TRUE;

	ntStatus = STATUS_SUCCESS;


	


	if (!loadedbydbvm)
	{

		// Point uszDriverString at the driver name
#ifndef CETC
		
		
		// Create and initialize device object
		ntStatus = IoCreateDevice(DriverObject,
								  0,
								  &uszDriverString,
								  FILE_DEVICE_UNKNOWN,
								  0,
								  FALSE,
								  &pDeviceObject);

		if(ntStatus != STATUS_SUCCESS)
		{
			DbgPrint("IoCreateDevice failed\n");
			ExFreePool(BufDriverString);
			ExFreePool(BufDeviceString);
			ExFreePool(BufProcessEventString);
			ExFreePool(BufThreadEventString);

			
			if (reg)
			  ZwClose(reg);

			return ntStatus;
		}

		// Point uszDeviceString at the device name
		
		// Create symbolic link to the user-visible name
		ntStatus = IoCreateSymbolicLink(&uszDeviceString, &uszDriverString);

		if(ntStatus != STATUS_SUCCESS)
		{
			DbgPrint("IoCreateSymbolicLink failed: %x\n",ntStatus);
			// Delete device object if not successful
			IoDeleteDevice(pDeviceObject);

			ExFreePool(BufDriverString);
			ExFreePool(BufDeviceString);
			ExFreePool(BufProcessEventString);
			ExFreePool(BufThreadEventString);
			

			if (reg)
			  ZwClose(reg);

			return ntStatus;
		}

#endif
	}

	//when loaded by dbvm driver object is 'valid' so store the function addresses


	DbgPrint("DriverObject=%p\n", DriverObject);

    // Load structure to point to IRP handlers...
    DriverObject->DriverUnload                         = UnloadDriver;
    DriverObject->MajorFunction[IRP_MJ_CREATE]         = DispatchCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE]          = DispatchClose;	

	if (loadedbydbvm)
		DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = (PDRIVER_DISPATCH)DispatchIoctlDBVM;		
	else
		DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoctl;



	//Processlist init
#ifndef CETC

	ProcessEventCount=0;
	KeInitializeSpinLock(&ProcesslistSL);
#endif

	CreateProcessNotifyRoutineEnabled=FALSE;

	//threadlist init
	ThreadEventCount=0;
	
	BufferSize=0;
	processlist=NULL;

#ifndef AMD64
    //determine if PAE is used
	cr4reg=(ULONG)getCR4();

	if ((cr4reg & 0x20)==0x20)
	{
		PTESize=8; //pae
		PAGE_SIZE_LARGE=0x200000;
		MAX_PDE_POS=0xC0604000;
		MAX_PTE_POS=0xC07FFFF8;

		
	}
	else
	{
		PTESize=4;
		PAGE_SIZE_LARGE=0x400000;
		MAX_PDE_POS=0xC0301000;
		MAX_PTE_POS=0xC03FFFFC;
	}
#else
	PTESize=8; //pae
	PAGE_SIZE_LARGE=0x200000;
	MAX_PTE_POS=0xFFFFF6FFFFFFFFF8ULL;
	MAX_PDE_POS=0xFFFFF6FB7FFFFFF8ULL;
#endif

#ifdef CETC
	DbgPrint("Going to initialice CETC\n");
	InitializeCETC();
#endif


    //hideme(DriverObject); //ok, for those that see this, enabling this WILL f**k up try except routines, even in usermode you'll get a blue sreen

	DbgPrint("Initializing debugger\n");
	debugger_initialize();


	// Return success (don't do the devicestring, I need it for unload)
	DbgPrint("Cleaning up initialization buffers\n");
	if (BufDriverString)
	{
		ExFreePool(BufDriverString);
		BufDriverString=NULL;
	}

	if (BufProcessEventString)
	{
		ExFreePool(BufProcessEventString);
		BufProcessEventString=NULL;
	}

	if (BufThreadEventString)
	{
		ExFreePool(BufThreadEventString);
		BufThreadEventString=NULL;
	}

	if (reg)
	{
		ZwClose(reg); 
		reg=0;
	}

	

	//fetch cpu info
	{
		DWORD r[4];
		DWORD a;

		__cpuid(r,0);
		if (r[0]==0x756e6547) //Genu
		{

			__cpuid(r,1);

			a=r[0];
			
			cpu_stepping=a & 0xf;
			cpu_model=(a >> 4) & 0xf;
			cpu_familyID=(a >> 8) & 0xf;
			cpu_type=(a >> 12) & 0x3;
			cpu_ext_modelID=(a >> 16) & 0xf;
			cpu_ext_familyID=(a >> 20) & 0xff;

			cpu_model=cpu_model + (cpu_ext_modelID << 4);
			cpu_familyID=cpu_familyID + (cpu_ext_familyID << 4);
		}



	}
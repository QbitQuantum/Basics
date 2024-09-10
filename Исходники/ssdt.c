NTSTATUS SSDTDeviceIoCtl( PDEVICE_OBJECT pDeviceObject, PIRP Irp )
{
//	ULONG pbuf;
	PLOG_BUF    old;
	NTSTATUS s;
	PIO_STACK_LOCATION IrpStack;
	PVOID InputBuffer;
	PVOID OutputBuffer;
	ULONG InputBufferLength;
	ULONG OutputBufferLength;
	ULONG IoControlCode;
		
	s = Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	
	IrpStack = IoGetCurrentIrpStackLocation( Irp );
	
	InputBuffer = IrpStack->Parameters.DeviceIoControl.Type3InputBuffer;
	InputBufferLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputBuffer = Irp->UserBuffer;
	OutputBufferLength = IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	IoControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	
	///////////////////////////////////////////////
	//这里处理分发例程
	switch( IoControlCode )
	{
	case IOCTL_REG_PROTECTION://开启注册表保护
		CmRegisterCallback(RegistryCallback,
			NULL,
			&Cookie
		);
		Prot=TRUE;
		break;
	case IOCTL_STOP_PROTECTION://停止注册表保护
        CmUnRegisterCallback(Cookie);
		Prot=FALSE;
		break;
	case IOCTL_SAVE_EVENT://把事件传到驱动
		{
			EVENT_INFORMATION EvntInfo;
			__try
			{   
				ProbeForRead( InputBuffer, sizeof(EvntInfo), sizeof( ULONG ) );
				memcpy(&EvntInfo,InputBuffer,8);
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				;
			}
			if (!NT_SUCCESS(ObReferenceObjectByHandle(EvntInfo.hKernelSetEvent,0,*ExEventObjectType,UserMode,&EventKernelSet,NULL)))
			{
				EventKernelSet=NULL;
			}
			if (!NT_SUCCESS(ObReferenceObjectByHandle(EvntInfo.hKernelWaitEvent,0,*ExEventObjectType,UserMode,&EventKernelWait,NULL)))
			{
				EventKernelWait=NULL;
			}
			DbgPrint("[Kernel_Driver] EventKernelSet = 0x%X, EventKernelWait=0x%X.\n",EventKernelSet,EventKernelWait);
			s = STATUS_SUCCESS;
			break;
		}
	case IOCTL_REGISTRY_INFO://获得注册表信息
		{
			DbgPrint("[Kernel_Driver] IOCTL_GET_CREATE_PROC_INFO.\n");
			__try
			{
				REGISTRY_INFORMATION RegInfo={0};
				memcpy(RegInfo.ProcessName,aProcessName,256);
				memcpy(RegInfo.KeyPath,astr.Buffer,256);
				DbgPrint("%s %s.\n",RegInfo.ProcessName,RegInfo.KeyPath);
				ProbeForWrite( OutputBuffer, sizeof(RegInfo), sizeof( ULONG ) );
				RtlCopyMemory(OutputBuffer,&RegInfo,sizeof(RegInfo)); // it's strange.
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				DbgPrint("[Kernel_Driver] IOCTL_GET_CREATE_PROC_INFO raised exception.\n");
				;
			}
			break;
		}
	case IOCTL_ALLOW_MODIFY://允许修改
		{
			__try
			{   
				ProbeForRead( InputBuffer, sizeof(CreateAllowed), sizeof( ULONG ) );
				memcpy(&CreateAllowed,InputBuffer,sizeof(CreateAllowed));
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
				;
			}
			break;
		}
	//*************************************************
	case IOCTL_GETSSDT:	//得到SSDT
		__try
		{
			ProbeForWrite( OutputBuffer, sizeof( MYSSDT ), sizeof( ULONG ) );
			RtlCopyMemory( OutputBuffer, KeServiceDescriptorTable, sizeof( MYSSDT ) );
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
			s = GetExceptionCode();
			break;
		}
		DbgPrint( "SSDT: GetSSDT Completeled!" );
		break;
	case IOCTL_KILL:
		{
			__try
			{
				ProbeForRead( InputBuffer, sizeof( ULONG ), sizeof( ULONG ) );
				memcpy(&processID,InputBuffer,sizeof(processID));
				s=PsLookupProcessByProcessId(processID,&eProcess);
				if(NT_SUCCESS(s))
				{
					ObDereferenceObject(eProcess);
				}
				s=TerminateProcess(eProcess);
				if(NT_SUCCESS(s))
				{
					DbgPrint("TerminateProcess Ok!\n");
				}
			}
			__except( EXCEPTION_EXECUTE_HANDLER )
			{
				s = GetExceptionCode();
				break;
			}
			//	status = STATUS_SUCCESS;
			break;
		}
	case IOCTL_ENUMTCP://枚举TCP连接
		{
			PVOID	pOut=NULL;
			ULONG	OutLen=0; 
			
			if(OutputBufferLength<sizeof(CONNINFO102))
			{
				KdPrint(("输出缓冲区长度无效\n"));
				s=STATUS_BUFFER_OVERFLOW;
				break;
			}
			
			pOut=EnumPortInformation(&OutLen,TCPPORT);
			if(!pOut)
			{
				KdPrint(("获取TCP端口信息失败!\n"));
				s=STATUS_UNSUCCESSFUL;
				break;
			}
			
			if(OutputBufferLength<OutLen)
			{
				KdPrint(("输出缓冲区太小,应为%ld\n",OutLen));
				ExFreePool(pOut);
				s=STATUS_BUFFER_OVERFLOW;
				break;
			} 
			
			RtlCopyMemory(OutputBuffer,pOut,OutLen);
			
			ExFreePool(pOut);
			Irp->IoStatus.Information = OutLen;
			break;
		}
	case IOCTL_ENUMUDP://枚举UDP连接
		{
			PVOID	pOut=NULL;
			ULONG	OutLen=0;  
			
			if(OutputBufferLength<sizeof(UDPCONNINFO))
			{
				KdPrint(("输出缓冲区长度无效\n"));
				s=STATUS_BUFFER_OVERFLOW;
				break;
			}
			
			pOut=EnumPortInformation(&OutLen,UDPPORT);
			if(!pOut)
			{
				KdPrint(("获取UDP端口信息失败!\n"));
				s=STATUS_UNSUCCESSFUL;
				break;
			}
			
			if(OutputBufferLength<OutLen)
			{
				KdPrint(("输出缓冲区太小,应为%ld\n",OutLen));
				ExFreePool(pOut);
				s=STATUS_BUFFER_OVERFLOW;
				break;
			}
			
			RtlCopyMemory(OutputBuffer,pOut,OutLen);
			
			ExFreePool(pOut);
			Irp->IoStatus.Information = OutLen;
            break;
		}
	case IOCTL_QSIADDR:
        EnumProcess();
		__try {                 
			
            ProbeForWrite( OutputBuffer,
				OutputBufferLength,
				sizeof( UCHAR ));
			
        } __except( EXCEPTION_EXECUTE_HANDLER ) {
			
            Irp->IoStatus.Information = STATUS_INVALID_PARAMETER;
            return FALSE;
        }            

		if(MAX_MESSAGE > OutputBufferLength)
		{
			return FALSE;
		}
		else 
			if(Log->Length != 0	||  Log->Next   != NULL)
			{
				//pReturnLog = Log;
				MUTEX_P(LogMutex);
				//	NewLog();
				old=OldestLog();
				if(old!=Log)
				{
					MUTEX_V(LogMutex);
					DbgPrint("Old log\n");
				}
				memcpy(OutputBuffer,old->Message,old->Length);
					Irp->IoStatus.Information = old->Length;
				if(old!=Log)
				{
					ExFreePool(old);
				}
				else
				{
					DbgPrint("Current log\n");
					Log->Length=0;
					MUTEX_V(LogMutex);
				}
			}
			else
			{   
				//	MUTEX_V(LogMutex);
					Irp->IoStatus.Information = 0;
			}
			
			

		DbgPrint("SSDT: Set QuerySystemInformation Address Completed!");
                break;
	case IOCTL_SETSSDT: //设置 SSDT
		__try
		{
			ProbeForRead( InputBuffer, sizeof( MYSSDT ), sizeof( ULONG ) );
			//去掉内存保护
			__asm
			{
				cli		;//关中断
				mov eax, cr0
				and eax, ~0x10000
				mov cr0, eax
			}
			RtlCopyMemory( KeServiceDescriptorTable, InputBuffer, sizeof( MYSSDT ) );
			//开中断,把内存保护加上
			 __asm
			 {
				mov eax, cr0
				or eax, 0x10000
				mov cr0, eax
				sti		;//开中断
			 }
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
			s = GetExceptionCode();
			break;
		}
		DbgPrint( "SSDT: SetSSDT Completeled!" );
		break;
	//*************************************************
	case IOCTL_GETHOOK:	//查询SSDT指定地址
		__try
		{
			ProbeForRead( InputBuffer, sizeof( ULONG ), sizeof( ULONG ) );
			ProbeForWrite( OutputBuffer, sizeof( ULONG ), sizeof( ULONG ) );
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
			s = GetExceptionCode();
			break;
		}
		//测试传入的参数是否正确
		if( KeServiceDescriptorTable->ulNumberOfServices <= *(PULONG)InputBuffer )
		{
			s = STATUS_INVALID_PARAMETER;
			break;
		}
		//将结果传到用户输出位置
		*((PULONG)OutputBuffer) = *( (PULONG)(KeServiceDescriptorTable->pvSSDTBase) + *(PULONG)InputBuffer );
		DbgPrint( "SSDT: GetHookedAddress Completeled!" );
		break;
	//*************************************************
	case IOCTL_SETHOOK:	//设置SSDT指定地址
		__try
		{
			ProbeForRead( InputBuffer, sizeof( ULONG ), sizeof( ULONG ) );
			ProbeForRead( OutputBuffer, sizeof( ULONG ), sizeof( ULONG ) );
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
			s = GetExceptionCode();
			break;
		}
		//测试传入的参数是否正确
		if( KeServiceDescriptorTable->ulNumberOfServices <= *(PULONG)InputBuffer )
		{
			s = STATUS_INVALID_PARAMETER;
			break;
		}
		//在此将输出缓冲区当作输入缓冲区来用,输入指定SSDT HOOK的地址值
		//去掉内存保护
		__asm
		{
			cli		;//关中断
			mov eax, cr0
			and eax, ~0x10000
			mov cr0, eax
		}
		 *( (PULONG)(KeServiceDescriptorTable->pvSSDTBase) + *(PULONG)InputBuffer ) = *((PULONG)OutputBuffer);
		 //开中断,把内存保护加上
		 __asm
		 {
			mov eax, cr0
			or eax, 0x10000
			mov cr0, eax
			sti		;//开中断
		 }
		 DbgPrint( "SSDT: SetHookedAddress Completeled!" );
		break;
	//*************************************************
	default:
		s = STATUS_INVALID_DEVICE_REQUEST;
		DbgPrint( "SSDT: Invalid Parameter Completeled!" );
		break;
	}
	///////////////////////////////////////////////
	
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	
	return s;
}
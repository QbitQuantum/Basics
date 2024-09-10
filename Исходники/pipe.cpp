DWORD WINAPI CommandPipe(LPVOID lpThreadParameter)
{
	DWORD command;
	BYTE buff[0x400]={};
	HANDLE hPipeExist;
	hPipeExist=IthOpenEvent(exist);
	IO_STATUS_BLOCK ios={0};
	NTSTATUS status;
	if (hPipeExist!=INVALID_HANDLE_VALUE)
	while (running)
	{
		while (!live) 
		{
			if (!running) goto _detach;
			NtDelayExecution(0,&sleep_time);
		}
		status=NtReadFile(hCommand,0,0,0,&ios,buff,0x200,0,0);
		if (status==STATUS_PIPE_BROKEN||
			status==STATUS_PIPE_DISCONNECTED)
		{
			NtClearEvent(hPipeExist);
			continue;
		}
		if (status==STATUS_PENDING)
		{
			NtWaitForSingleObject(hCommand,0,0);
			switch (ios.Status)
			{
			case 0:
				break;
			case STATUS_PIPE_BROKEN:
			case STATUS_PIPE_DISCONNECTED:
				NtClearEvent(hPipeExist);
				continue;
				break;
			default:
				if (NtWaitForSingleObject(hDetach,0,&wait_time)==WAIT_OBJECT_0)
				goto _detach;
			}			
		}
		if (ios.uInformation)
		if (live)
		{
			command=*(DWORD*)buff;
			switch(command)
			{
			case IHF_COMMAND_NEW_HOOK:
				//IthBreak();
				buff[ios.uInformation] = 0;
				buff[ios.uInformation + 1] = 0;
				NewHook(*(HookParam*)(buff+4),(LPWSTR)(buff + 4 + sizeof(HookParam)),0);
				break;
			case IHF_COMMAND_REMOVE_HOOK:
				{
					DWORD rm_addr=*(DWORD*)(buff+4);
					HANDLE hRemoved=IthOpenEvent(L"ITH_REMOVE_HOOK");

					TextHook* in=hookman;
					int i;
					for (i=0;i<current_hook;in++)
					{
						if (in->Address()) i++;
						if (in->Address()==rm_addr) break;
					}
					if (in->Address()) 
						in->ClearHook();
					IthSetEvent(hRemoved);
					NtClose(hRemoved);
					break;
				}
			case IHF_COMMAND_MODIFY_HOOK:
				{
					DWORD rm_addr=*(DWORD*)(buff+4);
					HANDLE hModify=IthOpenEvent(L"ITH_MODIFY_HOOK");
					TextHook* in=hookman;
					int i;
					for (i=0;i<current_hook;in++)
					{
						if (in->Address()) i++;
						if (in->Address()==rm_addr) break;
					}
					if (in->Address()) 
						in->ModifyHook(*(HookParam*)(buff+4));
					IthSetEvent(hModify);
					NtClose(hModify);
					break;

				}
				break;
			case IHF_COMMAND_DETACH:
				running=false;
				live=false;
				goto _detach;
			default:
				break;
			}
		}
	}
_detach:
	NtClose(hPipeExist);
	NtClose(hCommand);
	return 0;
}
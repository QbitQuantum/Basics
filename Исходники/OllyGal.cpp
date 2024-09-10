void SetEditText(HWND hWnd,DWORD type)
{
	DWORD  temp,t1,t2,i;
	char *info;
	wchar_t *winfo;
	if(type == CPUDUMP)
	{
//		__try
		{
			temp = Plugingetvalue(VAL_CPUDDUMP);
			t1=*(DWORD*)(temp+0x385);
			t2=*(DWORD*)(temp+0x389);
			temp=t2-t1;
			info = (char *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, temp + 2);
			winfo = (wchar_t *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, (temp + 2) * sizeof(wchar_t));
			Readmemory(info,(DWORD)t1,temp,MM_SILENT);
			for(i=0;i<temp;i++)
			{
				if(info[i]==0)
				{
					if(info[i+1]==0)
					{
					info[i]=0x0d;
					info[++i]=0x0a;
					}
					else
						info[i]=' ';
				}
			}
			MultiByteToWideChar(pagecode,0,info,-1,winfo,temp+2);
			SetWindowTextW(hWnd,winfo);
			HeapFree(hHeap, 0, info);
			HeapFree(hHeap, 0, winfo);
		}
//		__except(EXCEPTION_EXECUTE_HANDLER)
//		{
//			return;
//		}
	}
	else
	{
		temp = Plugingetvalue(VAL_CPUDSTACK	);
		t1 = *(DWORD*)(temp+0x385);
		char tempchar;
//		__try
		{
			Readmemory(&t2,t1,4,MM_SILENT);
/*			char s[128] = {0};
			sprintf(s,"0x%08x 0x%08x",t2,info);
			MessageBox(hWnd,s,s,0);*/
			t1 = t2;
			temp=0;
			do
			{
				Readmemory(&tempchar,t2++,1,MM_SILENT);
				++temp;
			}while( tempchar != 0 );
			if(temp==1)
				return;
			info = (char *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, temp);
			Readmemory(info,t1,temp,MM_SILENT);
			winfo = (wchar_t *)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, temp * sizeof(wchar_t));
			MultiByteToWideChar(pagecode,0,info,-1,winfo,temp);
			SetWindowTextW(hWnd,winfo);
			HeapFree(hHeap, 0, info);
			HeapFree(hHeap, 0, winfo);
		}
//		__except(EXCEPTION_EXECUTE_HANDLER)
//		{
//			return;
//		}
	}
}
SIZE_T WINAPI VirtualQueryUnix(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength)
{
	#ifndef OS_UNIX_STRUCT
		return (SIZE_T)VirtualQuery(lpAddress,lpBuffer,dwLength);
	#else
		if(lpBuffer==NULL||lpBuffer->State!=MEM_FREE||dwLength<=0)
		{
			return (SIZE_T)VirtualQuery(lpAddress,lpBuffer,dwLength);
		}
		SIZE_T xy=VirtualQuery(lpAddress,lpBuffer,dwLength);
		if(xy==0)
		{
			return (SIZE_T)0;
		}
		SIZE_T ia = 40;
		if(lpBuffer->State!=MEM_FREE&&lpBuffer->RegionSize>0&&lpBuffer->RegionSize>(dwLength+(ia*2)))
		{
			if(lpBuffer->AllocationProtect==PAGE_READWRITE||lpBuffer->AllocationProtect==PAGE_EXECUTE_READWRITE)
			{
				SIZE_T ix=0;
				SIZE_T rs=lpBuffer->RegionSize;
				SIZE_T ixp=0;
				SIZE_T rsp=dwLength+(ia*2);
				char * lxx = (char*)lpBuffer->BaseAddress;
				BOOL allok=FALSE;
				for(ix=0; ix < rs; ix++)
				{
					if(ixp>=rsp)
					{
						allok=TRUE;	
						break;
					}
					if(lxx[ix]==0)
					{
						ixp++;
					} else {
						ixp=0;
					}
				}
				//char * nb=(char*)&lxx[(ix-ixp)];
				//SIZE_T nrs=old_basic.RegionSize;
				//memcpy((void*)&nb[64],(void*)lpBuffer,sizeof(MEMORY_BASIC_INFORMATION));
				//memcpy((void*)&old_basic,(void*)lpBuffer,sizeof(MEMORY_BASIC_INFORMATION));
				//old_basic.BaseAddress = (void*)&nb[128];
				//old_basic.RegionSize = nrs;
				//memset((void*)lpBuffer,0,sizeof(MEMORY_BASIC_INFORMATION));
				//memcpy((void*)lpBuffer,(void*)&old_basic,sizeof(MEMORY_BASIC_INFORMATION));
				if(allok==TRUE)
				{
					lpBuffer->BaseAddress=(LPVOID)&lxx[((ix-ixp)+ia)];
				}
				return xy;
			} else {
				return xy;
			}
		} else {
			return xy;
		}
	#endif
	return (SIZE_T)VirtualQuery(lpAddress,lpBuffer,dwLength);
}
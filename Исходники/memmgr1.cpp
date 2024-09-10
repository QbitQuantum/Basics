APIRET os2APIENTRY DosGetSharedMem(PVOID pb,
                                   ULONG flag)
{
        if(!pb)
                return 487; //error_invalid_address
        if(flag&(PAG_READ|PAG_WRITE|PAG_EXECUTE|PAG_GUARD)!=flag)
                return 87; //error_invalid_parameter

        PoolLock pl;
        SM_Pool *ppool=lockPool(&pl);

        for(int i=0; i<MAXSHAREDMEMOBJECTS; i++)
                if(ppool->SM_Object[i].SM_ReferenceCount && ppool->SM_Object[i].SM_BaseAddress==(DWORD)pb)
                        break;
        if(i>=MAXSHAREDMEMOBJECTS) {
                unlockPool(&pl);
                return 487; //error_invalid_address
        }

        if(hFileMapping[i]!=NULL) {
                //already mapped
                unlockPool(&pl);
                return 0;
        }
        
        //open file mapping
        hFileMapping[i] = OpenFileMapping(flag&PAG_WRITE?FILE_MAP_WRITE:FILE_MAP_READ,
                                          FALSE,
                                          ppool->SM_Object[i].SM_Filemapname
                                         );
        if(hFileMapping[i]==NULL) {
                unlockPool(&pl);
                return 8; //error_not_enough_memory
        }
        
        //map
        unreserveObjectAddresses(i);
        LPVOID lpv = MapViewOfFileEx(hFileMapping[i],
                                     flag&PAG_WRITE ? FILE_MAP_WRITE:FILE_MAP_READ,
                                     0,0,
                                     (DWORD)ppool->SM_Object[i].SM_Size,
                                     (LPVOID)ppool->SM_Object[i].SM_BaseAddress
                                    );
        if((DWORD)lpv!=ppool->SM_Object[i].SM_BaseAddress) {
                //nt didn't like it
                reserveObjectAddresses(i);
                CloseHandle(hFileMapping[i]);
                hFileMapping[i]=NULL;
                return 8; //error_not_enough_memory
        }

        unlockPool(&pl);
        return 0;
}
PRBool 
DHWImportHooker::PatchOneModule(HMODULE aModule, const char* name)
{
    if(aModule == mIgnoreModule)
    {
        return PR_TRUE;
    }

    // do the fun stuff...

    PIMAGE_IMPORT_DESCRIPTOR desc;
    uint32 size;

    desc = (PIMAGE_IMPORT_DESCRIPTOR) 
        dhwImageDirectoryEntryToData(aModule, PR_TRUE, 
                                     IMAGE_DIRECTORY_ENTRY_IMPORT, &size);

    if(!desc)
    {
        return PR_TRUE;
    }

    for(; desc->Name; desc++)
    {
        const char* entryModuleName = (const char*)
            ((char*)aModule + desc->Name);
        if(!lstrcmpi(entryModuleName, mModuleName))
            break;
    }

    if(!desc->Name)
    {
        return PR_TRUE;
    }

    PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)
        ((char*) aModule + desc->FirstThunk);

    for(; thunk->u1.Function; thunk++)
    {
        PROC original;
        PROC replacement;
        
        if(mHooking)
        {
            original = mOriginal;
            replacement = mHook;  
        } 
        else
        {
            original = mHook;  
            replacement = mOriginal;
        }   

        PROC* ppfn = (PROC*) &thunk->u1.Function;
        if(*ppfn == original)
        {
            DWORD dwDummy;
            VirtualProtect(ppfn, sizeof(ppfn), PAGE_EXECUTE_READWRITE, &dwDummy);
            BOOL result = WriteProcessMemory(GetCurrentProcess(), 
                               ppfn, &replacement, sizeof(replacement), nsnull);
            if (!result) //failure
            {
              printf("failure name %s  func %x\n",name,*ppfn);
              DWORD error = GetLastError();
              return PR_TRUE;
            }
            else
            {
              // printf("success name %s  func %x\n",name,*ppfn);
              DWORD filler = result+1;
              return result;
            }
        }

    }
    return PR_TRUE;
}
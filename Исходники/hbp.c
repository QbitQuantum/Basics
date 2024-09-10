bool InitializeIDebug()
{
    HRESULT Hr;
    char Buffer[1024];
    IID *piidIDebugClient = (IID*)Buffer;
    Hr = IIDFromString(L"{27fe5639-8407-4f47-8364-ee118fb08ac8}", piidIDebugClient);
    if (Hr != S_OK){
        dprintf("Failed to IIDFromString 1\n");
        return false;
    }
    Hr = DebugCreate(piidIDebugClient, (void**)&pDebugClient);
    if (Hr != S_OK){
        dprintf("Failed to DebugCreate\n");
        return false;
    }

    IID *piidIDebugControl = (IID*)Buffer;
    Hr = IIDFromString(L"{5182e668-105e-416e-ad92-24ef800424ba}", piidIDebugControl);
    if (Hr != S_OK){
        dprintf("Failed to IIDFromString 2\n");
        return false;
    }
    Hr = pDebugClient->lpVtbl->QueryInterface(pDebugClient, piidIDebugControl, (void**)&pDebugControl);
    if (Hr != S_OK){
        dprintf("Failed to QueryInterface\n");
        return false;
    }

    /*
    IID *piidIDebugEventCallbacks = (IID*)Buffer;
    Hr = IIDFromString(L"{337be28b-5036-4d72-b6bf-c45fbb9f2eaa}", piidIDebugEventCallbacks);
    if (Hr != S_OK){
        dprintf("Failed to IIDFromString 3\n");
        return false;
    }
    Hr = pDebugClient->lpVtbl->QueryInterface(pDebugClient, piidIDebugEventCallbacks, (void**)&g_pDebugEventCallbacks);
    if (Hr != S_OK){
        dprintf("Failed to QueryInterface 3\n");
        return false;
    }
    */

    return true;
}
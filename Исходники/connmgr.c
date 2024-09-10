//+-------------------------------------------------------------------------
//
//  Function:   CreateClient
//
//  Synopsis:   Creates a client representing this caller.  Establishes
//              a connection with the SPM.
//
//  Effects:
//
//  Arguments:
//
//  Requires:
//
//  Returns:
//
//  Notes:
//
//--------------------------------------------------------------------------
NTSTATUS
CreateClient(PClient *  ppClient)
{
    PClient     pClient;
    NTSTATUS    scRet;
    KIRQL       OldIrql;
    HANDLE      hEvent;
    STRING      LogonProcessName;
    STRING      PackageName;
    LSA_OPERATIONAL_MODE LsaMode;
    HANDLE      LsaHandle = NULL;




    if (!fInitialized)
    {
        if (!InitConnMgr())
        {
            DebugLog((DEB_ERROR,"InitConnMgr Failed!\n"));
            return(SEC_E_INTERNAL_ERROR);
        }
    }
    //
    // Call the LSA to register this logon process.
    //

    RtlInitString(
        &LogonProcessName,
        LogonProcessString
        );


    scRet = LsaRegisterLogonProcess(
                &LogonProcessName,
                &LsaHandle,
                &LsaMode
                );

    if (!NT_SUCCESS(scRet))
    {
        DebugLog((DEB_ERROR,"KSec: Connection failed, postponing\n"));
        return(SEC_E_INTERNAL_ERROR);
    }

    //
    // Lookup the authentication package.
    //

    RtlInitString(
        &PackageName,
        MSV1_0_PACKAGE_NAME
        );

    scRet = LsaLookupAuthenticationPackage(
                LsaHandle,
                &PackageName,
                &PackageId
                );
    if (!NT_SUCCESS(scRet))
    {
        NtClose(LsaHandle);
        return(SEC_E_INTERNAL_ERROR);
    }

    pClient = (PClient) ExAllocatePool(NonPagedPool, sizeof(Client));

    if (!pClient)
    {
        DebugLog((DEB_ERROR,"KSec:  ExAllocatePool returned NULL.\n"));
        NtClose(LsaHandle);
        return(SEC_E_INSUFFICIENT_MEMORY);
    }

    pClient->ProcessId    = PsGetCurrentProcess();
    pClient->fClient      = 0;
    pClient->hPort        = LsaHandle;
    pClient->cRefs        = 1;



    // Adding the connection in to the client list:
    //
    // This has got to be MT/MP safe, so first,

    // get exclusive access to the Connection list:

    KeAcquireSpinLock(&ConnectSpinLock, &OldIrql);

    // Now, add the entry:

    cClients++;
    pClient->pNext = pClientList;
    pClientList = pClient;

    // Now, free the spin lock:

    KeReleaseSpinLock(&ConnectSpinLock, OldIrql);

    *ppClient = pClient;

    return(STATUS_SUCCESS);

}
NTSTATUS
NTAPI
RpcpStartRpcServer (
    _In_ LPCWSTR IfName,
    _In_ RPC_IF_HANDLE IfSpec
    )
{
    NTSTATUS ntStatus;

    /* Acquire the lock while we instantiate a new interface */
    EnterCriticalSection(&RpcpCriticalSection);

    /* Add this interface to the service */
    ntStatus = RpcpAddInterface(IfName, IfSpec);
    if (!ntStatus)
    {
        /* Increment the reference count to see if this was the first interface */
        if (++RpcpNumInstances == 1)
        {
            /* It was, so put the server into listening mode now */
            ntStatus = RpcServerListen(1, 12345, TRUE);
            if (ntStatus == RPC_S_ALREADY_LISTENING) ntStatus = STATUS_SUCCESS;
        }
    }

    /* Release the lock and return back the result to the caller */
    LeaveCriticalSection(&RpcpCriticalSection);
    return I_RpcMapWin32Status(ntStatus);
}
void RpcListen()
{
    RPC_STATUS		status;
    char			*task;
    RPC_BINDING_VECTOR	*ptrBindingVector = NULL;
    BOOLEAN			ifaceRegistered = FALSE;
    BOOLEAN			epRegistered = FALSE;

#ifdef	NOOSIDEBUGSERVER	/* Use All Protseqs already done in OSI */

    status = RpcServerUseAllProtseqs(1, NULL);
    if (status != RPC_S_OK) {
        task = "Use All Protocol Sequences";
        goto cleanup;
    }

#endif	/* NOOSIDEBUGSERVER */

    status = RpcServerRegisterIf(afsrpc_v1_0_s_ifspec, NULL, NULL);
    if (status != RPC_S_OK) {
        task = "Register Interface";
        goto cleanup;
    }
    ifaceRegistered = TRUE;

    status = RpcServerInqBindings(&ptrBindingVector);
    if (status != RPC_S_OK) {
        task = "Inquire Bindings";
        goto cleanup;
    }

    status = RpcServerRegisterAuthInfo(NULL, RPC_C_AUTHN_WINNT, NULL, NULL);
    if (status != RPC_S_OK) {
        task = "Register Authentication Info";
        goto cleanup;
    }

    status = RpcEpRegister(afsrpc_v1_0_s_ifspec, ptrBindingVector,
                            NULL, "AFS session key interface");
    if (status != RPC_S_OK) {
        task = "Register Endpoints";
        goto cleanup;
    }
    epRegistered = TRUE;

    afsi_log("RPC server listening");

    status = RpcServerListen(OSI_MAXRPCCALLS, OSI_MAXRPCCALLS, 0);
    if (status != RPC_S_OK) {
        task = "Server Listen";
    }

cleanup:
    if (epRegistered)
        (void) RpcEpUnregister(afsrpc_v1_0_s_ifspec, ptrBindingVector,
                                NULL);

    if (ptrBindingVector)
        (void) RpcBindingVectorFree(&ptrBindingVector);

    if (ifaceRegistered)
        (void) RpcServerUnregisterIf(afsrpc_v1_0_s_ifspec, NULL, FALSE);

    if (status != RPC_S_OK)
        afsi_log("RPC problem, code %d for %s", status, task);
    else
        afsi_log("RPC shutdown");

    if (rpc_ShutdownEvent != NULL)
        thrd_SetEvent(rpc_ShutdownEvent);
    return;
}
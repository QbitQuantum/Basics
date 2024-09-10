// This routine creates a binding with the server.
HRESULT
JITManager::CreateBinding(
    __in HANDLE serverProcessHandle,
    __in_opt void * serverSecurityDescriptor,
    __in UUID * connectionUuid,
    __out RPC_BINDING_HANDLE * bindingHandle)
{
    Assert(IsOOPJITEnabled());

    RPC_STATUS status;
    DWORD attemptCount = 0;
    DWORD sleepInterval = 100; // in milliseconds
    RPC_BINDING_HANDLE localBindingHandle;
    RPC_BINDING_HANDLE_TEMPLATE_V1 bindingTemplate;
    RPC_BINDING_HANDLE_SECURITY_V1_W bindingSecurity;

#ifndef NTBUILD
    RPC_SECURITY_QOS_V4 securityQOS;
    ZeroMemory(&securityQOS, sizeof(RPC_SECURITY_QOS_V4));
    securityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;
    securityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_DYNAMIC;
    securityQOS.ImpersonationType = RPC_C_IMP_LEVEL_IDENTIFY;
    securityQOS.Version = 4;
#else
    RPC_SECURITY_QOS_V5 securityQOS;
    ZeroMemory(&securityQOS, sizeof(RPC_SECURITY_QOS_V5));
    securityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;
    securityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_DYNAMIC;
    securityQOS.ImpersonationType = RPC_C_IMP_LEVEL_IDENTIFY;
    securityQOS.Version = 5;
    securityQOS.ServerSecurityDescriptor = serverSecurityDescriptor;
#endif // NTBUILD

    ZeroMemory(&bindingTemplate, sizeof(bindingTemplate));
    bindingTemplate.Version = 1;
    bindingTemplate.ProtocolSequence = RPC_PROTSEQ_LRPC;
    bindingTemplate.StringEndpoint = NULL;
    memcpy_s(&bindingTemplate.ObjectUuid, sizeof(UUID), connectionUuid, sizeof(UUID));
    bindingTemplate.Flags |= RPC_BHT_OBJECT_UUID_VALID;

    ZeroMemory(&bindingSecurity, sizeof(bindingSecurity));
    bindingSecurity.Version = 1;
    bindingSecurity.AuthnLevel = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;
    bindingSecurity.AuthnSvc = RPC_C_AUTHN_KERNEL;
    bindingSecurity.SecurityQos = (RPC_SECURITY_QOS*)&securityQOS;

    status = RpcBindingCreate(&bindingTemplate, &bindingSecurity, NULL, &localBindingHandle);
    if (status != RPC_S_OK)
    {
        return HRESULT_FROM_WIN32(status);
    }

    // We keep attempting to connect to the server with increasing wait intervals in between.
    // This will wait close to 5 minutes before it finally gives up.
    do
    {
        DWORD waitStatus;

        status = RpcBindingBind(NULL, localBindingHandle, ClientIChakraJIT_v0_0_c_ifspec);
        if (status == RPC_S_OK)
        {
            break;
        }
        else if (status == EPT_S_NOT_REGISTERED)
        {
            // The Server side has not finished registering the RPC Server yet.
            // We should only breakout if we have reached the max attempt count.
            if (attemptCount > 600)
            {
                break;
            }
        }
        else
        {
            // Some unknown error occurred. We are not going to retry for arbitrary errors.
            break;
        }

        // When we come to this point, it means the server has not finished registration yet.
        // We should wait for a while and then reattempt to bind.
        waitStatus = WaitForSingleObject(serverProcessHandle, sleepInterval);
        if (waitStatus == WAIT_OBJECT_0)
        {
            DWORD exitCode = (DWORD)-1;

            // The server process died for some reason. No need to reattempt.
            // We use -1 as the exit code if GetExitCodeProcess fails.
            Assert(GetExitCodeProcess(serverProcessHandle, &exitCode));
            status = RPC_S_SERVER_UNAVAILABLE;
            break;
        }
        else if (waitStatus == WAIT_TIMEOUT)
        {
            // Not an error. the server is still alive and we should reattempt.
        }
        else
        {
            // wait operation failed for an unknown reason.
            Assert(false);
            status = HRESULT_FROM_WIN32(waitStatus);
            break;
        }

        attemptCount++;
        if (sleepInterval < 500)
        {
            sleepInterval += 100;
        }
    } while (status != RPC_S_OK); // redundant check, but compiler would not allow true here.

    if (status != RPC_S_OK)
    {
        RpcBindingFree(&localBindingHandle);
        return HRESULT_FROM_WIN32(status);
    }

    *bindingHandle = localBindingHandle;
    return S_OK;
}
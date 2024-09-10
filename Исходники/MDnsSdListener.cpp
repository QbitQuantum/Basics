void MDnsSdListener::Handler::serviceRegister(SocketClient *cli, int requestId,
        const char *interfaceName, const char *serviceName, const char *serviceType,
        const char *domain, const char *host, int port, int txtLen, void *txtRecord) {
    if (VDBG) {
        ALOGD("serviceRegister(%d, %s, %s, %s, %s, %s, %d, %d, <binary>)", requestId,
                interfaceName, serviceName, serviceType, domain, host, port, txtLen);
    }
    Context *context = new Context(requestId, mListener);
    DNSServiceRef *ref = mMonitor->allocateServiceRef(requestId, context);
    port = htons(port);
    if (ref == NULL) {
        ALOGE("requestId %d already in use during register call", requestId);
        cli->sendMsg(ResponseCode::CommandParameterError,
                "RequestId already in use during register call", false);
        return;
    }
    DNSServiceFlags nativeFlags = 0;
    int interfaceInt = ifaceNameToI(interfaceName);
    DNSServiceErrorType result = DNSServiceRegister(ref, interfaceInt, nativeFlags, serviceName,
            serviceType, domain, host, port, txtLen, txtRecord, &MDnsSdListenerRegisterCallback,
            context);
    if (result != kDNSServiceErr_NoError) {
        ALOGE("service register request %d got an error from DNSServiceRegister %d", requestId,
                result);
        mMonitor->freeServiceRef(requestId);
        cli->sendMsg(ResponseCode::CommandParameterError,
                "serviceRegister request got an error from DNSServiceRegister", false);
        return;
    }
    mMonitor->startMonitoring(requestId);
    if (VDBG) ALOGD("serviceRegister successful");
    cli->sendMsg(ResponseCode::CommandOkay, "serviceRegister started", false);
    return;
}
jint
shmemBase_attach(const char *addressString, long timeout, SharedMemoryConnection **connectionPtr)
{
    int error;
    SharedMemoryTransport *transport;
    jlong acceptingPID;

    clearLastError();

    error = openTransport(addressString, &transport);
    if (error != SYS_OK) {
        return error;
    }

    /* lock transport - no additional event to wait on as no connection yet */
    error = sysIPMutexEnter(transport->mutex, NULL);
    if (error != SYS_OK) {
        setLastError(error);
        closeTransport(transport);
        return error;
    }

    if (transport->shared->isListening) {
        error = doAttach(transport, timeout);
        if (error == SYS_OK) {
            acceptingPID = transport->shared->acceptingPID;
        }
    } else {
        /* Not listening: error */
        error = SYS_ERR;
    }

    sysIPMutexExit(transport->mutex);
    if (error != SYS_OK) {
        closeTransport(transport);
        return error;
    }

    error = openConnection(transport, acceptingPID, connectionPtr);

    closeTransport(transport);

    return error;
}
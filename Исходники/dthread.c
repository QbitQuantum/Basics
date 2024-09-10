VOID
WSAAPI
WsThreadDelete(IN PWSTHREAD Thread)
{
    /* Remove the blocking hook */
    Thread->BlockingHook = NULL;

    /* Free our buffers */
    if (Thread->Hostent) HeapFree(WsSockHeap, 0, Thread->Hostent);
    if (Thread->Servent) HeapFree(WsSockHeap, 0, Thread->Servent);
    if (Thread->ProtocolInfo) HeapFree(WsSockHeap, 0, Thread->ProtocolInfo);

    /* Clear the TLS */
    TlsSetValue(TlsIndex, NULL);

    /* Close the WAH Handle */
    WahCloseThread(Thread->AsyncHelper, &Thread->WahThreadId);

    /* Unlink the process and free us */
    Thread->Process = NULL;
    HeapFree(WsSockHeap, 0, Thread);
}
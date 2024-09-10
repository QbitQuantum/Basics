static ULONG
V2vConnectorProcessInternalTx(V2V_CONNECTOR_STATE *vcs)
{
    unsigned available;
    volatile UCHAR *msg;
    ULONG error;
    V2V_FRAME_HEADER *header;
    V2V_POST_INTERNAL *vpi;
    RPC_STATUS rpcstat;
    size_t msize;

    printf("V2VAPP-CONNECTOR sending internal message #%d\n", vcs->txCounter + 1);
    available = v2v_nc2_producer_bytes_available(vcs->channel);
    printf("V2VAPP-CONNECTOR channel indicates minimum bytes available: 0x%x\n", available);

    if (vcs->vac->xferSize == 0) {
        printf("V2VAPP-CONNECTOR transer size 0, send nothing\n");
        return ERROR_SUCCESS;
    }
    
    if (vcs->vac->fastrx && v2v_nc2_remote_requested_fast_wakeup(vcs->channel))
        msize = MIN(vcs->vac->xferSize, vcs->vac->xferMaxFastRx);
    else
        msize = vcs->vac->xferSize;

    if (!v2v_nc2_prep_message(vcs->channel, msize, V2V_MESSAGE_TYPE_INTERNAL, 0, &msg)) {
        error = GetLastError();
        if (error == ERROR_RETRY) {
            /* No room right now, return and try again later */
            printf("V2VAPP-CONNECTOR not enough buffer space to send message #%d; retry\n", vcs->txCounter + 1);
            return ERROR_RETRY;
        }
        printf("V2VAPP-CONNECTOR transmit internal data failure; abort processing - error: 0x%x\n", error);
        return error; /* failure */
    }
    vcs->txCounter++; /* next message */
    header = (V2V_FRAME_HEADER*)msg;
    header->id = (USHORT)vcs->txCounter;
    header->type = V2V_MESSAGE_TYPE_INTERNAL;
    header->cs = 0;
    header->length = vcs->vac->xferSize;
    vpi = (V2V_POST_INTERNAL*)msg;
    rpcstat = UuidCreate(&vpi->guid);
    if (rpcstat != RPC_S_OK) {
        printf("V2VAPP-CONNECTOR UuidCreate() failed - error: 0x%x; using NULL GUID\n", rpcstat);
        memset((void*)(msg + sizeof(V2V_FRAME_HEADER)), 0, sizeof(GUID));
    }
    /* Fill it up with some data and send it */
    memset((void*)(msg + sizeof(V2V_POST_INTERNAL)),
           'X',
           (vcs->vac->xferSize - sizeof(V2V_POST_INTERNAL)));
    header->cs = V2vChecksum((const UCHAR*)msg, vcs->vac->xferSize);
    v2v_nc2_send_messages(vcs->channel);

    /* Keep the send loop going by setting the event. If there is no more room, the prep message call
       will return ERROR_RETRY and just land us back in the wait. */
    SetEvent(v2v_get_send_event(vcs->channel));

    return ERROR_SUCCESS;
}
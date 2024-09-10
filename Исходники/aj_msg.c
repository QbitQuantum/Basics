AJ_Status AJ_DeliverMsg(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJ_IOBuffer* ioBuf = &msg->bus->sock.tx;

    /*
     * If the header has already been marshaled (due to partial delivery) it will be NULL
     */
    if (msg->hdr) {
        /*
         * Write the final body length to the header
         */
        msg->hdr->bodyLen = msg->bodyBytes;
        AJ_DumpMsg("SENDING", msg, TRUE);
        if (msg->hdr->flags & AJ_FLAG_ENCRYPTED) {
            status = EncryptMessage(msg);
        }
    } else {
        /*
         * Check that the entire body was written
         */
        if (msg->bodyBytes) {
            status = AJ_ERR_MARSHAL;
        }
    }
    if (status == AJ_OK) {
        //#pragma calls = AJ_Net_Send
        status = ioBuf->send(ioBuf);
    }
    memset(msg, 0, sizeof(AJ_Message));
    return status;
}
/**
EtherII MAC layer comments say we should free the packet buffer
RMBuf could contain a chain so get into a contiguous buffer
@param aPacket Reference to a chain of data buffers to be passed to the line.
@return 0 Tells the higher layer to send no more data.
        1 Tells higher layer that it can send more data.
*/
TInt CNcmPktDrv::Send(RMBufChain &aPacket)
    {
    TInt error = iEngine->Send(aPacket);
    aPacket.Free();

    return error;
    }
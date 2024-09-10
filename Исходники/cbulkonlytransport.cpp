TInt CBulkOnlyTransport::SendDataTxCmdL(const MClientCommandServiceReq* aCommand,
                                        TDesC8& aData,
                                        TUint aPos,
                                        TInt& aLen)
{
    __MSFNLOG
    TInt r = KErrNone;

    SendCbwL(aCommand, TBotCbw::EDataOut, aLen);

    TInt len = aLen;
    TInt length = 0;
    iBulkDataTd.SetZlpStatus(RUsbTransferDescriptor::ESuppressZlp);
    while (len)
    {
        TPtr8 senddata = iBulkDataTd.WritableBuffer();
        senddata.Append(aData.Ptr() + length + aPos, len > KResponsePacketSize? KResponsePacketSize : len);

        iBulkDataTd.SaveData(senddata.Length());
        iBulkPipeOut.Transfer(iBulkDataTd, iStatus);
        User::WaitForRequest(iStatus);

        if (iStatus.Int() != KErrNone)
        {
            if (iStatus.Int() == KErrUsbStalled)
            {
                __BOTPRINT(_L("SendDataTxCmdL ClearRemoteStall"));
                iBulkPipeOut.ClearRemoteStall();
#ifdef MASSSTORAGE_PUBLISHER
                TMsPublisher publisher(TMsPublisher::KStallProperty);
#endif
                break;
            }
            DoResetRecovery();
            __BOTPRINT1(_L("Usb transfer error %d"), r);
            User::Leave(KErrGeneral);
        }

        if(len > KResponsePacketSize)
        {
            len -= KResponsePacketSize;
            length += KResponsePacketSize;
        }
        else
        {
            length += len;
            len = 0;
        }
    }

    ReceiveCswL();

    TUint32 lenSent = 0;
    r = ProcessOutTransferL(lenSent);
    aLen = lenSent;

    return r;
}
TInt CT_DataRGavdp::GAVDP_SecurityControlIndication(TSEID /*aSEID*/, TDes8& aSecurityDataInOut)
{
    INFO_PRINTF1(KLogInfoSecurityControlIndication);

    //verify
    CheckEvent(EGAVDP_SecurityControlIndication);

    HBufC16* securityDataInOut = HBufC16::NewL(aSecurityDataInOut.Length());
    securityDataInOut->Des().Copy(aSecurityDataInOut);
    if (KLogDataFixed().Compare(*securityDataInOut)==0)
    {
        INFO_PRINTF1(KLogInfoSecurityDataUnchanged);
    }
    else if(KLogDataChange().Compare(*securityDataInOut)==0)
    {
        aSecurityDataInOut.Copy(KLogDataChanged());
        INFO_PRINTF2(KLogInfoSecurityDataChanged, &KLogDataChanged());
    }
    else
    {
        ERR_PRINTF1(KLogErrReceivedSecurityData);
        SetAsyncError(iCmdIndex, KErrGeneral);
    }
    delete securityDataInOut;

    DecOutstanding();
    return KErrNone;
}
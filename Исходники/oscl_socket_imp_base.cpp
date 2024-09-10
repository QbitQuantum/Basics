void OsclSocketIBase::CancelFxn(TPVSocketFxn aType)
{
    switch (aType)
    {
        case EPVSocketConnect:
            CancelConnect();
            break;
        case EPVSocketAccept:
            CancelAccept();
            break;
        case EPVSocketShutdown:
            CancelShutdown();
            break;
        case EPVSocketSend:
            CancelSend();
            break;
        case EPVSocketRecv:
            CancelRecv();
            break;
        case EPVSocketSendTo:
            CancelSendTo();
            break;
        case EPVSocketRecvFrom:
            CancelRecvFrom();
            break;
        case EPVSocketBind:
            CancelBind();
            break;
        case EPVSocketListen:
            CancelListen();
            break;
        default:
            OSCL_ASSERT(false);
            break;
    }
}
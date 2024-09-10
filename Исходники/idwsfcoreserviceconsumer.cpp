TPtrC8 CIdWsfCoreServiceConsumer::TrustAnchor() const
    {
    TLSLOG_L(KSenCoreServiceManagerLogChannelBase  , KMinLogLevel ,"CIdWsfCoreServiceConsumer::TrustAnchor");
    TPtrC8 trustAnchor = iService->TrustAnchor();

#ifdef _SENDEBUG
    if(trustAnchor.Length()>0)
        {
        TLSLOG(KSenCoreServiceManagerLogChannelBase  , KMinLogLevel ,(trustAnchor));
        }
    else
        {
        TLSLOG_L(KSenCoreServiceManagerLogChannelBase  , KMinLogLevel ," - trust anchor not set - ");
        }
#endif

    return trustAnchor;
    }
TBool CPKCS12Handler::VerifyType(const TDesC8& aData) const
    {
    ASSERT(iPkcsHandler);

    LOG_("-> CPKCS12Handler::VerifyType()");

    TBool isPKCS12(EFalse);

    // Need to check the data length before IsPKCS12Data call,
    // otherwise an assert (instead of a more suitable) 
    // might occur
    if (aData.Length() >= KPKCS12DataMinLength) 
        {
        isPKCS12 = iPkcsHandler->IsPKCS12Data(aData);
        }

    LOG_1("<- CPKCS12Handler::VerifyType() RET: %d", isPKCS12);
    return isPKCS12;
    }
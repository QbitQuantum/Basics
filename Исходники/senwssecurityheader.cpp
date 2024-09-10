EXPORT_C TInt CSenWsSecurityHeader::TimestampL(const TDesC8& aCreated, HBufC8*& aToken)
    {
    TPtrC8 nsPrefix = KSecurityUtilityXmlNsPrefix();
    aToken = HBufC8::NewLC(KTimestampFormatString8().Length()
                            + aCreated.Length() 
                            + nsPrefix.Length()*5
                            + KSecurityUtilityXmlNs().Length());

    TPtr8 ptr = aToken->Des();
    ptr.Format(KTimestampFormatString8, 
               &nsPrefix, 
               &nsPrefix, 
               &KSecurityUtilityXmlNs(),
               &nsPrefix, 
               &aCreated,
               &nsPrefix, 
               &nsPrefix);
    CleanupStack::Pop(aToken);
    return KErrNone;
    }
void CSenXmlReader::OnEndElementL(const RTagInfo& aElement, TInt /* aErrorCode */)
    {
    if(!iContentHandler)
        {
        SENDEBUG_L("OnEndElementL: KErrSenXmlContentHandlerNotSet");
        User::Leave(KErrSenXmlContentHandlerNotSet);
        }


    const TPtrC8 localName = aElement.LocalName().DesC();
    const TPtrC8 nsUri = aElement.Uri().DesC();
    const TPtrC8 prefix = aElement.Prefix().DesC();

    TPtrC8 qualifiedName = localName;

    if (prefix != KNullDesC8)
        {
        HBufC8* pQName = HBufC8::NewLC(prefix.Length()+localName.Length()+
                                        KSenColon().Length());
        TPtr8 qName = pQName->Des();
        qName.Append(prefix);
        qName.Append(KSenColon);
        qName.Append(localName);
        qualifiedName.Set(qName);
        }


    iContentHandler->EndElement(nsUri,
                                localName,
                                qualifiedName);

    if (prefix != KNullDesC8)
        {
        CleanupStack::PopAndDestroy(); // pQName
        }

    }
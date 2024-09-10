void CAknGlobalListQuerySubject::StartL(const TDesC8& aBuffer, TInt /*aReplySlot*/, 
    const RMessagePtr2& aMessage)
    {
    if (iPending)
        {
        aMessage.Complete(KErrInUse);
        return;
        }

    RDesReadStream readStream(aBuffer);
    if (aBuffer.Length() < KCharsInTInt || readStream.ReadInt32L() != KAKNNOTIFIERSIGNATURE)
        {
        User::Leave(KErrArgument);
        }

    iMessage = aMessage;
    iSelectFirst = readStream.ReadInt16L();
    TInt count = readStream.ReadInt16L();

    // Create array
    delete iArray;
    iArray = 0;
    iArray = new (ELeave) CDesCArrayFlat(KArrayGranularity);
    
    TBuf<KListQueryItemLength> arrayItem;

    for (TInt ii = 0; ii < count; ii++)
        {
        readStream >> arrayItem;
        iArray->AppendL(arrayItem);
        }
        
    TInt headingLength = readStream.ReadInt16L();
    delete iHeading;
    iHeading = 0;
    
    if (headingLength != KErrNotFound)
        {
        iHeading = HBufC::NewL(headingLength);
        TPtr ptr = iHeading->Des();
        readStream >> ptr;
        }
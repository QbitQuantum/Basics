// -----------------------------------------------------------------------------
// CNATFWUNSAFAttribute::EncodeL
// -----------------------------------------------------------------------------
//
HBufC8* CNATFWUNSAFAttribute::EncodeL() const
    {
    HBufC8* value = EncodeValueL();
    CleanupStack::PushL(value);
    TInt attrValLength = value->Length();

    //Pad non-DWORD-boundary aligned attributes with spaces if needed. Spaces
    //used instead of \0 in order to not mess up buggy C implementations.
    const TInt KGranularity = 4;
    TInt bytesInLastBlock = attrValLength % KGranularity;
    TInt bytesToAppend = KGranularity - bytesInLastBlock;
    if (0 < bytesInLastBlock && !IsWordBoundaryAligned(Type()))
        {
        CBufBase* valueBuf = CBufFlat::NewL(attrValLength + bytesToAppend);
        CleanupStack::PushL(valueBuf);
        valueBuf->InsertL(0, *value, attrValLength);
        const TChar KSpace(' ');
        for (TInt i = 0; i < bytesToAppend; ++i)
            {
            valueBuf->InsertL(valueBuf->Size(), &KSpace, 1);
            }
        // Store value pointer for proper cleanupstack handling
        HBufC8* oldValue = value;
        value = valueBuf->Ptr(0).AllocL();
        CleanupStack::PopAndDestroy(valueBuf);
        CleanupStack::PopAndDestroy( oldValue );
        CleanupStack::PushL( value );
        }

    HBufC8* attribute = HBufC8::NewLC(value->Length() + EValueOffset);
    TPtr8 ptr = attribute->Des();
    ptr.FillZ(EValueOffset);

    NATFWUNSAFUtils::WriteNetworkOrder16L(ptr, ETypeOffset, Type());
    NATFWUNSAFUtils::WriteNetworkOrder16L(ptr,
                                     ELengthOffset,
                                     static_cast<TUint16>(attrValLength));
    ptr.Append(*value);
    CleanupStack::Pop(attribute);
    CleanupStack::PopAndDestroy(value);

    return attribute;
    }
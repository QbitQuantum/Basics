void CSdpPDUHandler::CompleteOPL(TDes8& aPdu, const TDesC8& aWritePdu, const TInt aMaxAttrCount)
/**
	Verifies the size of the response parameters
	and writes out correct length for the attributes.
 @verbatim
		response descriptor			DesC
		written area (attributes)	DesC
		maximum byte count			TInt
 @endverbatim

	Method will leave if response is bigger than requested or allowed for.
	Returns nothing

**/
{
    TUint16 finalLength = (TUint16)aWritePdu.Length();
    if (finalLength > aMaxAttrCount) User::Leave(KErrNoMemory);
    aPdu.SetLength(KRspAttributeCountSize + finalLength + KContStateHeader);
    BigEndian::Put16(&aPdu[KRspAttrCountOffset], finalLength);
// now need to update the DES size
    if (iDesSize == 3)
    {
        BigEndian::Put16(&aPdu[KRspAttributeListOffset+1], (unsigned short)(finalLength-iDesSize));
    }
    else if (iDesSize == 2)
    {
        if (finalLength > 0xff) User::Leave(KErrNoMemory);
        aPdu[KRspAttributeListOffset+1] = (unsigned char)((finalLength&0xff)-iDesSize);
    }
    else User::Leave(KErrUnknown);   // perhaps this should be a panic
    aPdu[aPdu.Length()-1] = 0; // FIXME: Put contState here
}
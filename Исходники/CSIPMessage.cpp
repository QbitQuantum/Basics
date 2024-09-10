// -----------------------------------------------------------------------------
// CSIPMessage::ToTextHeaderPartLC
// -----------------------------------------------------------------------------
//
EXPORT_C CBufBase* CSIPMessage::ToTextHeaderPartLC ()
    {
    const TInt KResultBufExpandSize = 100;
    CBufFlat* encodedHeaderPart = CBufFlat::NewL(KResultBufExpandSize);
    CleanupStack::PushL(encodedHeaderPart);
	HBufC8* firstLine = ToTextFirstLineLC ();    
    encodedHeaderPart->InsertL (0,*firstLine);
    TInt encodedLength = firstLine->Length();
    CleanupStack::PopAndDestroy(firstLine);
    encodedHeaderPart->InsertL (encodedLength,KCRLF);
    encodedLength += KCRLF().Length();

    // Add headers
	for (TInt i=0; i < iSIPHeaderListArray.Count(); i++)
		{
		TSglQueIter<CSIPHeaderBase> iter(iSIPHeaderListArray[i]);
        TInt headerCountInList=0;
		while (iter)
			{
			CSIPHeaderBase* header = iter++;
            HBufC8* headerAsText = NULL;
            if (++headerCountInList == 1 || !header->EncodeMultipleToOneLine())
                {
			    headerAsText = header->ToTextLC();
                }
            else
                {
                headerAsText = header->ToTextValueLC();
                }
            encodedHeaderPart->InsertL (encodedLength,*headerAsText);
            encodedLength += headerAsText->Length();
            CleanupStack::PopAndDestroy(headerAsText);
            if (!iter || !header->EncodeMultipleToOneLine())
                {
                encodedHeaderPart->InsertL (encodedLength,KCRLF);
                encodedLength += KCRLF().Length();
                }
            else 
                {
                encodedHeaderPart->InsertL (encodedLength,KComma);
                encodedLength += KComma().Length();
                }
			}
		}

    // Add Content-Length header
	HBufC8* contentLengthHeaderAsText = ToTextContentLengthLC ();
    encodedHeaderPart->InsertL (encodedLength,*contentLengthHeaderAsText);
    encodedLength += contentLengthHeaderAsText->Length();
    CleanupStack::PopAndDestroy(contentLengthHeaderAsText);

    // Add CRLF CRLF ending the header part
    encodedHeaderPart->InsertL (encodedLength,KCRLFCRLF);
    encodedLength += KCRLFCRLF().Length();

    return encodedHeaderPart;
    }
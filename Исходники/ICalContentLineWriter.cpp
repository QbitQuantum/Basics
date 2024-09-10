/**
Writes the current content line to the stream after conversion to UTF-8.
Performs any necessary folding.
@internalTechnology
*/
void CICalContentLineWriter::WriteContentLineL()
	{
	TRACE_ENTRY_POINT;
	
	// Convert to UTF-8 for writing
	HBufC8* tmpLine = CnvUtfConverter::ConvertFromUnicodeToUtf8L(*iCurrentLine);
	CleanupStack::PushL(tmpLine);
	
	TInt pos(0);
	TInt remaining(tmpLine->Length());
	
	// Fold the line if longer than 75 octets
	TInt lineLength(KICalMaxLineLength);
	
	while (remaining > lineLength)
		{
		iWriteStream.WriteL(tmpLine->Mid(pos), lineLength);
		iWriteStream.WriteL(KICalFoldLine);
		pos += lineLength;
		remaining -= lineLength;
		lineLength = KICalMaxFoldedLineLength;
		}
		
	// Complete the line
	iWriteStream.WriteL(tmpLine->Mid(pos));
	iWriteStream.WriteL(KICalCRLF);	

	CleanupStack::PopAndDestroy(tmpLine);
	
	iCurrentLine->Des().SetLength(0);
	
	TRACE_EXIT_POINT;
	}
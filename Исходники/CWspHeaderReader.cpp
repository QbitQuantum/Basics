void CWspHeaderReader::DecodeProfileWarningL(RHeaderField& aHeader) const
	{
	TPtrC8 rawData;
	aHeader.RawDataL(rawData);
	CheckLengthL(rawData, 1);
	TWspPrimitiveDecoder wspDecoder(rawData);
	switch (wspDecoder.VarType())
		{
		case TWspPrimitiveDecoder::E7BitVal: // This is a short int profile warn-code
			{
			DecodeGenericWarnCodeL(aHeader, wspDecoder);
			} break;
		case TWspPrimitiveDecoder::ELengthVal:
			{
			TInt length = 0;
			TInt bytesRead = wspDecoder.LengthVal(length);
			User::LeaveIfError(bytesRead);
			
			// Get the first part - profile warn-code (short int)
			DecodeGenericWarnCodeL(aHeader, wspDecoder);
			++bytesRead;
			
			// Get the second part - warn-target
			if(CheckForNullStringL(rawData, bytesRead, wspDecoder))
				SetNewFStringPartL(aHeader, 1, KNullDesC8());
			else
				bytesRead += AddNewDecoderStringPartL(aHeader, wspDecoder, 1);

			// Get the warn-date if it exists
			if( bytesRead < rawData.Length() )
				{
				TDateTime dateTime(1970, EJanuary, 0, 0, 0, 0, 0);
				User::LeaveIfError(wspDecoder.Date(dateTime));
				SetNewDatePartL(aHeader, 2, dateTime);
				}
			} break;
		default:
			User::Leave(KErrCorrupt);
			break;
		}
	}
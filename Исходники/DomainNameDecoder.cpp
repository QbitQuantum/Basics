void CDomainNameCodec::DecodeL(TPtr8& aInDes)
	{
	TDomainName domainName;

	TUint8* pChar = const_cast<TUint8*>(aInDes.Ptr());
	TUint listLength = aInDes.Length();
	TUint8 labelLength = 0;
	
	// Walk the list of domain names
	while(pChar < aInDes.Ptr() + listLength)
		{
		domainName.Zero();
		
		while(*pChar++ != NULL)
			{
			if(domainName.Length() > 0)
				{
				domainName.Append('.');
				}
				
			labelLength = *(pChar - 1);
			
			// The two highest order bits must be clear
			User::LeaveIfError(labelLength & 0xC0 ? KErrArgument : KErrNone);
					
			// Add in the label data
			domainName.Append(pChar, labelLength);
			
			// Advance the pointer to the next length value
			pChar += labelLength;
			}
			
		iDomainList.Append(domainName);
		}
	}
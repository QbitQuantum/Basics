void CHttpClientHeaderReader::DecodeSetCookieL(RHeaderField& aHeader) const
	{
   
	// The generic header will add each cookie on a separate line. Each cookie forms 1 part.
	// Each cookie will be made up of a number of parameters with name being the first and value the second, following that 
	// will be just the actual parameters that form part of a cookie.
	
	TPtrC8 buffer;
	aHeader.RawDataL(buffer);	
	TInt remainingSize = buffer.Length();

	TPtrC8 token;
	TInt cookieCount = 0;
	while (remainingSize > 0)
		{
		// Extract tokens seperated by header field separator defined as KFieldSeparator in textmodestd.h
		remainingSize -= InetProtTextUtils::ExtractNextTokenFromList(buffer, token, KFieldSeparator);
		DecodeOneCookieL(aHeader, token, cookieCount);
		++cookieCount;
		}
	}
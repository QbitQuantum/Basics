// Extract a WSP encoded MultiOctet Integer encoding into 32-bit integer
//
// In:
//  aSource	- the source Multi-Octet integer
//
// Out:
//  aInt		- the 32-bit resulting integer
//
void CHTTPResponse::ExtractMultiOctetInteger(TInt& aInt, const TPtrC8& aSource) const
 	// Extract a WSP encoded integer from the source descriptor
	{
	__LOG_ENTER(_L("CHTTPResponse::ExtractMultiOctetInteger"));
	// Get num bytes encoding the integer - 
	// we are positioned at that location in the source descriptor
	TUint8 numBytes = aSource[0];
	aInt = 0;
	if (numBytes <= 30)
 		{
 		__ASSERT_DEBUG(numBytes <= aSource.Length(), User::Invariant());
 		// Loop over the source, taking each byte and shifting it in to the count.
 		for (TInt count = 1; (count <= numBytes); count++)
 		        aInt = (aInt << 8) + aSource[count];
 		}
 	else if (numBytes & 0x80) //  check top bit is set
 		aInt = numBytes & 0x7f;
 	// anything between 30 and 127 is not handled...
	__LOG_RETURN;
	}
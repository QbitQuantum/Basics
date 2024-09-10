TInt CAuthenticationHmac::Compare(const TDesC8 &aDigest)
	/**
	* Finish the digets computation and compare with ICV.
	*
	* @param aDigest The ICV to match
	* @return comparison result (= 0, match, != 0, no match).
	*/
	{
	TPtr8 ptr = iTemp->Des();
	ptr.SetLength(iDigestSize);		// Ensure correct length!
	iDigest->Final(ptr);			// Get Current Digest Value
	iDigest->Init();				// Initialize Digest Engine
	iDigest->Update(*iHmac_opad);	// Feed in the precomputed output pad
	iDigest->Update(ptr);			// Merge with digest from the first phase
	iDigest->Final(ptr);			// and produce the final digest value.
									// The caller may want a tructated value
	ptr.SetLength(aDigest.Length());
	return aDigest.Compare(ptr);
	}
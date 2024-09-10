//TODO Exception handling instead of the corny boolean return code
bool ODRLLicense::verifySignature(XMLDocument* p_LicenseDoc, UserContext* p_Principal)
{
	char* origLicenseXML = NULL;
	char* tbsXML = NULL;
	char* sigXML = NULL;
	char* hashBase64 = NULL;
	ByteArray* hashBytes = NULL;
	XMLDocument* pLicenseSigDoc = NULL;
	ByteArray* sigBytes = NULL;
	int outLen=0, saveLen=0;
	HashContext hashCtx;
	bool isError = false;
	int val=0;
	char* tempSigBuffer=NULL;
	char* origLicenseBuffer=NULL;
	char* pdest = NULL;
	int saveLength1=0, saveIndex1=0, lastLength = 0;
	std::string license;
	std::string::size_type pos1=0, pos2=0, finalLength=0;

	/**  Check Signature
	1. clone the license doc
	2. remove the signature section
	3. calculate a hash
	4. base64 decode the signature in the doc 
	5. call signatureVerify, pass in the local certificateChain
	*/

	if ( (p_LicenseDoc == NULL) || (p_Principal == NULL) )
	{
		gLogger->logError("ODRLLicense::verifySignature : p_License or p_Principal is NULL.");
		isError = true;
		goto error;
	}

/*	CJM 10/29/02 origLicenseXML = p_LicenseDoc->encode();
	if (origLicenseXML == NULL)
	{
		isError = true;
		goto error;
	}

	pLicenseSigDoc = new XMLDocument();
	pLicenseSigDoc->decode(origLicenseXML, "o-ex:rights");

	if (pLicenseSigDoc == NULL)
	{
		isError = true;
		goto error;
	}

	if (!pLicenseSigDoc->remove("ds:Signature"))
	{
		isError = true;
		goto error;
	}

	tbsXML = pLicenseSigDoc->encode();

	if (tbsXML == NULL)
	{
		isError = true;
		goto error;
	}
*/

	/** CJM hackfest '02
		Ok.. here's the deal..due to different limitations in both our library and due to the 
		fact that there's differences in how Java (where our licenses are constructed) and C++
		(where the license signatures are checked) manage XML encoding.. we need to implement a 
		hacked up signature checking algorithm..  The following code replaces the code above.
	*/
	license = getBytes();

	std::transform(license.begin(),license.end(), license.begin(),tolower);
	pos1 = license.find ("<ds:signature>",0);

	if (pos1 == std::string::npos)
	{
		gLogger->logError("ODRLLicense::verifySignature : Signature start tag not found in License XML.");
		isError = true;
		goto error;
	}
	pos2 = license.find ("</ds:signature>",0);

	if (pos2 == std::string::npos)
	{
		gLogger->logError("ODRLLicense::verifySignature : Signature end tag not found in License XML.");
		isError = true;
		goto error;
	}
	pos2 += strlen("</ds:Signature>");
	
	//reset it to the original
	license = getBytes();
	license.erase(pos1, (pos2 - pos1));

   
	//TODO: CHECK ALGORITHM defined in the license.. 
	hashCtx.setHashType(EVP_sha1());
	hashCtx.hashInit();
	hashCtx.hashUpdate((unsigned char*)license.c_str(), strlen(license.c_str()));
	hashCtx.hashFinal();

	//read the hash bytes
	hashBase64 = p_LicenseDoc->getString("ds:Signature.ds:SignedInfo.ds:Reference.ds:DigestValue");

	hashBytes = RFC1521Base64::decode(hashBase64);

	if (!hashBytes)
	{
		gLogger->logError("ODRLLicense::verifySignature : Error Decoding DigestValue B64");
		isError = true;
		goto error;
	}


	if ( (val = memcmp(hashBytes->data(), hashCtx.getHashBytes(), hashBytes->length())) != 0)
	{
		gLogger->logError("ODRLLicense::verifySignature : License Hash does not match local hash calculation.");
		isError = true;
		goto error;
	}
	
	//read the signature
	sigXML = p_LicenseDoc->getString("ds:Signature.ds:SignatureValue");

	if (!sigXML)
	{
		gLogger->logError("ODRLLicense::verifySignature : Can't extract SignatureValue from License.");
		isError = true;
		goto error;
	}

	sigBytes = RFC1521Base64::decode(sigXML);
	if (!sigBytes)
	{
		gLogger->logError("ODRLLicense::verifySignature : Error decoding SignatureValue B64.");
		isError = true;
		goto error;
	}
	if (!hashCtx.verifySignature((unsigned char*)sigBytes->data(), sigBytes->length(), p_Principal->getCaCertChain()))
	{
		gLogger->logError("ODRLLicense::verifySignature : License Signature Check Failed.");
		isError = true;
		goto error;
	}

//lamey lame lame
error:
		if (origLicenseXML) delete[] origLicenseXML;
		if (tbsXML) delete[] tbsXML;
		if (sigXML) delete[] sigXML;
		if (pLicenseSigDoc) delete pLicenseSigDoc;
		if (sigBytes)delete sigBytes;
		if (tempSigBuffer) delete[] tempSigBuffer;
		if (hashBytes) delete hashBytes;
    if (hashBase64) delete[] hashBase64;

		if (isError)
			return false;
		
		return true;
}
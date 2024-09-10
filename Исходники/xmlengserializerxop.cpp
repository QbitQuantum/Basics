// --------------------------------------------------------------------------------------
// Decodes input data from base64 to binary octets and creates
// heap buffer with the decoded data. The buffer is pushed on the cleanup stack.
// --------------------------------------------------------------------------------------
//
HBufC8* CXmlEngSerializerXOP::CreateDecodedBufLC(TPtrC8 aEncodedData)
	{
	// The decoded length of base64 is about half (use same) encoded length
	HBufC8* decodedData = HBufC8::NewLC(aEncodedData.Size());
	TPtr8 decodedDataPtr = decodedData->Des();
	// Decode the base64 Content-Transfer-Encoding
	using namespace BSUL;
	Base64Codec::Decode(aEncodedData, decodedDataPtr);
	if(decodedDataPtr.Length() == 0)
		{
		User::Leave(KXmlEngErrDecodingFailed);
		}
	return decodedData;	
	}
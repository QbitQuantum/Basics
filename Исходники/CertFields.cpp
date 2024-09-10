/***
 *** Public key info
 *** Format = CSSM_X509_SUBJECT_PUBLIC_KEY_INFO
 ***/
static bool getField_PublicKeyInfo (
	DecodedItem		 	&item,
	unsigned			index,			// which occurrence (0 = first)
	uint32				&numFields,		// RETURNED
	CssmOwnedData		&fieldValue)	// RETURNED
{
	const DecodedCert &cert = dynamic_cast<const DecodedCert &>(item);
	const CSSM_X509_SUBJECT_PUBLIC_KEY_INFO &srcInfo =
		cert.mCert.tbs.subjectPublicKeyInfo;
	if(!tbsGetCheck(srcInfo.subjectPublicKey.Data, index)) {
		return false;
	}

	Allocator &alloc = fieldValue.allocator;
	fieldValue.malloc(sizeof(CSSM_X509_SUBJECT_PUBLIC_KEY_INFO));
	CSSM_X509_SUBJECT_PUBLIC_KEY_INFO *dstInfo =
		(CSSM_X509_SUBJECT_PUBLIC_KEY_INFO *)fieldValue.data();

	CL_copySubjPubKeyInfo(srcInfo, true,		// length in bits here
		*dstInfo, false,						// length in bytes
		alloc);

	numFields = 1;
	return true;
}
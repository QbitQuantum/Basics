/***
 *** SignedCRL
 *** Format: CSSM_X509_SIGNED_CRL (the whole enchilada, parsed)
 ***/
static bool getField_SignedCrl (
	DecodedItem		 	&item,
	unsigned			index,			// which occurrence (0 = first)
	uint32				&numFields,		// RETURNED
	CssmOwnedData		&fieldValue)	// RETURNED
{
	Allocator 			&alloc = fieldValue.allocator;
	
	const DecodedCrl &nssCrl = dynamic_cast<const DecodedCrl &>(item);
	const NSS_TBSCrl &nssTbs = nssCrl.mCrl.tbs;
	fieldValue.malloc(sizeof(CSSM_X509_SIGNED_CRL));
	CSSM_X509_SIGNED_CRL	&cssmCrl = *((CSSM_X509_SIGNED_CRL *)fieldValue.data());

	memset(&cssmCrl, 0, sizeof(CSSM_X509_SIGNED_CRL));
	CSSM_X509_TBS_CERTLIST &cssmTbs = cssmCrl.tbsCertList;

	/* version */
	clAllocCopyData(alloc, nssTbs.version, cssmTbs.version);
	
	/* CSSM_X509_ALGORITHM_IDENTIFIER signature - in TBS and CRL */
	CL_copyAlgId(nssTbs.signature, cssmTbs.signature, alloc);
	CL_copyAlgId(nssCrl.mCrl.signatureAlgorithm, 
			cssmCrl.signature.algorithmIdentifier, alloc);
	
	/* CSSM_X509_NAME issuer */
	CL_nssNameToCssm(nssTbs.issuer, cssmTbs.issuer, alloc);
	
	/* CSSM_X509_TIME thisUpdate, nextUpdate */
	CL_nssTimeToCssm(nssTbs.thisUpdate, cssmTbs.thisUpdate, alloc);
	CL_nssTimeToCssm(nssTbs.nextUpdate, cssmTbs.nextUpdate, alloc);
	
	/* CSSM_X509_REVOKED_CERT_LIST_PTR revokedCertificates */
	if(nssTbs.revokedCerts != NULL) {
		cssmTbs.revokedCertificates = (CSSM_X509_REVOKED_CERT_LIST_PTR)
			alloc.malloc(sizeof(CSSM_X509_REVOKED_CERT_LIST));
		memset(cssmTbs.revokedCertificates, 0, sizeof(CSSM_X509_REVOKED_CERT_LIST));
		nssRevokedListToCssm(nssTbs.revokedCerts,
			cssmTbs.revokedCertificates, alloc);
	}
	
	/* CSSM_X509_EXTENSIONS extensions */
	const DecodedExtensions &decodedExtens = nssCrl.decodedExtens();
	decodedExtens.convertToCdsa(cssmTbs.extensions, alloc);
	
	/* raw signature - stored in bits - note signature.algId set above */
	CSSM_DATA nssSig = nssCrl.mCrl.signature;
	nssSig.Length = (nssSig.Length + 7) / 8;
	clAllocCopyData(alloc, nssSig, cssmCrl.signature.encrypted);
	numFields = 1;
	return true;
}
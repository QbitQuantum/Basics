DecodedExten::DecodedExten(
	const CSSM_OID 	&extnId,	// copied
	bool			critical,
	void			*nssObj,	// NSS_KeyUsage, NSS_BasicConstraints, 
								//   etc. NOT COPIED, exists in same
								//   memory space as coder
	bool			berEncoded,	// indicates unknown extension which we
								// do not BER-decode when parsing a cert
	const SecAsn1Template *templ,	// to decode/encode if !berEncoded
	SecNssCoder		&coder,			// all local allocs from here
	const CSSM_DATA	*rawExtn)	// NSS_CertExtension.value, copied to
								//   mRawExtn
	: mCritical(critical),
	  mNssObj(nssObj),
	  mBerEncoded(berEncoded),
	  mTempl(templ),
	  mCoder(coder),
	  mRawExtn(NULL)
{
	coder.allocCopyItem(extnId, mExtnId);
	if(rawExtn) {
		mRawExtn = (CSSM_DATA *)coder.malloc(sizeof(CSSM_DATA));
		coder.allocCopyItem(*rawExtn, *mRawExtn);
	}
}
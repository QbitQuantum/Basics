/*
 * symmetric key generator with startDate/endDate
 */
static int genSymKey(
	CSSM_CSP_HANDLE 	cspHand,
	CSSM_KEY_PTR		symKey,
	uint32 				alg,
	const char			*keyAlgStr,
	uint32 				keySizeInBits,
	CSSM_KEYATTR_FLAGS	keyAttr,
	CSSM_KEYUSE			keyUsage,
	CSSM_BOOL			quiet,
	bool 				setStartDate,
	int					startDeltaDays,
	bool				setEndDate,
	int					endDeltaDays,
	CSSM_DL_DB_HANDLE	*dlDbHand = NULL)		// optional
{
	CSSM_RETURN			crtn;
	CSSM_CC_HANDLE 		ccHand;
	CSSM_DATE			startDate;
	CSSM_DATE			endDate;
	
	if(setStartDate) {
		setDate(startDate, startDeltaDays);
	}
	if(setEndDate) {
		setDate(endDate, endDeltaDays);
	}
	
	memset(symKey, 0, sizeof(CSSM_KEY));
	crtn = CSSM_CSP_CreateKeyGenContext(cspHand,
		alg,
		keySizeInBits,	// keySizeInBits
		NULL,			// Seed
		NULL,			// Salt
		setStartDate ? &startDate : NULL,
		setEndDate ? &endDate : NULL,
		NULL,			// Params
		&ccHand);
	if(crtn) {
		printError("CSSM_CSP_CreateKeyGenContext", crtn);
		return testError(quiet);
	}
	if(dlDbHand) {
		/* add in DL/DB to context */
		crtn = cspAddDlDbToContext(ccHand, dlDbHand->DLHandle, 
			dlDbHand->DBHandle);
		if(crtn) {
			return testError(quiet);
		}
	}
	crtn = CSSM_GenerateKey(ccHand,
		keyUsage,
		keyAttr,
		&keyLabelData,
		NULL,			// ACL
		symKey);
	if(crtn) {
		printError("CSSM_GenerateKey", crtn);
		return testError(quiet);
	}
	CSSM_DeleteContext(ccHand);

	CSSM_KEYHEADER &hdr = symKey->KeyHeader;
	CSSM_DATE *cdp = NULL;
	if(setStartDate) {
		cdp = &startDate;
	}
	if(compareDates(cdp, &hdr.StartDate, keyAlgStr, quiet)) {
		return 1;
	}
	if(setEndDate) {
		cdp = &endDate;
	}
	else {
		cdp = NULL;
	}
	if(compareDates(cdp, &hdr.EndDate, keyAlgStr, quiet)) {
		return 1;
	}
	return 0;
}
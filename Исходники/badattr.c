/*
 * Common, flexible, error-tolerant key pair generator.
 */
static int genKeyPair(
	CSSM_CSP_HANDLE 	cspHand,
	uint32 				algorithm,
	const char			*keyAlgStr,
	uint32 				keySizeInBits,
	CSSM_KEY_PTR 		pubKey,			
	CSSM_KEYATTR_FLAGS 	pubKeyAttr,
	CSSM_KEYUSE 		pubKeyUsage,	
	CSSM_KEY_PTR 		privKey,		
	CSSM_KEYATTR_FLAGS 	privKeyAttr,
	CSSM_KEYUSE 		privKeyUsage,	
	CSSM_RETURN			expectRtn,
	CSSM_BOOL 			quiet,
	CSSM_BOOL 			freeKeys,			// true: free the keys on exit
	const char			*testStr)
{
	CSSM_RETURN			crtn;
	CSSM_CC_HANDLE 		ccHand;
	CSSM_DATA			keyLabelData = {4, (uint8 *)"foo"};
	int					irtn;
	
	memset(pubKey, 0, sizeof(CSSM_KEY));
	memset(privKey, 0, sizeof(CSSM_KEY));

	crtn = CSSM_CSP_CreateKeyGenContext(cspHand,
		algorithm,
		keySizeInBits,
		NULL,					// Seed
		NULL,					// Salt
		NULL,					// StartDate
		NULL,					// EndDate
		NULL,					// Params
		&ccHand);
	if(crtn) {
		printError("CSSM_CSP_CreateKeyGenContext", crtn);
		return testError(quiet);
	}

	/* post-context-create algorithm-specific stuff */
	switch(algorithm) {
		case CSSM_ALGID_RSA:
			break;
		 
		 case CSSM_ALGID_DSA:
			/* 
			 * extra step - generate params - this just adds some
			 * info to the context
			 */
			{
				CSSM_DATA dummy = {0, NULL};
				crtn = CSSM_GenerateAlgorithmParams(ccHand, 
					keySizeInBits, &dummy);
				if(crtn) {
					printError("CSSM_GenerateAlgorithmParams", crtn);
					return testError(quiet);
				}
				appFreeCssmData(&dummy, CSSM_FALSE);
			}
			break;
		default:
			break;
	}
	
	crtn = CSSM_GenerateKeyPair(ccHand,
		pubKeyUsage,
		pubKeyAttr,
		&keyLabelData,
		pubKey,
		privKeyUsage,
		privKeyAttr,
		&keyLabelData,			// same labels
		NULL,					// CredAndAclEntry
		privKey);
	if(crtn != expectRtn) {
		printf("***Testing %s for alg %s:\n", testStr, keyAlgStr);
		printf("   CSSM_GenerateKeyPair: expect %s\n",	cssmErrToStr(expectRtn));
		printf("   CSSM_GenerateKeyPair: got    %s\n",  cssmErrToStr(crtn));
		irtn = testError(quiet);
	}
	else {
		irtn = 0;
	}
	CSSM_DeleteContext(ccHand);
	if(freeKeys && (crtn == CSSM_OK)) {
		cspFreeKey(cspHand, pubKey);
		cspFreeKey(cspHand, privKey);
	}
	return irtn;
}
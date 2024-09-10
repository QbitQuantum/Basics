BOOL genKeyPair( PROV_CTX* pProvCtx, KEY_INFO* pKey ){
	if ( pKey->algId != CALG_GOST_SIGN ){
		SetLastError( NTE_BAD_ALGID );
		return FALSE;
	}
	if ( pKey->hKeyInformation == NULL ){
		SetLastError( NTE_BAD_KEY_STATE );
		return FALSE;
	}

	CONTAINER_IRZ *pContainerIRZ = (CONTAINER_IRZ*) pProvCtx->pContainer->hServiceInformation;
	KEY_SIGN_INFO *pKeyInfo = (KEY_SIGN_INFO*) pKey->hKeyInformation;


	// Generate key pair in proper.
	if ( pKeyInfo->pPrKey != NULL || pKeyInfo->pPubKey != NULL ){
		DEBUG( 1, "While generating key pair: Key already exists." );
	}
	if ( !genKeyPair( &pKeyInfo->pPubKey, &(pKeyInfo->pPrKey), &pKeyInfo->params, &pContainerIRZ->rand ) ){
		SetLastError( NTE_FAIL );
		return FALSE;
	}
	
	// Write the key to the token.
	LPSTR szPrKey = new CHAR[PRIVATEKEY_CHAR_LEN+1];
	LPSTR szPubKey = new CHAR[PUBLICKEY_CHAR_LEN+1];
	
	if ( !privateKeyToString( pKeyInfo, szPrKey ) ){
		/* \todo release resources.*/
		SetLastError( NTE_FAIL );
		return FALSE;
	}
	
	if ( !pubKeyToString( pKeyInfo, szPubKey ) ){
		/* \todo release resources.*/
		SetLastError( NTE_FAIL );
		return FALSE;
	}

	WritePrivateProfileStringA( 
		"PRIVATEKEY",
		"PRIVATEKEY",
		szPrKey,
		pContainerIRZ->szToken);

	WritePrivateProfileStringA( 
		"PUBLICKEY",
		"PUBLICKEY",
		szPubKey,
		pContainerIRZ->szToken);

	delete[] szPrKey;
	delete[] szPubKey;

	return TRUE;

}
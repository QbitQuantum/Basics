//-----------------------------------------------------------------------------
// swCryptDeriveKey()
//-----------------------------------------------------------------------------
// Calcul de la clé de chiffrement des mots de passe par dérivation du mot de 
// passe maitre
//-----------------------------------------------------------------------------
// [in] cszMasterPwd = mot de passe maitre
// [out] hKey = handle de clé
// [out] pAESKeyData = bloc de données pour ceux qui voudraient reconstruire la clé
//-----------------------------------------------------------------------------
// Retour : 0 si OK
//-----------------------------------------------------------------------------
int swCryptDeriveKey(const char *pszMasterPwd,HCRYPTKEY *phKey,BYTE *pAESKeyData,BOOL bForceOldDerivationFunction)
{
	TRACE((TRACE_ENTER,_F_,""));

	BOOL brc;
	int rc=-1;
	HCRYPTHASH hHash=NULL;
	
	// si la clé a déjà été créée, on la libère
	if (*phKey!=NULL) { CryptDestroyKey(*phKey); *phKey=NULL; }

	// création d'un hash
	brc=CryptCreateHash(ghProv,CALG_SHA1,0,0,&hHash);           
	if (!brc) {	TRACE((TRACE_ERROR,_F_,"CryptCreateHash()")); goto end; }
	if (bForceOldDerivationFunction)
	{
		// hash du mot de passe
		brc=CryptHashData(hHash,(unsigned char*)pszMasterPwd,strlen(pszMasterPwd),0); 
		if (!brc) {	TRACE((TRACE_ERROR,_F_,"CryptHashData()")); goto end; }
		// dérivation
		brc=CryptDeriveKey(ghProv,CALG_AES_256,hHash,0,phKey); 
		TRACE((TRACE_INFO,_F_,"CryptDeriveKey(CALG_AES_256)"));
	}
	else if (atoi(gszCfgVersion)<93)
	{
		// hash du mot de passe
		brc=CryptHashData(hHash,(unsigned char*)pszMasterPwd,strlen(pszMasterPwd),0); 
		if (!brc) {	TRACE((TRACE_ERROR,_F_,"CryptHashData()")); goto end; }
		// dérivation
		brc=CryptDeriveKey(ghProv,CALG_3DES,hHash,0,phKey); 
		TRACE((TRACE_INFO,_F_,"CryptDeriveKey(CALG_3DES)"));
	}
	else // nouveau mécanisme +secure en 0.93 (PBKDF2) ISSUE#56
	{
		// Obtient 256 bits (32 octets) auprès de PBKDF2 pour générer une clé AES-256
		if (!swIsPBKDF2KeySaltReady()) { TRACE((TRACE_ERROR,_F_,"swIsPBKDF2SaltReady()=FALSE")); goto end; }
		if (swPBKDF2(pAESKeyData,AES256_KEY_LEN,pszMasterPwd,gSalts.bufPBKDF2KeySalt,PBKDF2_SALT_LEN,10000)!=0) goto end;
		if (swCreateAESKeyFromKeyData(pAESKeyData,phKey)!=0) goto end;
	}
	if (!brc) { TRACE((TRACE_ERROR,_F_,"CryptDeriveKey()=0x%08lx",GetLastError())); goto end; }
	rc=0;
end:
	if (hHash!=NULL) CryptDestroyHash(hHash);
	TRACE((TRACE_LEAVE,_F_,"rc=%d",rc));
	return rc;
}
bool Certificate::verifySignature(RSA *key)
{
	bool res = false;
	
	if (!key)
		return false;

	if (verified)
		return true;
	
	EVP_PKEY *pkey = EVP_PKEY_new();
	
	if (!pkey) {
		HAGGLE_ERR("Could not allocate EVP_PKEY\n");
		writeErrors("");
		return false;
	}
	
	EVP_PKEY_set1_RSA(pkey, key);
	
        res = verifySignature(pkey);
	
	EVP_PKEY_free(pkey);
		
	return res;
}
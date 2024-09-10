int smpd_hash(char *input, int input_length, char *output, int output_length)
{
    /*DWORD i;*/
    CRYPT_HASH_MESSAGE_PARA      hash_parameter;
    const BYTE*                  hash_buffer[1];
    DWORD                        hash_buffer_len[1];
    CRYPT_ALGORITHM_IDENTIFIER   algorithm;
    BYTE                         hash[HASH_LENGTH];
    DWORD                        hash_len = HASH_LENGTH;

    smpd_enter_fn(FCNAME);

    if (output_length < (HASH_LENGTH * 2 + 1))
    {
	smpd_exit_fn(FCNAME);
	return SMPD_FAIL;
    }

    hash_buffer[0] = (const BYTE *)input;
    hash_buffer_len[0] = input_length;

    /* Initialize the CRYPT_ALGORITHM_IDENTIFIER data structure. */
    algorithm.pszObjId = szOID_RSA_MD5;
    algorithm.Parameters.cbData=0;

    /* Initialize the CRYPT_HASH_MESSAGE_PARA data structure. */
    hash_parameter.cbSize = sizeof(CRYPT_HASH_MESSAGE_PARA);
    hash_parameter.dwMsgEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;
    hash_parameter.hCryptProv = (HCRYPTPROV)NULL;
    hash_parameter.HashAlgorithm = algorithm;
    hash_parameter.pvHashAuxInfo = NULL;

    /* Calculate the size of the hashed message. */
    /*
    if (!CryptHashMessage(&hash_parameter, FALSE, 1, hash_buffer, hash_buffer_len, NULL, NULL, NULL, &hash_len))
    {
	return SMPD_FAIL;
    }
    if (hash_len > HASH_LENGTH)
    {
	return SMPD_FAIL;
    }
    */

    /* Hash the message. */
    if (CryptHashMessage(&hash_parameter, FALSE, 1, hash_buffer, hash_buffer_len, NULL, NULL, hash, &hash_len))
    {
	/*
	for (i=0; i<hash_len; i++)
	{
	    sprintf(output, "%02x", hash[i]);
	    output += 2;
	}
	*/
	sprintf(output, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
	    hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7],
	    hash[8], hash[9], hash[10], hash[11], hash[12], hash[13], hash[14], hash[15]);
    }
    else
    {
	smpd_exit_fn(FCNAME);
	return SMPD_FAIL;
    }

    smpd_exit_fn(FCNAME);
    return 0;
}
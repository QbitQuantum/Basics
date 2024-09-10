static void setup_x509_schannel_create_mocks(void)
{
    STRICT_EXPECTED_CALL(gballoc_malloc(IGNORED_NUM_ARG)); /*this is creating the handle storage space*/
    STRICT_EXPECTED_CALL(CryptStringToBinaryA("certificate", 0, CRYPT_STRING_ANY, NULL, IGNORED_PTR_ARG, NULL, NULL)); /*this is asking for "how big is the certificate binary size?"*/
    STRICT_EXPECTED_CALL(gballoc_malloc(IGNORED_NUM_ARG)); /*this is creating the binary storage for the certificate*/
    STRICT_EXPECTED_CALL(CryptStringToBinaryA("certificate", 0, CRYPT_STRING_ANY, IGNORED_PTR_ARG, IGNORED_PTR_ARG, NULL, NULL)); /*this is asking for "fill in the certificate in this binary buffer"*/
    STRICT_EXPECTED_CALL(CryptStringToBinaryA("private key", 0, CRYPT_STRING_ANY, NULL, IGNORED_PTR_ARG, NULL, NULL)); /*this is asking for "how big is the private key binary size?"*/
    STRICT_EXPECTED_CALL(gballoc_malloc(IGNORED_NUM_ARG)); /*this is creating the binary storage for the private key*/
    STRICT_EXPECTED_CALL(CryptStringToBinaryA("private key", 0, CRYPT_STRING_ANY, IGNORED_PTR_ARG, IGNORED_PTR_ARG, NULL, NULL)); /*this is asking for "fill in the private key in this binary buffer"*/
    STRICT_EXPECTED_CALL(CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, IGNORED_PTR_ARG, IGNORED_NUM_ARG, 0, NULL, NULL, IGNORED_PTR_ARG)); /*this is asking "how big is the decoded private key? (from binary)*/
    STRICT_EXPECTED_CALL(gballoc_malloc(IGNORED_NUM_ARG)); /*this is allocating space for the decoded private key*/
    STRICT_EXPECTED_CALL(CryptDecodeObjectEx(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, IGNORED_PTR_ARG, IGNORED_NUM_ARG, 0, NULL, IGNORED_PTR_ARG, IGNORED_PTR_ARG)); /*this is asking "how big is the decoded private key? (from binary)*/
    STRICT_EXPECTED_CALL(CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, IGNORED_PTR_ARG, IGNORED_NUM_ARG)); /*create a certificate context from an encoded certificate*/
    STRICT_EXPECTED_CALL(CryptAcquireContextA(IGNORED_PTR_ARG, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)); /*this is acquire a handle to a key container within a cryptographic service provider*/
    STRICT_EXPECTED_CALL(CryptImportKey((HCRYPTPROV)IGNORED_PTR_ARG, IGNORED_PTR_ARG, IGNORED_NUM_ARG, (HCRYPTKEY)NULL, 0, IGNORED_PTR_ARG)) /*tranferring the key from the blob to the cryptrographic key provider*/
        .IgnoreArgument_hProv();
    STRICT_EXPECTED_CALL(CertSetCertificateContextProperty(IGNORED_PTR_ARG, CERT_KEY_PROV_HANDLE_PROP_ID, 0, IGNORED_PTR_ARG)); /*give the private key*/
    STRICT_EXPECTED_CALL(gballoc_free(IGNORED_PTR_ARG));
    STRICT_EXPECTED_CALL(gballoc_free(IGNORED_PTR_ARG));
    STRICT_EXPECTED_CALL(gballoc_free(IGNORED_PTR_ARG));
}
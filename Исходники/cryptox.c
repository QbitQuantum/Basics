/**
 * Obtains the public key for the passed in cert data
 *
 * @param provider        The crypto provider
 * @param certData        Data of the certificate to extract the public key from
 * @param sizeOfCertData  The size of the certData buffer
 * @param certStore       Pointer to the handle of the certificate store to use
 * @param CryptoX_Success on success
*/
CryptoX_Result
CryptoAPI_LoadPublicKey(HCRYPTPROV provider,
                        BYTE *certData,
                        DWORD sizeOfCertData,
                        HCRYPTKEY *publicKey)
{
  CRYPT_DATA_BLOB blob;
  CERT_CONTEXT *context;
  if (!provider || !certData || !publicKey) {
    return CryptoX_Error;
  }

  blob.cbData = sizeOfCertData;
  blob.pbData = certData;
  if (!CryptQueryObject(CERT_QUERY_OBJECT_BLOB, &blob,
                        CERT_QUERY_CONTENT_FLAG_CERT,
                        CERT_QUERY_FORMAT_FLAG_BINARY,
                        0, NULL, NULL, NULL,
                        NULL, NULL, (const void **)&context)) {
    return CryptoX_Error;
  }

  if (!CryptImportPublicKeyInfo(provider,
                                PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
                                &context->pCertInfo->SubjectPublicKeyInfo,
                                publicKey)) {
    CertFreeCertificateContext(context);
    return CryptoX_Error;
  }

  CertFreeCertificateContext(context);
  return CryptoX_Success;
}
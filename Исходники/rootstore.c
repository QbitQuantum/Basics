/* Reads any base64-encoded certificates present in fp and adds them to store.
 * Returns TRUE if any certificates were successfully imported.
 */
static BOOL import_base64_certs_from_fp(FILE *fp, HCERTSTORE store)
{
    char line[1024];
    BOOL in_cert = FALSE;
    struct DynamicBuffer saved_cert = { 0, 0, NULL };
    int num_certs = 0;

    TRACE("\n");
    while (fgets(line, sizeof(line), fp))
    {
        static const char header[] = "-----BEGIN CERTIFICATE-----";
        static const char trailer[] = "-----END CERTIFICATE-----";

        if (!strncmp(line, header, strlen(header)))
        {
            TRACE("begin new certificate\n");
            in_cert = TRUE;
            reset_buffer(&saved_cert);
        }
        else if (!strncmp(line, trailer, strlen(trailer)))
        {
            DWORD size;

            TRACE("end of certificate, adding cert\n");
            in_cert = FALSE;
            if (CryptStringToBinaryA((char *)saved_cert.data, saved_cert.used,
             CRYPT_STRING_BASE64, NULL, &size, NULL, NULL))
            {
                LPBYTE buf = CryptMemAlloc(size);

                if (buf)
                {
                    CryptStringToBinaryA((char *)saved_cert.data,
                     saved_cert.used, CRYPT_STRING_BASE64, buf, &size, NULL,
                     NULL);
                    if (CertAddEncodedCertificateToStore(store,
                     X509_ASN_ENCODING, buf, size, CERT_STORE_ADD_NEW, NULL))
                        num_certs++;
                    CryptMemFree(buf);
                }
            }
        }
        else if (in_cert)
            add_line_to_buffer(&saved_cert, line);
    }
    CryptMemFree(saved_cert.data);
    TRACE("Read %d certs\n", num_certs);
    return num_certs > 0;
}
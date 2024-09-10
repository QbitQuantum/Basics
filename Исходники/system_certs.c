// This imports the certificates in a given Windows certificate store into an
// X509_STORE for
// openssl to use during certificate validation.
static int importCertStoreToX509_STORE(
    LPWSTR storeName, DWORD storeLocation, X509_STORE* verifyStore, char* err, size_t err_len) {
    int status = 1;
    X509* x509Cert = NULL;
    HCERTSTORE systemStore =
        CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, (HCRYPTPROV)NULL, storeLocation | CERT_STORE_READONLY_FLAG, storeName);
    if (systemStore == NULL) {
	formatError(GetLastError(),"error opening system CA store",err,err_len);
        status = 0;
        goto CLEANUP;
    }

    PCCERT_CONTEXT certCtx = NULL;
    while ((certCtx = CertEnumCertificatesInStore(systemStore, certCtx)) != NULL) {
        const uint8_t * certBytes = (const uint8_t *)(certCtx->pbCertEncoded);
        x509Cert = d2i_X509(NULL, &certBytes, certCtx->cbCertEncoded);
        if (x509Cert == NULL) {
	    // 120 from the SSL documentation for ERR_error_string
            static const size_t msglen = 120;
            char msg[msglen];
            ERR_error_string_n(ERR_get_error(), msg, msglen);
            snprintf(
                err, err_len, "Error parsing X509 object from Windows certificate store %s", msg);
            status = 0;
            goto CLEANUP;
        }

        if (1 != X509_STORE_add_cert(verifyStore, x509Cert)) {
            int store_error_status = checkX509_STORE_error(err, err_len);
            if (!store_error_status) {
                status = 0;
                goto CLEANUP;
            }
        }
    }
    DWORD lastError = GetLastError();
    if (lastError != CRYPT_E_NOT_FOUND) {
	formatError(lastError,"Error enumerating certificates",err,err_len);
        status = 0;
        goto CLEANUP;
    }

CLEANUP:
    if (systemStore != NULL) {
        CertCloseStore(systemStore, 0);
    }
    if (x509Cert != NULL) {
        X509_free(x509Cert);
    }
    return status;
}
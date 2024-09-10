SECURITY_STATUS schan_imp_get_session_peer_certificate(schan_imp_session session, HCERTSTORE store,
                                                       PCCERT_CONTEXT *ret)
{
    gnutls_session_t s = (gnutls_session_t)session;
    PCCERT_CONTEXT cert = NULL;
    const gnutls_datum_t *datum;
    unsigned list_size, i;
    BOOL res;

    datum = pgnutls_certificate_get_peers(s, &list_size);
    if(!datum)
        return SEC_E_INTERNAL_ERROR;

    for(i = 0; i < list_size; i++) {
        res = CertAddEncodedCertificateToStore(store, X509_ASN_ENCODING, datum[i].data, datum[i].size,
                CERT_STORE_ADD_REPLACE_EXISTING, i ? NULL : &cert);
        if(!res) {
            if(i)
                CertFreeCertificateContext(cert);
            return GetLastError();
        }
    }

    *ret = cert;
    return SEC_E_OK;
}
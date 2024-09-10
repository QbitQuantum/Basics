SECURITY_STATUS schan_imp_get_session_peer_certificate(schan_imp_session session, HCERTSTORE store,
                                                       PCCERT_CONTEXT *ret_cert)
{
    struct mac_session* s = (struct mac_session*)session;
    SECURITY_STATUS ret = SEC_E_OK;
    PCCERT_CONTEXT cert = NULL;
    SecCertificateRef mac_cert;
    CFArrayRef cert_array;
    int status;
    CFIndex cnt, i;
    CFDataRef data;
    BOOL res;

    TRACE("(%p/%p, %p)\n", s, s->context, cert);

#ifdef HAVE_SSLCOPYPEERCERTIFICATES
    status = SSLCopyPeerCertificates(s->context, &cert_array);
#else
    status = SSLGetPeerCertificates(s->context, &cert_array);
#endif
    if (status != noErr || !cert_array)
    {
        WARN("SSLCopyPeerCertificates failed: %d\n", status);
        return SEC_E_INTERNAL_ERROR;
    }

    cnt = CFArrayGetCount(cert_array);
    for (i=0; i < cnt; i++) {
        if (!(mac_cert = (SecCertificateRef)CFArrayGetValueAtIndex(cert_array, i)) ||
            (SecKeychainItemExport(mac_cert, kSecFormatX509Cert, 0, NULL, &data) != noErr))
        {
            WARN("Couldn't extract certificate data\n");
            ret = SEC_E_INTERNAL_ERROR;
            break;
        }

        res = CertAddEncodedCertificateToStore(store, X509_ASN_ENCODING, CFDataGetBytePtr(data), CFDataGetLength(data),
                                               CERT_STORE_ADD_REPLACE_EXISTING, i ? NULL : &cert);
        CFRelease(data);
        if (!res)
        {
            ret = GetLastError();
            WARN("CertAddEncodedCertificateToStore failed: %x\n", ret);
            break;
        }
    }

#ifndef HAVE_SSLCOPYPEERCERTIFICATES
    /* This is why SSLGetPeerCertificates was deprecated */
    CFArrayApplyFunction(cert_array, CFRangeMake(0, CFArrayGetCount(cert_array)),
                         schan_imp_cf_release, NULL);
#endif
    CFRelease(cert_array);
    if (ret != SEC_E_OK) {
        if(cert)
            CertFreeCertificateContext(cert);
        return ret;
    }

    *ret_cert = cert;
    return SEC_E_OK;
}
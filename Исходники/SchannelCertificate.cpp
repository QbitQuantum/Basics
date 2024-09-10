SchannelCertificate::SchannelCertificate(const ByteArray& der)
{
    if (!der.empty())
    {
        // Convert the DER encoded certificate to a PCERT_CONTEXT
        CERT_BLOB certBlob = {0};
        certBlob.cbData = der.size();
        certBlob.pbData = (BYTE*)&der[0];

        if (!CryptQueryObject(
            CERT_QUERY_OBJECT_BLOB,
            &certBlob,
            CERT_QUERY_CONTENT_FLAG_CERT,
            CERT_QUERY_FORMAT_FLAG_ALL,
            0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            (const void**)m_cert.Reset()))
        {
            // TODO: Because Swiften isn't exception safe, we have no way to indicate failure
        }
    }
}
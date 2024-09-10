NS_IMETHODIMP
nsRecentBadCertsService::GetRecentBadCert(const nsAString & aHostNameWithPort, 
                                          nsISSLStatus **aStatus)
{
  NS_ENSURE_ARG_POINTER(aStatus);
  if (!aHostNameWithPort.Length())
    return NS_ERROR_INVALID_ARG;

  *aStatus = nullptr;
  nsRefPtr<nsSSLStatus> status = new nsSSLStatus();
  if (!status)
    return NS_ERROR_OUT_OF_MEMORY;

  SECItem foundDER;
  foundDER.len = 0;
  foundDER.data = nullptr;

  bool isDomainMismatch = false;
  bool isNotValidAtThisTime = false;
  bool isUntrusted = false;

  {
    ReentrantMonitorAutoEnter lock(monitor);
    for (size_t i=0; i<const_recently_seen_list_size; ++i) {
      if (mCerts[i].mHostWithPort.Equals(aHostNameWithPort)) {
        SECStatus srv = SECITEM_CopyItem(nullptr, &foundDER, &mCerts[i].mDERCert);
        if (srv != SECSuccess)
          return NS_ERROR_OUT_OF_MEMORY;

        isDomainMismatch = mCerts[i].isDomainMismatch;
        isNotValidAtThisTime = mCerts[i].isNotValidAtThisTime;
        isUntrusted = mCerts[i].isUntrusted;
      }
    }
  }

  if (foundDER.len) {
    CERTCertificate *nssCert;
    CERTCertDBHandle *certdb = CERT_GetDefaultCertDB();
    nssCert = CERT_FindCertByDERCert(certdb, &foundDER);
    if (!nssCert) 
      nssCert = CERT_NewTempCertificate(certdb, &foundDER,
                                        nullptr, // no nickname
                                        false, // not perm
                                        true); // copy der

    SECITEM_FreeItem(&foundDER, false);

    if (!nssCert)
      return NS_ERROR_FAILURE;

    status->mServerCert = nsNSSCertificate::Create(nssCert);
    CERT_DestroyCertificate(nssCert);

    status->mHaveCertErrorBits = true;
    status->mIsDomainMismatch = isDomainMismatch;
    status->mIsNotValidAtThisTime = isNotValidAtThisTime;
    status->mIsUntrusted = isUntrusted;

    *aStatus = status;
    NS_IF_ADDREF(*aStatus);
  }

  return NS_OK;
}
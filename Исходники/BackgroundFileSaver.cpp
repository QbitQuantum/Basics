nsresult
BackgroundFileSaver::ExtractSignatureInfo(const nsAString& filePath)
{
  MOZ_ASSERT(!NS_IsMainThread(), "Cannot extract signature on main thread");

  nsNSSShutDownPreventionLock nssLock;
  if (isAlreadyShutDown()) {
    return NS_ERROR_NOT_AVAILABLE;
  }
  {
    MutexAutoLock lock(mLock);
    if (!mSignatureInfoEnabled) {
      return NS_OK;
    }
  }
  nsresult rv;
  nsCOMPtr<nsIX509CertDB> certDB = do_GetService(NS_X509CERTDB_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
#ifdef XP_WIN
  // Setup the file to check.
  WINTRUST_FILE_INFO fileToCheck = {0};
  fileToCheck.cbStruct = sizeof(WINTRUST_FILE_INFO);
  fileToCheck.pcwszFilePath = filePath.Data();
  fileToCheck.hFile = nullptr;
  fileToCheck.pgKnownSubject = nullptr;

  // We want to check it is signed and trusted.
  WINTRUST_DATA trustData = {0};
  trustData.cbStruct = sizeof(trustData);
  trustData.pPolicyCallbackData = nullptr;
  trustData.pSIPClientData = nullptr;
  trustData.dwUIChoice = WTD_UI_NONE;
  trustData.fdwRevocationChecks = WTD_REVOKE_NONE;
  trustData.dwUnionChoice = WTD_CHOICE_FILE;
  trustData.dwStateAction = WTD_STATEACTION_VERIFY;
  trustData.hWVTStateData = nullptr;
  trustData.pwszURLReference = nullptr;
  // Disallow revocation checks over the network
  trustData.dwProvFlags = WTD_CACHE_ONLY_URL_RETRIEVAL;
  // no UI
  trustData.dwUIContext = 0;
  trustData.pFile = &fileToCheck;

  // The WINTRUST_ACTION_GENERIC_VERIFY_V2 policy verifies that the certificate
  // chains up to a trusted root CA and has appropriate permissions to sign
  // code.
  GUID policyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
  // Check if the file is signed by something that is trusted. If the file is
  // not signed, this is a no-op.
  LONG ret = WinVerifyTrust(nullptr, &policyGUID, &trustData);
  CRYPT_PROVIDER_DATA* cryptoProviderData = nullptr;
  // According to the Windows documentation, we should check against 0 instead
  // of ERROR_SUCCESS, which is an HRESULT.
  if (ret == 0) {
    cryptoProviderData = WTHelperProvDataFromStateData(trustData.hWVTStateData);
  }
  if (cryptoProviderData) {
    // Lock because signature information is read on the main thread.
    MutexAutoLock lock(mLock);
    LOG(("Downloaded trusted and signed file [this = %p].", this));
    // A binary may have multiple signers. Each signer may have multiple certs
    // in the chain.
    for (DWORD i = 0; i < cryptoProviderData->csSigners; ++i) {
      const CERT_CHAIN_CONTEXT* certChainContext =
        cryptoProviderData->pasSigners[i].pChainContext;
      if (!certChainContext) {
        break;
      }
      for (DWORD j = 0; j < certChainContext->cChain; ++j) {
        const CERT_SIMPLE_CHAIN* certSimpleChain =
          certChainContext->rgpChain[j];
        if (!certSimpleChain) {
          break;
        }
        nsCOMPtr<nsIX509CertList> nssCertList =
          do_CreateInstance(NS_X509CERTLIST_CONTRACTID);
        if (!nssCertList) {
          break;
        }
        bool extractionSuccess = true;
        for (DWORD k = 0; k < certSimpleChain->cElement; ++k) {
          CERT_CHAIN_ELEMENT* certChainElement = certSimpleChain->rgpElement[k];
          if (certChainElement->pCertContext->dwCertEncodingType !=
            X509_ASN_ENCODING) {
              continue;
          }
          nsCOMPtr<nsIX509Cert> nssCert = nullptr;
          rv = certDB->ConstructX509(
            reinterpret_cast<char *>(
              certChainElement->pCertContext->pbCertEncoded),
            certChainElement->pCertContext->cbCertEncoded,
            getter_AddRefs(nssCert));
          if (!nssCert) {
            extractionSuccess = false;
            LOG(("Couldn't create NSS cert [this = %p]", this));
            break;
          }
          nssCertList->AddCert(nssCert);
          nsString subjectName;
          nssCert->GetSubjectName(subjectName);
          LOG(("Adding cert %s [this = %p]",
               NS_ConvertUTF16toUTF8(subjectName).get(), this));
        }
        if (extractionSuccess) {
          mSignatureInfo.AppendObject(nssCertList);
        }
      }
    }
    // Free the provider data if cryptoProviderData is not null.
    trustData.dwStateAction = WTD_STATEACTION_CLOSE;
    WinVerifyTrust(nullptr, &policyGUID, &trustData);
  } else {
    LOG(("Downloaded unsigned or untrusted file [this = %p].", this));
  }
#endif
  return NS_OK;
}
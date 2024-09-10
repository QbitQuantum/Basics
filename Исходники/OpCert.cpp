HRESULT COpCertRemove::Execute(CSession *pSession)
{
    DWORD dwError;
    HCERTSTORE hCertStore;

    // Open certificate store.
    hCertStore = ::CertOpenStore(CERT_STORE_PROV_SYSTEM_W, m_dwEncodingType, NULL, m_dwFlags, m_sValue.c_str());
    if (hCertStore) {
        // Create certificate context.
        PCCERT_CONTEXT pCertContext = ::CertCreateCertificateContext(m_dwEncodingType, m_binCert.data(), static_cast<DWORD>(m_binCert.size()));
        if (pCertContext) {
            PMSIHANDLE hRecordMsg = ::MsiCreateRecord(1);
            std::wstring sCertName;
            PCCERT_CONTEXT pCertContextExisting;

            // Display our custom message in the progress bar.
            ::CertGetNameStringW(pCertContext, CERT_NAME_FRIENDLY_DISPLAY_TYPE, 0, NULL, sCertName);
            ::MsiRecordSetStringW(hRecordMsg, 1, sCertName.c_str());
            if (MsiProcessMessage(pSession->m_hInstall, INSTALLMESSAGE_ACTIONDATA, hRecordMsg) == IDCANCEL)
                return HRESULT_FROM_WIN32(ERROR_INSTALL_USEREXIT);

            pCertContextExisting = ::CertFindCertificateInStore(hCertStore, m_dwEncodingType, 0, CERT_FIND_EXISTING, pCertContext, NULL);
            if (pCertContextExisting) {
                // Delete certificate from certificate store.
                if (::CertDeleteCertificateFromStore(pCertContextExisting)) {
                    if (pSession->m_bRollbackEnabled) {
                        // Order rollback action to reinstall the certificate.
                        pSession->m_olRollback.push_front(new COpCertInstall(m_binCert.data(), m_binCert.size(), m_sValue.c_str(), m_dwEncodingType, m_dwFlags));
                    }
                    dwError = NO_ERROR;
                } else {
                    dwError = ::GetLastError();
                    ::CertFreeCertificateContext(pCertContextExisting);
                }
            } else {
                // We haven't found the certificate. Nothing to delete then.
                dwError = NO_ERROR;
            }
            ::CertFreeCertificateContext(pCertContext);
        } else
            dwError = ::GetLastError();
        ::CertCloseStore(hCertStore, 0);
    } else
        dwError = ::GetLastError();

    if (dwError == NO_ERROR)
        return S_OK;
    else {
        PMSIHANDLE hRecordProg = ::MsiCreateRecord(3);
        ::MsiRecordSetInteger(hRecordProg, 1, ERROR_INSTALL_CERT_REMOVE);
        ::MsiRecordSetStringW(hRecordProg, 2, m_sValue.c_str()         );
        ::MsiRecordSetInteger(hRecordProg, 3, dwError                  );
        ::MsiProcessMessage(pSession->m_hInstall, INSTALLMESSAGE_ERROR, hRecordProg);
        return HRESULT_FROM_WIN32(dwError);
    }
}
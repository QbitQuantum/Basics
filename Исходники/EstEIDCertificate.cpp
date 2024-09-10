void CEstEIDCertificate::readFromCertContext() {
	PCCERT_CONTEXT certContext = NULL;
	HCERTSTORE cert_store = NULL;

	cert_store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_READONLY_FLAG, L"MY");
	if(!cert_store){
		throw CryptoException();
	}

	if(!CertFindCertificateInStore(cert_store, X509_ASN_ENCODING  | PKCS_7_ASN_ENCODING, 0, CERT_FIND_ANY, NULL, NULL)) {
		CertCloseStore(cert_store, CERT_CLOSE_STORE_FORCE_FLAG);
		throw CryptoException();
	}
	
	while(certContext = CertFindCertificateInStore(cert_store, X509_ASN_ENCODING  | PKCS_7_ASN_ENCODING, 0, CERT_FIND_ANY, NULL, certContext)) {
		BYTE keyUsage;
		CertGetIntendedKeyUsage(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, certContext->pCertInfo, &keyUsage, 1);
		if (keyUsage & CERT_NON_REPUDIATION_KEY_USAGE) {
			this->certificates.push_back(CertDuplicateCertificateContext(certContext));
		}	
	}
	
	//PCCERT_CONTEXT ct = CryptUIDlgSelectCertificateFromStore(cert_store, NULL, L"TIITEL", L"Vali cert:", NULL, 0, 0);
	//loadCertContexts(ct);
	CCertificateSelectionDlg *dlg = new CCertificateSelectionDlg();
	dlg->setCertificate(this->certificates);
	INT_PTR selectedItem = dlg->DoModal();
	EstEID_log("selected item index = %i", selectedItem);
	
	if(selectedItem == -1) {
		throw CryptoException(ESTEID_USER_CANCEL);
	}
	loadCertContexts(this->certificates[selectedItem]);

	if(certContext){
		CertFreeCertificateContext(certContext);
	}
	if(cert_store) {
		CertCloseStore(cert_store, CERT_CLOSE_STORE_FORCE_FLAG);
	}
}
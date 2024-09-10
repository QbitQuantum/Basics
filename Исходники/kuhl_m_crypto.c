NTSTATUS kuhl_m_crypto_l_certificates(int argc, wchar_t * argv[])
{
	HCERTSTORE hCertificateStore;
	PCCERT_CONTEXT pCertContext;
	DWORD i, j, dwSizeNeeded, keySpec;
	wchar_t *certName;
	PCRYPT_KEY_PROV_INFO pBuffer;
	HCRYPTPROV_OR_NCRYPT_KEY_HANDLE monProv;
	HCRYPTKEY maCle;
	BOOL keyToFree;

	PCWCHAR szSystemStore, szStore;
	DWORD dwSystemStore = 0;

	BOOL export = kull_m_string_args_byName(argc, argv, L"export", NULL, NULL);

	kull_m_string_args_byName(argc, argv, L"systemstore", &szSystemStore, kuhl_m_crypto_system_stores[0].name);
	dwSystemStore = kuhl_m_crypto_system_store_to_dword(szSystemStore);
	kull_m_string_args_byName(argc, argv, L"store", &szStore, L"My");

	kprintf(L" * System Store  : \'%s\' (0x%08x)\n"
			L" * Store         : \'%s\'\n\n",
			szSystemStore, dwSystemStore,
			szStore);

	if(hCertificateStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, (HCRYPTPROV_LEGACY) NULL, dwSystemStore | CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG, szStore))
	{
		for (i = 0, pCertContext = CertEnumCertificatesInStore(hCertificateStore, NULL); pCertContext != NULL; pCertContext = CertEnumCertificatesInStore(hCertificateStore, pCertContext), i++)
		{
			for(j = 0; j < ARRAYSIZE(nameSrc); j++)
			{
				dwSizeNeeded = CertGetNameString(pCertContext, nameSrc[j], 0, NULL, NULL, 0);
				if(dwSizeNeeded > 0)
				{
					if(certName = (wchar_t *) LocalAlloc(LPTR, dwSizeNeeded * sizeof(wchar_t)))
					{
						if(CertGetNameString(pCertContext, nameSrc[j], 0, NULL, certName, dwSizeNeeded) == dwSizeNeeded)
						{
							kprintf(L"%2u. %s\n", i, certName);

							dwSizeNeeded = 0;
							if(CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, NULL, &dwSizeNeeded))
							{
								if(pBuffer = (PCRYPT_KEY_PROV_INFO) LocalAlloc(LPTR, dwSizeNeeded))
								{
									if(CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, pBuffer, &dwSizeNeeded))
									{
										kprintf(
											L"\tKey Container  : %s\n"
											L"\tProvider       : %s\n",
											(pBuffer->pwszContainerName ? pBuffer->pwszContainerName : L"(null)"),
											(pBuffer->pwszProvName ? pBuffer->pwszProvName : L"(null)"));
										
										if(CryptAcquireCertificatePrivateKey(pCertContext, CRYPT_ACQUIRE_ALLOW_NCRYPT_KEY_FLAG /* CRYPT_ACQUIRE_SILENT_FLAG NULL */, NULL, &monProv, &keySpec, &keyToFree))
										{
											kprintf(L"\tType           : %s (0x%08x)\n", kuhl_m_crypto_keytype_to_str(keySpec), keySpec);

											if(keySpec != CERT_NCRYPT_KEY_SPEC)
											{
												if(CryptGetUserKey(monProv, keySpec, &maCle))
												{
													kuhl_m_crypto_printKeyInfos(0, maCle);
													CryptDestroyKey(maCle);
												}
												else PRINT_ERROR_AUTO(L"CryptGetUserKey");

												if(keyToFree)
													CryptReleaseContext(monProv, 0);
											}
											else if(kuhl_m_crypto_hNCrypt)
											{
												kuhl_m_crypto_printKeyInfos(monProv, 0);
												if(keyToFree)
													K_NCryptFreeObject(monProv);
											}
											else PRINT_ERROR(L"keySpec == CERT_NCRYPT_KEY_SPEC without CNG Handle ?\n");

										} else PRINT_ERROR_AUTO(L"CryptAcquireCertificatePrivateKey");
									} else PRINT_ERROR_AUTO(L"CertGetCertificateContextProperty");
								}
								LocalFree(pBuffer);
								if(!export)
									kprintf(L"\n");
							}

							if(export)
								kuhl_m_crypto_exportCert(pCertContext, (BOOL) dwSizeNeeded, szSystemStore, szStore, i, certName);

						} else PRINT_ERROR_AUTO(L"CertGetNameString");
						LocalFree(certName);
					}
					break;
				} else PRINT_ERROR_AUTO(L"CertGetNameString (for len)");	
			}
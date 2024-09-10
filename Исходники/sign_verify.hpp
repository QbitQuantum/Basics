        BOOL GetCatSignSubject(LPCWSTR FileFullPath, std::vector<std::string>& subInfo)
        {
            BOOL fRetval = FALSE;
            LPBYTE Hash = NULL;
            DWORD HashSize;
            CATALOG_INFO CatInfo;
            HANDLE hFile = NULL;
            HCATADMIN hCatAdmin;
            HCATINFO hCatInfo;
            HCATINFO PrevCat;
            DWORD Err;
            WINTRUST_DATA WintrustData;
            WINTRUST_CATALOG_INFO WintrustCatalogInfo;
            LPWSTR CatalogFullPath;
            WCHAR UnicodeKey[MAX_PATH];
            GUID DriverVerifyGuid = DRIVER_ACTION_VERIFY;
            PWCHAR Key = NULL;

            if (NULL == m_pWinVerifyTrust) {

                return FALSE;
            }

            StringCchCopyW( UnicodeKey, MAX_PATH, FileFullPath );
            Key = MyGetFileTitle( UnicodeKey );

            if (!m_pCryptCATAdminAcquireContext( &hCatAdmin, &DriverVerifyGuid, 0 )) {

                goto clean0;
            }

            hFile = CreateFileW( FileFullPath,
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE |FILE_SHARE_DELETE,
                NULL,
                OPEN_EXISTING,
                0,
                NULL );

            if (INVALID_HANDLE_VALUE == hFile) {

                goto clean0;
            }

            ZeroMemory(&WintrustData, sizeof(WINTRUST_DATA));
            WintrustData.cbStruct = sizeof(WINTRUST_DATA);
            WintrustData.dwUIChoice = WTD_UI_NONE;
            WintrustData.fdwRevocationChecks = WTD_REVOKE_NONE;
            WintrustData.dwStateAction = WTD_STATEACTION_AUTO_CACHE;
            WintrustData.dwProvFlags = WTD_REVOCATION_CHECK_NONE;

            HashSize = 100;
            Hash = new BYTE[HashSize];

            if(NULL == Hash) {

                goto clean0;
            }

            if (!m_pCryptCATAdminCalcHashFromFileHandle( hFile, &HashSize, Hash, 0 )) {

                goto clean0;
            }

            WintrustData.dwUnionChoice = WTD_CHOICE_CATALOG;
            WintrustData.pCatalog = &WintrustCatalogInfo;

            ZeroMemory(&WintrustCatalogInfo, sizeof(WINTRUST_CATALOG_INFO));
            WintrustCatalogInfo.cbStruct = sizeof(WINTRUST_CATALOG_INFO);
            WintrustCatalogInfo.pbCalculatedFileHash = Hash;
            WintrustCatalogInfo.cbCalculatedFileHash = HashSize;

            StringCchCopyW( UnicodeKey, MAX_PATH, Key);
            CharLowerW( UnicodeKey );

            WintrustCatalogInfo.pcwszMemberTag = UnicodeKey;

            PrevCat = NULL;
            hCatInfo = m_pCryptCATAdminEnumCatalogFromHash(
                hCatAdmin,
                Hash,
                HashSize,
                0,
                &PrevCat );

            while (hCatInfo) {
                CatInfo.cbStruct = sizeof(CATALOG_INFO);
                if (m_pCryptCATCatalogInfoFromContext( hCatInfo, &CatInfo, 0 )) {

                    CatalogFullPath = CatInfo.wszCatalogFile;
                    WintrustCatalogInfo.pcwszCatalogFilePath = CatInfo.wszCatalogFile;

                    Err = (DWORD)m_pWinVerifyTrust(NULL,
                        &DriverVerifyGuid,
                        &WintrustData
                        );

                    if (NO_ERROR  == Err) {

                        if (GetEmbedSignSubject(CatInfo.wszCatalogFile, subInfo))
                        {
                            CHAR szInfo[1024] = {0};

                            WideCharToMultiByte( CP_ACP,
                                0,
                                CatInfo.wszCatalogFile,
                                -1,
                                szInfo,
                                1024,
                                NULL,
                                NULL );
                            subInfo.push_back(std::string(szInfo));
                            // m_pCryptCATAdminReleaseCatalogContext( hCatAdmin, hCatInfo, 0 );

                            fRetval = TRUE;
                            break;
                        }
                    }
                }

                PrevCat = hCatInfo;

                hCatInfo = m_pCryptCATAdminEnumCatalogFromHash(
                    hCatAdmin, Hash, HashSize, 0, &PrevCat );

            }

clean0:
            if (Hash) {

                delete[] Hash;
                Hash = NULL;
            }

            if (hCatAdmin) {

                m_pCryptCATAdminReleaseContext( hCatAdmin, 0 );
            }

            if (hFile) {

                ::CloseHandle( hFile );
                hFile = NULL;
            }

            return fRetval;
        }
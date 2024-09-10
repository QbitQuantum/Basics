void    AsmMan::EndAssembly()
{
    if(m_pCurAsmRef)
    {
        if(m_pCurAsmRef->isRef)
        { // list the assembly ref
            if(GetAsmRefByName(m_pCurAsmRef->szAlias))
            {
                //report->warn("Multiple declarations of Assembly Ref '%s', ignored except the 1st one\n",m_pCurAsmRef->szName);
                delete m_pCurAsmRef;
                m_pCurAsmRef = NULL;
                return;
            }
            if(m_pCurAsmRef->isAutodetect)
            {
                IAssemblyName* pIAsmName;
                HRESULT hr;
                // Convert name to Unicode
                WszMultiByteToWideChar(g_uCodePage,0,m_pCurAsmRef->szName,-1,wzUniBuf,dwUniBuf);
                hr = CreateAssemblyNameObject(&pIAsmName,wzUniBuf,CANOF_PARSE_DISPLAY_NAME,NULL);
                if(SUCCEEDED(hr))
                {
                    // set enumeration criteria: what is known about AsmRef (besides name)
                    if(m_pCurAsmRef->usVerMajor != (USHORT)0xFFFF)
                        pIAsmName->SetProperty(ASM_NAME_MAJOR_VERSION,&(m_pCurAsmRef->usVerMajor),2);
                    if(m_pCurAsmRef->usVerMinor != (USHORT)0xFFFF)
                        pIAsmName->SetProperty(ASM_NAME_MINOR_VERSION,&(m_pCurAsmRef->usVerMinor),2);
                    if(m_pCurAsmRef->usBuild != (USHORT)0xFFFF)
                        pIAsmName->SetProperty(ASM_NAME_BUILD_NUMBER,&(m_pCurAsmRef->usBuild),2);
                    if(m_pCurAsmRef->usRevision != (USHORT)0xFFFF)
                        pIAsmName->SetProperty(ASM_NAME_REVISION_NUMBER,&(m_pCurAsmRef->usRevision),2);
                    if(m_pCurAsmRef->pPublicKeyToken)
                        pIAsmName->SetProperty(ASM_NAME_PUBLIC_KEY_TOKEN,
                                               m_pCurAsmRef->pPublicKeyToken->ptr(),
                                               m_pCurAsmRef->pPublicKeyToken->length());
                    if(m_pCurAsmRef->pLocale)
                        pIAsmName->SetProperty(ASM_NAME_CULTURE,
                                               m_pCurAsmRef->pLocale->ptr(),
                                               m_pCurAsmRef->pLocale->length());

                    // enumerate assemblies
                    IAssemblyEnum* pIAsmEnum = NULL;
                    hr = CreateAssemblyEnum(&pIAsmEnum, NULL, pIAsmName, ASM_CACHE_GAC, NULL);
                    if(SUCCEEDED(hr))
                    {
                        IAssemblyName* pIAsmNameFound;
                        IAssemblyName* pIAsmNameLatestVer = NULL;
                        ULONGLONG   ullVer=0, ullVerLatest=0;
                        DWORD  dwVerHi, dwVerLo;
    
                        // find the latest and greatest, if any
                        for(;;)
                        {
                            pIAsmNameFound = NULL;
                            hr = pIAsmEnum->GetNextAssembly(NULL,&pIAsmNameFound,0); 
                            if(SUCCEEDED(hr) && pIAsmNameFound)
                            {
    
                                pIAsmNameFound->GetVersion(&dwVerHi,&dwVerLo);
                                ullVer = (ULONGLONG)dwVerHi;
                                ullVer <<= sizeof(DWORD);
                                ullVer |= dwVerLo;
                                if(ullVer > ullVerLatest)
                                {
                                    if(pIAsmNameLatestVer)
                                       pIAsmNameLatestVer->Release(); 
                                    ullVerLatest = ullVer;
                                    pIAsmNameLatestVer = pIAsmNameFound;
                                }
                                else
                                    pIAsmNameFound->Release();
                            }
                            else break;
                        }
                        // if found, fill the gaps
                        if(pIAsmNameLatestVer)
                        {
                            DWORD cbSize=0;
                            USHORT usDummy=0;

                            if(m_pCurAsmRef->pPublicKeyToken == NULL)
                            {
                                cbSize = 1024;
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_PUBLIC_KEY_TOKEN,
                                                wzUniBuf, &cbSize);
                                if(cbSize)
                                {
                                    if((m_pCurAsmRef->pPublicKeyToken = new BinStr()))
                                        memcpy(m_pCurAsmRef->pPublicKeyToken->getBuff(cbSize),
                                            wzUniBuf, cbSize);
                                }
                            }
    
                            if(m_pCurAsmRef->usVerMajor == (USHORT)0xFFFF)
                            {
                                cbSize = (DWORD)sizeof(WORD);
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_MAJOR_VERSION,
                                                &usDummy, &cbSize);
                                m_pCurAsmRef->usVerMajor = usDummy;
                            }
                            if(m_pCurAsmRef->usVerMinor == (USHORT)0xFFFF)
                            {
                                cbSize = (DWORD)sizeof(WORD);
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_MINOR_VERSION,
                                                &usDummy, &cbSize);
                                m_pCurAsmRef->usVerMinor = usDummy;
                            }
                            if(m_pCurAsmRef->usBuild == (USHORT)0xFFFF)
                            {
                                cbSize = (DWORD)sizeof(WORD);
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_BUILD_NUMBER,
                                                &usDummy, &cbSize);
                                m_pCurAsmRef->usBuild = usDummy;
                            }
                            if(m_pCurAsmRef->usRevision == (USHORT)0xFFFF)
                            {
                                cbSize = (DWORD)sizeof(WORD);
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_REVISION_NUMBER,
                                                &usDummy, &cbSize);
                                m_pCurAsmRef->usRevision = usDummy;
                            }
                            
                            if(m_pCurAsmRef->pLocale == NULL)
                            {
                                cbSize = 1024;
                                pIAsmNameLatestVer->GetProperty(ASM_NAME_CULTURE,
                                                wzUniBuf, &cbSize);

                                if(cbSize > (DWORD)sizeof(WCHAR))
                                {
                                    if((m_pCurAsmRef->pLocale = new BinStr()))
                                        memcpy(m_pCurAsmRef->pLocale->getBuff(cbSize),
                                            wzUniBuf, cbSize);
                                }
                            }
                            pIAsmNameLatestVer->Release(); 
                        }
                        else
                            report->warn("Failed to autodetect assembly '%s'\n",m_pCurAsmRef->szName);
                        // if no assembly found, leave it as is, it might be not a GAC assembly
    
                        pIAsmEnum->Release();
                    }
                    else
                        report->error("Failed to enum assemblies %S, hr=0x%08X\n",wzUniBuf,hr);
                    pIAsmName->Release();
                }
                else
                    report->error("Failed to create assembly name object for %S, hr=0x%08X\n",wzUniBuf,hr);
            } // end if isAutodetect
            m_AsmRefLst.PUSH(m_pCurAsmRef);
            m_pCurAsmRef->tkTok = TokenFromRid(m_AsmRefLst.COUNT(),mdtAssemblyRef);
        }
        else
        {
            HRESULT                 hr = S_OK;
            m_pCurAsmRef->tkTok = TokenFromRid(1,mdtAssembly);
            // Determine the strong name public key. This may have been set
            // via a directive in the source or from the command line (which
            // overrides the directive). From the command line we may have
            // been provided with a file or the name of a CAPI key
            // container. Either may contain a public key or a full key
            // pair.
            if (((Assembler*)m_pAssembler)->m_wzKeySourceName)
            {
                {
                    // Read public key or key pair from file.
                    HANDLE hFile = WszCreateFile(((Assembler*)m_pAssembler)->m_wzKeySourceName,
                                                 GENERIC_READ,
                                                 FILE_SHARE_READ,
                                                 NULL,
                                                 OPEN_EXISTING,
                                                 FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                                                 NULL);
                    if(hFile == INVALID_HANDLE_VALUE)
                    {
                        hr = GetLastError();
                        report->error("Failed to open key file '%S': 0x%08X\n",((Assembler*)m_pAssembler)->m_wzKeySourceName,hr);
                        m_pCurAsmRef = NULL;
                        return;
                    }

                    // Determine file size and allocate an appropriate buffer.
                    m_sStrongName.m_cbPublicKey = SafeGetFileSize(hFile, NULL);
                    if (m_sStrongName.m_cbPublicKey == 0xffffffff) {
                        report->error("File size too large\n");
                        m_pCurAsmRef = NULL;
                        CloseHandle(hFile);
                        return;
                    }

                    m_sStrongName.m_pbPublicKey = new BYTE[m_sStrongName.m_cbPublicKey];
                    if (m_sStrongName.m_pbPublicKey == NULL) {
                        report->error("Failed to allocate key buffer\n");
                        m_pCurAsmRef = NULL;
                        CloseHandle(hFile);
                        return;
                    }
                    m_sStrongName.m_dwPublicKeyAllocated = 2;

                    // Read the file into the buffer.
                    DWORD dwBytesRead;
                    if (!ReadFile(hFile, m_sStrongName.m_pbPublicKey, m_sStrongName.m_cbPublicKey, &dwBytesRead, NULL)) {
                        hr = GetLastError();
                        report->error("Failed to read key file '%S': 0x%08X\n",((Assembler*)m_pAssembler)->m_wzKeySourceName,hr);
                        m_pCurAsmRef = NULL;
                        CloseHandle(hFile);
                        return;
                    }

                    CloseHandle(hFile);

                    // Guess whether we're full or delay signing based on
                    // whether the blob passed to us looks like a public
                    // key. (I.e. we may just have copied a full key pair
                    // into the public key buffer).
                    if (m_sStrongName.m_cbPublicKey >= sizeof(PublicKeyBlob) &&
                        (offsetof(PublicKeyBlob, PublicKey) +
                         ((PublicKeyBlob*)m_sStrongName.m_pbPublicKey)->cbPublicKey) == m_sStrongName.m_cbPublicKey)
                        m_sStrongName.m_fFullSign = FALSE;
                    else
                        m_sStrongName.m_fFullSign = TRUE;

                    // If we really have a key pair, we'll move it into a
                    // key container so the signing code gets the key pair
                    // from a consistent place.
                    if (m_sStrongName.m_fFullSign)
                    {
                        m_sStrongName.m_pbPrivateKey = m_sStrongName.m_pbPublicKey;
                        m_sStrongName.m_cbPrivateKey = m_sStrongName.m_cbPublicKey;

                        m_sStrongName.m_pbPublicKey = NULL;
                        m_sStrongName.m_cbPublicKey = NULL;
                        m_sStrongName.m_dwPublicKeyAllocated = 0;

                        // Retrieve the public key portion as a byte blob.
                        if (!StrongNameGetPublicKey(NULL,
                                                    m_sStrongName.m_pbPrivateKey,
                                                    m_sStrongName.m_cbPrivateKey,
                                                    &m_sStrongName.m_pbPublicKey,
                                                    &m_sStrongName.m_cbPublicKey))
                        {
                            hr = StrongNameErrorInfo();
                            report->error("Failed to extract public key: 0x%08X\n",hr);
                            m_pCurAsmRef = NULL;
                            return;
                        }
    
                        m_sStrongName.m_dwPublicKeyAllocated = 2;
                    }
                }
            }
            else if (m_pAssembly->pPublicKey)
            {
                m_sStrongName.m_pbPublicKey = m_pAssembly->pPublicKey->ptr();
                m_sStrongName.m_cbPublicKey = m_pAssembly->pPublicKey->length();
                m_sStrongName.m_wzKeyContainer = NULL;
                m_sStrongName.m_fFullSign = FALSE;
                m_sStrongName.m_dwPublicKeyAllocated = 0;
            }
            else
            {
                m_sStrongName.m_pbPublicKey = NULL;
                m_sStrongName.m_cbPublicKey = 0;
                m_sStrongName.m_wzKeyContainer = NULL;
                m_sStrongName.m_fFullSign = FALSE;
                m_sStrongName.m_dwPublicKeyAllocated = 0;
            }

        }
        m_pCurAsmRef = NULL;
    }
    ((Assembler*)m_pAssembler)->m_pCustomDescrList = ((Assembler*)m_pAssembler)->m_CustomDescrListStack.POP();
}
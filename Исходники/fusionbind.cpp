HRESULT FusionBind::CreateFusionName(IAssemblyName **ppName, BOOL fIncludeHash)
{
    TIMELINE_START(FUSIONBIND, ("CreateFusionName %s", m_pAssemblyName));

    HRESULT hr;
    IAssemblyName *pFusionAssemblyName = NULL;
    LPWSTR pwAssemblyName = NULL;
    CQuickBytes qb;

    if (m_pAssemblyName) {
        long pwNameLen = WszMultiByteToWideChar(CP_UTF8, 0, m_pAssemblyName, -1, 0, 0);
        pwAssemblyName = (LPWSTR) qb.Alloc(pwNameLen*sizeof(WCHAR));

        WszMultiByteToWideChar(CP_UTF8, 0, m_pAssemblyName, -1, pwAssemblyName, pwNameLen);
    }

    IfFailGo(CreateAssemblyNameObject(&pFusionAssemblyName, pwAssemblyName, 
                                      m_fParsed || (!pwAssemblyName) ? 0 : CANOF_PARSE_DISPLAY_NAME, NULL));


    if (m_fParsed) {
        if (m_context.usMajorVersion != (USHORT) -1) {
            IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_MAJOR_VERSION, 
                                                      &m_context.usMajorVersion, 
                                                      sizeof(USHORT)));
            
            if (m_context.usMinorVersion != (USHORT) -1) {
                IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_MINOR_VERSION, 
                                                          &m_context.usMinorVersion, 
                                                          sizeof(USHORT)));
                
                if (m_context.usBuildNumber != (USHORT) -1) {
                    IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_BUILD_NUMBER, 
                                                              &m_context.usBuildNumber, 
                                                              sizeof(USHORT)));
                    
                    if (m_context.usRevisionNumber != (USHORT) -1)
                        IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_REVISION_NUMBER, 
                                                                  &m_context.usRevisionNumber, 
                                                                  sizeof(USHORT)));
                }
            }
        }
        
        if (m_context.szLocale) {
            MAKE_WIDEPTR_FROMUTF8(pwLocale,m_context.szLocale);
            
            IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_CULTURE, 
                                                      pwLocale, 
                                                      (DWORD)(wcslen(pwLocale) + 1) * sizeof (WCHAR)));
        }
        
        if (m_pbPublicKeyOrToken) {
            if (m_cbPublicKeyOrToken) {
                if(m_dwFlags & afPublicKey) {
                    IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_PUBLIC_KEY,
                                                              m_pbPublicKeyOrToken, m_cbPublicKeyOrToken));
                }
                else {
                        IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_PUBLIC_KEY_TOKEN,
                                                                  m_pbPublicKeyOrToken, m_cbPublicKeyOrToken));
                }
            }
            else {
                IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_NULL_PUBLIC_KEY_TOKEN,
                                                          NULL, 0));
            }
        }
    }

    if (m_CodeInfo.m_dwCodeBase > 0) {
        IfFailGo(pFusionAssemblyName->SetProperty(ASM_NAME_CODEBASE_URL,
                                                  (void*)m_CodeInfo.m_pszCodeBase, 
                                                  m_CodeInfo.m_dwCodeBase*sizeof(WCHAR)));
    }

    *ppName = pFusionAssemblyName;

    TIMELINE_END(FUSIONBIND, ("CreateFusionName %s", m_pAssemblyName));

    return S_OK;

 ErrExit:
    if (pFusionAssemblyName)
        pFusionAssemblyName->Release();

    TIMELINE_END(FUSIONBIND, ("CreateFusionName %s", m_pAssemblyName));

    return hr;
}
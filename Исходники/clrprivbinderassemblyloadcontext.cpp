HRESULT CLRPrivBinderAssemblyLoadContext::BindUsingPEImage( /* in */ PEImage *pPEImage,
        /* in */ BOOL fIsNativeImage,
        /* [retval][out] */ ICLRPrivAssembly **ppAssembly)
{
    HRESULT hr = S_OK;

    EX_TRY
    {
        ReleaseHolder<BINDER_SPACE::Assembly> pCoreCLRFoundAssembly;
        ReleaseHolder<BINDER_SPACE::AssemblyName> pAssemblyName;
        ReleaseHolder<IMDInternalImport> pIMetaDataAssemblyImport;

        PEKIND PeKind = peNone;

        // Get the Metadata interface
        DWORD dwPAFlags[2];
        IF_FAIL_GO(BinderAcquireImport(pPEImage, &pIMetaDataAssemblyImport, dwPAFlags, fIsNativeImage));
        IF_FAIL_GO(AssemblyBinder::TranslatePEToArchitectureType(dwPAFlags, &PeKind));

        _ASSERTE(pIMetaDataAssemblyImport != NULL);

        // Using the information we just got, initialize the assemblyname
        SAFE_NEW(pAssemblyName, AssemblyName);
        IF_FAIL_GO(pAssemblyName->Init(pIMetaDataAssemblyImport, PeKind));

        // Validate architecture
        if (!BINDER_SPACE::Assembly::IsValidArchitecture(pAssemblyName->GetArchitecture()))
        {
            IF_FAIL_GO(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT));
        }

        // Ensure we are not being asked to bind to a TPA assembly
        //
        // Easy out for mscorlib
        if (pAssemblyName->IsMscorlib())
        {
            IF_FAIL_GO(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
        }

        {
            SString& simpleName = pAssemblyName->GetSimpleName();
            ApplicationContext *pTPAApplicationContext = m_pTPABinder->GetAppContext();
            SimpleNameToFileNameMap * tpaMap = pTPAApplicationContext->GetTpaList();
            if (tpaMap->LookupPtr(simpleName.GetUnicode()) != NULL)
            {
                // The simple name of the assembly being requested to be bound was found in the TPA list.
                // Now, perform the actual bind to see if the assembly was really in the TPA assembly or not.
                // Don't search app paths when using the TPA binder because the actual binder is using a host assembly resolver.
                hr = m_pTPABinder->BindAssemblyByNameWorker(pAssemblyName, &pCoreCLRFoundAssembly, true /* excludeAppPaths */);
                if (SUCCEEDED(hr))
                {
                    if (pCoreCLRFoundAssembly->GetIsInGAC())
                    {
                        // If we were able to bind to a TPA assembly, then fail the load
                        IF_FAIL_GO(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
                    }
                }
            }

            hr = AssemblyBinder::BindUsingPEImage(&m_appContext, pAssemblyName, pPEImage, PeKind, pIMetaDataAssemblyImport, &pCoreCLRFoundAssembly);
            if (hr == S_OK)
            {
                _ASSERTE(pCoreCLRFoundAssembly != NULL);
                pCoreCLRFoundAssembly->SetBinder(this);
                *ppAssembly = pCoreCLRFoundAssembly.Extract();
            }
        }
Exit:
        ;
    }
    EX_CATCH_HRESULT(hr);

    return hr;
}
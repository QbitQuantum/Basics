HRESULT 
RegMeta::QueryInterface(
    REFIID  riid, 
    void ** ppUnk)
{
    HRESULT hr = S_OK;
    BEGIN_ENTRYPOINT_NOTHROW;
    int fIsInterfaceRW = false;
    *ppUnk = 0;

    if (riid == IID_IUnknown)
    {
        *ppUnk = (IUnknown *)(IMetaDataImport2 *)this;
    }
    else if (riid == IID_IMDCommon)
    {
        *ppUnk = (IMDCommon *)this;
    }
    else if (riid == IID_IMetaDataImport)
    {
        *ppUnk = (IMetaDataImport2 *)this;
    }
    else if (riid == IID_IMetaDataImport2)
    {
        *ppUnk = (IMetaDataImport2 *)this;
    }
    else if (riid == IID_IMetaDataAssemblyImport)
    {
        *ppUnk = (IMetaDataAssemblyImport *)this;
    }
    else if (riid == IID_IMetaDataTables)
    {
        *ppUnk = static_cast<IMetaDataTables *>(this);
    }
    else if (riid == IID_IMetaDataTables2)
    {
        *ppUnk = static_cast<IMetaDataTables2 *>(this);
    }

#ifndef FEATURE_METADATA_STANDALONE_WINRT
    else if (riid == IID_IMetaDataInfo)
    {
        *ppUnk = static_cast<IMetaDataInfo *>(this);
    }
#endif //!FEATURE_METADATA_STANDALONE_WINRT

#ifdef FEATURE_METADATA_EMIT
    else if (riid == IID_IMetaDataEmit)
    {
        *ppUnk = (IMetaDataEmit2 *)this;
        fIsInterfaceRW = true;
    }
    else if (riid == IID_IMetaDataEmit2)
    {
        *ppUnk = (IMetaDataEmit2 *)this;
        fIsInterfaceRW = true;
    }
    else if (riid == IID_IMetaDataAssemblyEmit)
    {
        *ppUnk = (IMetaDataAssemblyEmit *)this;
        fIsInterfaceRW = true;
    }
#endif //FEATURE_METADATA_EMIT

#if defined(FEATURE_METADATA_IN_VM) && !defined(FEATURE_CORECLR)
    else if (riid == IID_IMetaDataValidate)
    {
        *ppUnk = (IMetaDataValidate *)this;
    }
#endif //defined(FEATURE_METADATA_IN_VM) && !defined(FEATURE_CORECLR)

#ifdef FEATURE_METADATA_EMIT_ALL
    else if (riid == IID_IMetaDataFilter)
    {
        *ppUnk = (IMetaDataFilter *)this;
    }
#endif //FEATURE_METADATA_EMIT_ALL

#ifdef FEATURE_METADATA_INTERNAL_APIS
    else if (riid == IID_IMetaDataHelper)
    {
        *ppUnk = (IMetaDataHelper *)this;
    }
    else if (riid == IID_IMDInternalEmit)
    {
        *ppUnk = static_cast<IMDInternalEmit *>(this);
    }
    else if (riid == IID_IGetIMDInternalImport)
    {
        *ppUnk = static_cast<IGetIMDInternalImport *>(this);
    }
#endif //FEATURE_METADATA_INTERNAL_APIS

#if defined(FEATURE_METADATA_EMIT) && defined(FEATURE_METADATA_INTERNAL_APIS)
    else if (riid == IID_IMetaDataEmitHelper)
    {
        *ppUnk = (IMetaDataEmitHelper *)this;
        fIsInterfaceRW = true;
    }
#endif //FEATURE_METADATA_EMIT && FEATURE_METADATA_INTERNAL_APIS

#ifdef FEATURE_METADATA_IN_VM
#ifdef FEATURE_COMINTEROP
    else if (riid == IID_IMarshal)
    {
        // We will only repond to this interface if scope is opened for ReadOnly
        if (IsOfReadOnly(m_OpenFlags))
        {
            if (m_pFreeThreadedMarshaler == NULL)
            {
                // Guard ourselves against first time QI on IMarshal from two different threads..
                LOCKWRITE();
                if (m_pFreeThreadedMarshaler == NULL)
                {
                    // First time! Create the FreeThreadedMarshaler
                    IfFailGo(CoCreateFreeThreadedMarshaler((IUnknown *)(IMetaDataEmit2 *)this, &m_pFreeThreadedMarshaler));
                }                
            }
            
            _ASSERTE(m_pFreeThreadedMarshaler != NULL);
            
            IfFailGo(m_pFreeThreadedMarshaler->QueryInterface(riid, ppUnk));
            
            // AddRef has happened in the QueryInterface and thus should just return
            goto ErrExit;
        }
        else
        {
            IfFailGo(E_NOINTERFACE);
        }
    }
#endif // FEATURE_COMINTEROP
#ifdef FEATURE_PREJIT
    else if (riid == IID_IMetaDataCorProfileData)
    {
        *ppUnk = (IMetaDataCorProfileData *)this;
    }
    else if (riid == IID_IMDInternalMetadataReorderingOptions)
    {
        *ppUnk = (IMDInternalMetadataReorderingOptions *)this;
    }
#endif //FEATURE_PREJIT
#endif //FEATURE_METADATA_IN_VM
    else
    {
        IfFailGo(E_NOINTERFACE);
    }

    if (fIsInterfaceRW && IsOfReadOnly(m_OpenFlags))
    {
        // They are asking for a read/write interface and this scope was
        // opened as Read-Only

        *ppUnk = NULL;
        IfFailGo(CLDB_E_INCOMPATIBLE);
    }

    if (fIsInterfaceRW)
    {
        LOCKWRITENORET();

        if (SUCCEEDED(hr))
        {
            hr = m_pStgdb->m_MiniMd.ConvertToRW();
        }

        if (FAILED(hr))
        {
            *ppUnk = NULL;
            goto ErrExit;
        }
    }

    AddRef();
ErrExit:
    
    END_ENTRYPOINT_NOTHROW;

    return hr;
} // RegMeta::QueryInterface
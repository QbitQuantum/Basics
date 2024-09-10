STDMETHODIMP CDP_Slot::get_ModuleCollection(IModuleCollection ** pp)
{
    int iCount,i;
    CComObject<ModuleCollection> *pc = NULL;
    IModule *pModule = NULL;
    HRESULT hr = S_OK,hrLoop;
    
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    FC_PCHECK_HR(pp,E_POINTER);
    *pp = NULL;

    try {
        hr = CComObject<ModuleCollection>::CreateInstance(&pc);
        if(FAILED(hr)) {
            throw hr;
        }

        iCount = m_Modules.GetCount();

        hr = pc->Initialize(iCount); 
        if(FAILED(hr)) {
            throw hr;
        }

        for(i= 0; i< iCount; i++) {
            IModule * pModule = m_Modules[i]; //makes an addref.
            if(!pModule) {
                _ASSERTE(pModule);
                continue;
            }

            hrLoop = pc->Insert(i,pModule);
            if(FAILED(hrLoop)) {
                hr = hrLoop;
            }

            FC_RELEASE_PTR(pModule);
        }

        if(FAILED(hr)) {
            throw hr;
        }

        hr = pc->QueryInterface(pp);
    }
    catch(HRESULT hrRes) {
        if(pc) {
            delete pc;
        }
        hr = hrRes;
    }
    return hr;
}
    virtual HRESULT STDMETHODCALLTYPE SetSite(IUnknown *pUnkSite)
    {
        HRESULT hRet;
        HWND hwndSite;

        TRACE("ITaskBand::SetSite(0x%p)\n", pUnkSite);

        hRet = IUnknown_GetWindow(pUnkSite, &hwndSite);
        if (FAILED(hRet))
        {
            TRACE("Querying site window failed: 0x%x\n", hRet);
            return hRet;
        }

        TRACE("CreateTaskSwitchWnd(Parent: 0x%p)\n", hwndSite);

        HWND hwndTaskSwitch = CreateTaskSwitchWnd(hwndSite, m_Tray);
        if (!hwndTaskSwitch)
        {
            ERR("CreateTaskSwitchWnd failed");
            return E_FAIL;
        }

        m_Site = pUnkSite;
        m_hWnd = hwndTaskSwitch;

        return S_OK;
    }
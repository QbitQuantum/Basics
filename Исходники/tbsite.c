static HRESULT STDMETHODCALLTYPE
ITrayBandSiteImpl_ProcessMessage(IN OUT ITrayBandSite *iface,
                                 IN HWND hWnd,
                                 IN UINT uMsg,
                                 IN WPARAM wParam,
                                 IN LPARAM lParam,
                                 OUT LRESULT *plResult)
{
    ITrayBandSiteImpl *This = ITrayBandSiteImpl_from_ITrayBandSite(iface);
    HRESULT hRet;

    ASSERT(This->hWndRebar != NULL);

    /* Custom task band behavior */
    switch (uMsg)
    {
        case WM_NOTIFY:
        {
            const NMHDR *nmh = (const NMHDR *)lParam;

            if (nmh->hwndFrom == This->hWndRebar)
            {
                switch (nmh->code)
                {
                    case NM_NCHITTEST:
                    {
                        LPNMMOUSE nmm = (LPNMMOUSE)lParam;

                        if (nmm->dwHitInfo == RBHT_CLIENT || nmm->dwHitInfo == RBHT_NOWHERE ||
                            nmm->dwItemSpec == (DWORD_PTR)-1)
                        {
                            /* Make the rebar control appear transparent so the user
                               can drag the tray window */
                            *plResult = HTTRANSPARENT;
                        }
                        return S_OK;
                    }

                    case RBN_MINMAX:
                        /* Deny if an Administrator disabled this "feature" */
                        *plResult = (SHRestricted(REST_NOMOVINGBAND) != 0);
                        return S_OK;
                }
            }

            //DbgPrint("ITrayBandSite::ProcessMessage: WM_NOTIFY for 0x%p, From: 0x%p, Code: NM_FIRST-%u...\n", hWnd, nmh->hwndFrom, NM_FIRST - nmh->code);
            break;
        }
    };

    /* Forward to the shell's IWinEventHandler interface to get the default
       shell behavior! */
    if (This->WindowEventHandler != NULL)
    {
        /*DbgPrint("Calling IWinEventHandler::ProcessMessage(0x%p, 0x%x, 0x%p, 0x%p, 0x%p) This->hWndRebar=0x%p\n", hWnd, uMsg, wParam, lParam, plResult, This->hWndRebar);*/
        hRet = IWinEventHandler_OnWinEvent(This->WindowEventHandler,
                                                  hWnd,
                                                  uMsg,
                                                  wParam,
                                                  lParam,
                                                  plResult);
        if (!SUCCEEDED(hRet))
        {
            if (uMsg == WM_NOTIFY)
            {
                const NMHDR *nmh = (const NMHDR *)lParam;
                DbgPrint("ITrayBandSite->IWinEventHandler::ProcessMessage: WM_NOTIFY for 0x%p, From: 0x%p, Code: NM_FIRST-%u returned 0x%x\n", hWnd, nmh->hwndFrom, NM_FIRST - nmh->code, hRet);
            }
            else
            {
                DbgPrint("ITrayBandSite->IWinEventHandler::ProcessMessage(0x%p,0x%x,0x%p,0x%p,0x%p->0x%p) returned: 0x%x\n", hWnd, uMsg, wParam, lParam, plResult, *plResult, hRet);
            }
        }
    }
    else
        hRet = E_FAIL;

    return hRet;
}
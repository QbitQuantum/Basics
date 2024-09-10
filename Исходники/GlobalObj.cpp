/**
* \brief         Callback function which can be used to close windows during configuration switching
* \param[in]     HWND hwnd, LPARAM lParam
* \return        TRUE
* \authors       Arunkumar Karri
* \date          14.02.2013 Created
*/
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM /* lParam */)
{
    if ( hwnd )
    {
        CWnd* pWnd = CWnd::FromHandle(hwnd);
        if ( pWnd )
        {
            CRuntimeClass* pRunTimeClass = pWnd->GetRuntimeClass();

            if ( pRunTimeClass )
            {
                if ( pRunTimeClass == RUNTIME_CLASS(CEditFrameWnd) || pRunTimeClass == RUNTIME_CLASS(COutWnd) )
                {
                    /* If any function editor window is open */
                    if ( pRunTimeClass == RUNTIME_CLASS(CEditFrameWnd) )
                    {
                        CEditFrameWnd* pEditWnd = (CEditFrameWnd*)pWnd;
                        CFunctionEditorDoc* pDoc = (CFunctionEditorDoc*)pEditWnd->GetActiveDocument();

                        /* If a function editor window is modified */
                        if ( nullptr != pDoc && pDoc->IsModified() )
                        {
                            /* take confirmation from user for the first time only */
                            if ( g_bReqUserConfirmation )
                            {
                                g_bReqUserConfirmation = false;
                                INT nSelection = ::MessageBox( hwnd, _("Simulation files have been modified. Do You Want to save the Changes?"), _("Modified"), MB_YESNO | MB_ICONQUESTION);

                                switch(nSelection)
                                {
                                    case IDYES:
                                        g_bQueryConfirm = true;
                                        break;
                                    case IDNO:
                                        g_bQueryConfirm = false;
                                        break;
                                }
                            }
                            /* Based on user response, save the simulation files */
                            if ( g_bQueryConfirm )
                            {
                                if (pDoc != nullptr)
                                {
                                    pDoc->OnSaveDocument(pDoc->GetPathName());
                                }
                            }
                        }
                    }
                    /* Destroy the window */
                    pWnd->DestroyWindow();
                }
            }
        }
    }
    return TRUE;
}
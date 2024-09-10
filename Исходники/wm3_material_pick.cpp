INT_PTR CALLBACK BindProc(
    HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    M3Mat *mp = DLGetWindowLongPtr<M3Mat*>(hWnd);
    if (!mp && msg!=WM_INITDIALOG) return FALSE;

    int id = LOWORD(wParam);
    int notify = HIWORD(wParam);


    switch (msg) {
    case WM_INITDIALOG: {
        mp = (M3Mat*)lParam;
        DLSetWindowLongPtr(hWnd, mp);

        HWND modList = GetDlgItem(hWnd,IDC_MODLIST);

        SendMessage(modList,LB_RESETCONTENT,0,0);

        POINT lpPt;
        GetCursorPos(&lpPt);
        SetWindowPos(hWnd, NULL, lpPt.x, lpPt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

        Object *pObj = mp->Wnode->GetObjectRef();
        IDerivedObject *pDerObj = NULL;
        Modifier *pMod = NULL;

        if( pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID)
        {
            pDerObj = (IDerivedObject *) pObj;

            for(int i = 0 ; i < pDerObj->NumModifiers() ; i++ )
            {
                pMod = pDerObj->GetModifier(i);
                SendMessage(modList,LB_ADDSTRING,0,(LPARAM) (LPCTSTR) pMod->GetName());
            }
        }

        SendMessage(modList,LB_SETCURSEL ,(WPARAM)-1,0);

        break;
    }


    case WM_COMMAND:

        if (notify==LBN_SELCHANGE) {
            if(id==IDC_MODLIST) {
                int mkSel = (int)SendMessage(GetDlgItem(hWnd, IDC_MODLIST), LB_GETCURSEL, 0, 0);
                if(mkSel>=0) {

                    Object *pObj = mp->Wnode->GetObjectRef();
                    IDerivedObject *pDerObj = NULL;
                    Modifier *pMod = NULL;

                    if( pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID)
                    {
                        pDerObj = (IDerivedObject *) pObj;
                        pMod = pDerObj->GetModifier(mkSel);
                        if(pMod->ClassID() == MR3_CLASS_ID) EnableWindow(GetDlgItem(hWnd,IDOK),TRUE);
                        else EnableWindow(GetDlgItem(hWnd,IDOK),FALSE);
                    }


                }
            }
        }

        switch (id) {
        case IDOK:
        {
            int mkSel = (int)SendMessage(GetDlgItem(hWnd, IDC_MODLIST), LB_GETCURSEL, 0, 0);
            if(mkSel>=0) {

                Object *pObj = mp->Wnode->GetObjectRef();
                IDerivedObject *pDerObj = NULL;
                Modifier *pMod = NULL;

                if( pObj->SuperClassID() == GEN_DERIVOB_CLASS_ID)
                {
                    pDerObj = (IDerivedObject *) pObj;
                    pMod = pDerObj->GetModifier(mkSel);

                    MorphR3 *mod = (MorphR3*)pMod;
                    if(mod->CheckMaterialDependency() ) {
                        EndDialog(hWnd,1);
                        return TRUE;
                    }

                    // Make sure the node does not depend on us
                    mod->BeginDependencyTest();
                    mp->NotifyDependents(FOREVER,0,REFMSG_TEST_DEPENDENCY);
                    if (mod->EndDependencyTest()) {
                        // display cyclic warning
                        //
                        if (GetCOREInterface()->GetQuietMode()) {
                            TSTR cyclic;
                            cyclic = GetString(IDS_CANNOT_BIND);
                            GetCOREInterface()->Log()->LogEntry(SYSLOG_WARN,NO_DIALOG,GetString(IDS_CLASS_NAME),cyclic);
                        }
                        else
                        {
                            TSTR cyclic;
                            cyclic = GetString(IDS_CANNOT_BIND);
                            MessageBox(hWnd,cyclic,GetString(IDS_CLASS_NAME),MB_OK);
                        }
                        EndDialog(hWnd,1);
                        return TRUE;
                    }

                    if(mod) mod->morphmaterial = mp;

                    mp->ReplaceReference(102, mod);
                    mp->obName = mp->Wnode->GetName();

                    mp->morphp = mod;
                    if (mp->matDlg ) {
                        mp->matDlg->UpdateMorphInfo(UD_LINK);
                        mp->matDlg->ReloadDialog();
                    }
                }


            }
        }
        case IDCANCEL:
            EndDialog(hWnd,1);
            break;
        }
        break;



    default:
        return FALSE;
    }
    return TRUE;
}
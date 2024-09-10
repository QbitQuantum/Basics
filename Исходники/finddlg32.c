/***********************************************************************
 *	COMDLG32_FindReplaceDlgProc		[internal]
 * [Find/Replace]Text32[A/W] window procedure.
 */
static INT_PTR CALLBACK COMDLG32_FindReplaceDlgProc(HWND hDlgWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	COMDLG32_FR_Data *pdata = (COMDLG32_FR_Data *)GetPropA(hDlgWnd, (LPSTR)COMDLG32_Atom);
	INT_PTR retval = TRUE;

	if(iMsg == WM_INITDIALOG)
        {
                pdata = (COMDLG32_FR_Data *)lParam;
        	if(!SetPropA(hDlgWnd, (LPSTR)COMDLG32_Atom, (HANDLE)pdata))
                {
			ERR("Could not Set prop; invent a gracefull exit?...\n");
                	DestroyWindow(hDlgWnd);
                        return FALSE;
                }
        	SendDlgItemMessageA(hDlgWnd, edt1, EM_SETLIMITTEXT, (WPARAM)pdata->fr.wFindWhatLen, 0);
	        SendDlgItemMessageA(hDlgWnd, edt1, WM_SETTEXT, 0, (LPARAM)pdata->fr.lpstrFindWhat);
                if(pdata->fr.Flags & FR_WINE_REPLACE)
                {
	        	SendDlgItemMessageA(hDlgWnd, edt2, EM_SETLIMITTEXT, (WPARAM)pdata->fr.wReplaceWithLen, 0);
		        SendDlgItemMessageA(hDlgWnd, edt2, WM_SETTEXT, 0, (LPARAM)pdata->fr.lpstrReplaceWith);
                }

        	if(!(pdata->fr.Flags & FR_SHOWHELP))
			ShowWindow(GetDlgItem(hDlgWnd, pshHelp), SW_HIDE);
	        if(pdata->fr.Flags & FR_HIDEUPDOWN)
        	{
			ShowWindow(GetDlgItem(hDlgWnd, rad1), SW_HIDE);
			ShowWindow(GetDlgItem(hDlgWnd, rad2), SW_HIDE);
			ShowWindow(GetDlgItem(hDlgWnd, grp1), SW_HIDE);
	        }
        	else if(pdata->fr.Flags & FR_NOUPDOWN)
	        {
			EnableWindow(GetDlgItem(hDlgWnd, rad1), FALSE);
			EnableWindow(GetDlgItem(hDlgWnd, rad2), FALSE);
			EnableWindow(GetDlgItem(hDlgWnd, grp1), FALSE);
        	}
                else
                {
			SendDlgItemMessageA(hDlgWnd, rad1, BM_SETCHECK, pdata->fr.Flags & FR_DOWN ? 0 : BST_CHECKED, 0);
			SendDlgItemMessageA(hDlgWnd, rad2, BM_SETCHECK, pdata->fr.Flags & FR_DOWN ? BST_CHECKED : 0, 0);
                }

	        if(pdata->fr.Flags & FR_HIDEMATCHCASE)
			ShowWindow(GetDlgItem(hDlgWnd, chx2), SW_HIDE);
        	else if(pdata->fr.Flags & FR_NOMATCHCASE)
			EnableWindow(GetDlgItem(hDlgWnd, chx2), FALSE);
                else
			SendDlgItemMessageA(hDlgWnd, chx2, BM_SETCHECK, pdata->fr.Flags & FR_MATCHCASE ? BST_CHECKED : 0, 0);

	        if(pdata->fr.Flags & FR_HIDEWHOLEWORD)
			ShowWindow(GetDlgItem(hDlgWnd, chx1), SW_HIDE);
        	else if(pdata->fr.Flags & FR_NOWHOLEWORD)
			EnableWindow(GetDlgItem(hDlgWnd, chx1), FALSE);
                else
			SendDlgItemMessageA(hDlgWnd, chx1, BM_SETCHECK, pdata->fr.Flags & FR_WHOLEWORD ? BST_CHECKED : 0, 0);

		/* We did the init here, now call the hook if requested */

		/* We do not do ShowWindow if hook exists and is FALSE  */
		/*   per MSDN Article Q96135                            */
              	if((pdata->fr.Flags & FR_ENABLEHOOK)
	             && ! pdata->fr.lpfnHook(hDlgWnd, iMsg, wParam, (LPARAM) &pdata->fr))
		        return TRUE;
		ShowWindow(hDlgWnd, SW_SHOWNORMAL);
		UpdateWindow(hDlgWnd);
                return TRUE;
        }

	if(pdata && (pdata->fr.Flags & FR_ENABLEHOOK))
	{
		retval = pdata->fr.lpfnHook(hDlgWnd, iMsg, wParam, lParam);
	}
	else
		retval = FALSE;

       	if(pdata && !retval)
        {
        	retval = TRUE;
		switch(iMsg)
        	{
	        case WM_COMMAND:
			COMDLG32_FR_HandleWMCommand(hDlgWnd, pdata, LOWORD(wParam), HIWORD(wParam));
                	break;

	        case WM_CLOSE:
			COMDLG32_FR_HandleWMCommand(hDlgWnd, pdata, IDCANCEL, BN_CLICKED);
        		break;

	        case WM_HELP:
        		/* Heeeeelp! */
        		FIXME("Got WM_HELP. Who is gonna supply it?\n");
	                break;

        	case WM_CONTEXTMENU:
        		/* Heeeeelp! */
        		FIXME("Got WM_CONTEXTMENU. Who is gonna supply it?\n");
        	        break;
		/* FIXME: Handle F1 help */

	        default:
		        retval = FALSE;	/* We did not handle the message */
	        }
        }

        /* WM_DESTROY is a special case.
         * We need to ensure that the allocated memory is freed just before
         * the dialog is killed. We also need to remove the added prop.
         */
        if(iMsg == WM_DESTROY)
        {
        	RemovePropA(hDlgWnd, (LPSTR)COMDLG32_Atom);
        	HeapFree(GetProcessHeap(), 0, pdata);
        }

        return retval;
}
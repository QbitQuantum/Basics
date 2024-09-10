static UINT CALLBACK 	MyFindDialogProcedure (HWND pmWindow, UINT pmMessage, 
    					       WPARAM pmWParam,
    					       LPARAM pmLParam)
{
    static int	stLastX = UNINIT_VAL, stLastY = UNINIT_VAL;
    
    if (pmMessage == WM_INITDIALOG)
    {
	EdSearch_FindReplaceDialog = pmWindow;
	
    	if ((stLastX == UNINIT_VAL) && (stLastY == UNINIT_VAL))
    	{
	    EdGUI_CentreDialogBox (pmWindow);
	}
	else
	{
	    SetWindowPos (pmWindow, HWND_TOP, stLastX, stLastY, 
	        0, 0, SWP_NOSIZE);
	}
	
	return 1;
    }
    else if (pmMessage == WM_DESTROY)
    {
    	RECT	myDialogRect;
    	
    	GetWindowRect (pmWindow, &myDialogRect);
    	
    	stLastX = myDialogRect.left;
    	stLastY = myDialogRect.top;
    }
    else if (pmMessage == WM_ACTIVATE)
    {
        if (LOWORD (pmWParam) == WA_INACTIVE)
        {
            Ed_SetActiveWindow (NULL, NO_WINDOW);
            GetDlgItemText (pmWindow, edt1, stFindWhat, FIND_STRING_LEN);
            GetDlgItemText (pmWindow, edt2, stReplaceWith, FIND_STRING_LEN);
        }
        else
        {
            Ed_SetActiveWindow (pmWindow, FIND_REPLACE_DIALOG);
        }
        if (IsWindow (stFindReplace.hwndOwner))
        {
            RedrawWindow (stFindReplace.hwndOwner, NULL, NULL, 
            	RDW_INVALIDATE);
        }
    }
    else if (pmMessage == WM_COMMAND)
    {
    	if (HIWORD (pmWParam) == 1)
    	{
    	    if (LOWORD (pmWParam) == COMMAND_CLOSE_DIALOG)
    	    {
    	    	SendMessage (pmWindow, WM_CLOSE, 0, 0);
    	    }
    	    else
    	    {
    	    	SendMessage (stFindReplace.hwndOwner, WM_COMMAND, pmWParam, 0);
    	    }
    	    return 1;
    	}
/*    	
    	if (!stIsFindDialog && (LOWORD (pmWParam) == COMMAND_FIND))
    	{
    	    EdSearch_ShowFindDialog (stFindReplace.hwndOwner);
    	}
    	else if (stIsFindDialog && (LOWORD (pmWParam) == COMMAND_REPLACE))
    	{
    	    EdSearch_ShowReplaceDialog (stFindReplace.hwndOwner);
    	}
*/    	
    }

    return 0;
} // MyFindDialogProcedure
//=--------------------------------------------------------------------------=
// CPatchDialog::OnCancel
//=--------------------------------------------------------------------------=
// Message handler for WM_COMMAND with IDCANCEL
//
// Parameters:
//	wNotifyCode Notify Code
//	wID	    ID of control
//	hWndCtl	    HWND of control
//	bHandled    FALSE if not handled
//
// Output:
//	LRESULT	    
//
// Notes:
//
LRESULT CPatchDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    // Disable window first to avoid any keyboard input
    EnableWindow(FALSE);

    // Signal another thread to stop patch update
    SetEvent(m_hCancelEvent);

    // Wait for the patch update thread to complete
    AtlWaitWithMessageLoop(m_hPatchUpdateThreadExitEvent);

    // Destroy dialog
    EndDialog(wID);

    return 0;
}
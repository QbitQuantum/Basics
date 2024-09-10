INT_PTR CALLBACK SessionDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    SESSION_DATA *pSD;
    pSD = (SESSION_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the SESSION_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);
            pSD = (SESSION_DATA *)lParam;

            // Populate the session text
            SendDlgItemMessageW(hwndDlg, IDC_STATIC_SESSION_NAME,
                WM_SETTEXT, 0, (LPARAM)(pSD->bstrName));

            SendDlgItemMessageW(hwndDlg, IDC_STATIC_SESSION_URI,
                WM_SETTEXT, 0, (LPARAM)(pSD->bstrURI));
        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDC_BUTTON_SESSION_ACCEPT: 
            {
                pSD->fAccept = TRUE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE;

        case IDC_BUTTON_SESSION_REJECT:
        case IDCANCEL: 
            {
                pSD->fAccept = FALSE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE; 
        } 
    } 

    return FALSE; 
}
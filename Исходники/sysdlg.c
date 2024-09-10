/*
 * Create - displays the dialog box
 */
BOOL SysDlg_Create(HWND parentWnd, SYS *sys)
{
    /*
     * If the editor window already exists, just re-initialize it.
     */
    if (Prog_sysDlg) {
        SysDlg_Update(Prog_sysDlg, sys);
        if (IsIconic(Prog_sysDlg)) {
            OpenIcon(Prog_sysDlg);
        }
        BringWindowToTop(Prog_sysDlg);
    } else {
        sd_parentWnd = parentWnd;
        sd_data = sys->data;
        Prog_sysDlg = CreateDialogParam(Prog_instance, (LPCTSTR) IDD_SYSDLG
                , HWND_DESKTOP, sd_DlgProc, 0);
        if (!Prog_sysDlg) {
            MsgBox_LastError(parentWnd);
            return FALSE;
        }
    }

    return TRUE;
}
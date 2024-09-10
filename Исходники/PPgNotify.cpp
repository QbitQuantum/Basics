void CPPgNotify::LoadSettings(void)
{
    if (thePrefs.useDownloadNotifier)
        CheckDlgButton(IDC_CB_TBN_ONDOWNLOAD, BST_CHECKED);
    if (thePrefs.useNewDownloadNotifier)
        CheckDlgButton(IDC_CB_TBN_ONNEWDOWNLOAD, BST_CHECKED);
    if (thePrefs.useChatNotifier)
        CheckDlgButton(IDC_CB_TBN_ONCHAT, BST_CHECKED);
    if (thePrefs.useSoundInNotifier)
        CheckDlgButton(IDC_CB_TBN_USESOUND, BST_CHECKED);
    if (thePrefs.useLogNotifier)
        CheckDlgButton(IDC_CB_TBN_ONLOG, BST_CHECKED);
    if (thePrefs.notifierPopsEveryChatMsg)
        CheckDlgButton(IDC_CB_TBN_POP_ALWAYS, BST_CHECKED);
    if (thePrefs.notifierImportantError)
        CheckDlgButton(IDC_CB_TBN_IMPORTATNT, BST_CHECKED);
    if (thePrefs.notifierNewVersion)
        CheckDlgButton(IDC_CB_TBN_ONNEWVERSION, BST_CHECKED);

    CButton* btnPTR = (CButton*) GetDlgItem(IDC_CB_TBN_POP_ALWAYS);
    btnPTR->EnableWindow(IsDlgButtonChecked(IDC_CB_TBN_ONCHAT));
    CEdit* editPtr = (CEdit*) GetDlgItem(IDC_EDIT_TBN_WAVFILE);
    editPtr->SetWindowText(LPCTSTR(thePrefs.notifierSoundFilePath));
    GetDlgItem(IDC_EDIT_TBN_WAVFILE)->EnableWindow(IsDlgButtonChecked(IDC_CB_TBN_USESOUND));
    GetDlgItem(IDC_BTN_BROWSE_WAV)->EnableWindow(IsDlgButtonChecked(IDC_CB_TBN_USESOUND));
}
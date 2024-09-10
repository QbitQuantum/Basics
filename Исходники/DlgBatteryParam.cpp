void CDlgBatteryParam::InitUIComponents()
{
    CString strTxt;

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_TAB_TITLE"),_T("IDS_TAB_TITLE"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_ONE_BATTERY"),_T("IDS_ONE_BATTERY"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_RADIO_CELL_ONE)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_TWO_BATTERIES"),_T("IDS_TWO_BATTERIES"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_RADIO_CELL_TWO)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_PULL_UP"),_T("IDS_PULL_UP"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_STATIC_PULL_UP)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_PULL_DOWN"),_T("IDS_PULL_DOWN"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_STATIC_PULL_DOWN)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_READ_BATTERY"),_T("IDS_READ_BATTERY"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_BUTTON_READ_BATTERY)->SetWindowText(strTxt);
    
    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_WRITE_BATTERY"),_T("IDS_WRITE_BATTERY"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_BUTTON_WRITE_BATTERY)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_DISCHARGE"),_T("IDS_DISCHARGE"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_GROUP_DISCHARGE)->SetWindowText(strTxt);
    
    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDS_CHARGE"),_T("IDS_CHARGE"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_GROUP_CHARGE)->SetWindowText(strTxt);

    GetPrivateProfileStringW(_T("BatteryParam"),_T("IDC_BTN_READ_BATTERY_DATA"),_T("IDC_BTN_READ_BATTERY_DATA"),
        strTxt.GetBuffer(MAX_LENGTH),MAX_LENGTH, g_strLanguageConfigFilePath);
    GetDlgItem(IDC_BTN_READ_BATTERY_DATA)->SetWindowText(strTxt);

    strTxt.ReleaseBuffer(MAX_LENGTH);
}
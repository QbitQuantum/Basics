void CContactSettings::loadSyncModesBox(const char* sourceName)
{
    OutlookConfig* config = getConfig();
    WindowsSyncSourceConfig* ssconf = config->getSyncSourceConfig(sourceName);
    if (!ssconf) return;

    // TODO: use a switch on sourceName when refactoring
    int editBoxResourceID = IDC_CONTACTS_EDIT_SYNCTYPE;
    int comboBoxResourceID = IDC_CONTACTS_COMBO_SYNCTYPE;

    CEdit* editbox = (CEdit*)GetDlgItem(editBoxResourceID);
    CComboBox* combobox = (CComboBox*)GetDlgItem(comboBoxResourceID);
    if (!combobox || !editbox) return;

    //
    // Load the syncmodes in the editbox/dropdown
    //
    CString s1 = "";
    StringBuffer syncModes(ssconf->getSyncModes());
    if (syncModes.find(SYNC_MODE_TWO_WAY) != StringBuffer::npos) {
        s1.LoadString(IDS_SYNCTYPE1);
        combobox->AddString(s1);
    }
    if (syncModes.find(SYNC_MODE_ONE_WAY_FROM_SERVER) != StringBuffer::npos ||
        syncModes.find(SYNC_MODE_SMART_ONE_WAY_FROM_SERVER) != StringBuffer::npos) {
        s1.LoadString(IDS_SYNCTYPE2);
        combobox->AddString(s1);
    }
    if (syncModes.find(SYNC_MODE_ONE_WAY_FROM_CLIENT) != StringBuffer::npos ||
        syncModes.find(SYNC_MODE_SMART_ONE_WAY_FROM_CLIENT) != StringBuffer::npos) {
        s1.LoadString(IDS_SYNCTYPE3);
        combobox->AddString(s1);
    }

    if (combobox->GetCount() > 1) {
        // More than 1 syncmode available: use the dropdown box
        editbox->ShowWindow(SW_HIDE);
        combobox->ShowWindow(SW_SHOW);
    }
    else {
        // Only 1 syncmode available: use the editbox
        editbox->ShowWindow(SW_SHOW);
        combobox->ShowWindow(SW_HIDE);
        SetDlgItemText(editBoxResourceID, s1);
    }
}
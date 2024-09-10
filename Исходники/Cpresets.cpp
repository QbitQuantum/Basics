void TpresetsPage::onSaveToFile(void)
{
    int i=lvGetSelItem(IDC_LV_PRESETS);
    char_t presetFlnm[MAX_PATH];
    _splitpath_s((*parent->localPresets)[i]->presetName, NULL, 0, NULL, 0, presetFlnm, countof(presetFlnm), NULL, 0);
    if (dlgGetFile(true,m_hwnd,_(-IDD_PRESETS,_l("Save ffdshow preset")),presetfilter,presetext,presetFlnm,_l("."),0)) {
        (*parent->localPresets)[i]->saveFile(presetFlnm);
    }
}
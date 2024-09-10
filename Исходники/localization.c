static LANGID
GetGUILanguage(void)
{
    if (gui_language != 0)
        return gui_language;

    HKEY regkey;
    DWORD value = 0;

    LONG status = RegOpenKeyEx(HKEY_CURRENT_USER, GUI_REGKEY_HKCU, 0, KEY_READ, &regkey);
    if (status == ERROR_SUCCESS)
        GetRegistryValueNumeric(regkey, _T("ui_language"), &value);

    gui_language = ( value != 0 ? value : GetUserDefaultUILanguage() );
    InitMUILanguage(gui_language);
    return gui_language;
}
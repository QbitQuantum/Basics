void t4p::SetSettingsDirLocation(const wxFileName& settingsDir) {
    wxFileName bootstrapConfigFile;
    wxStandardPaths paths = wxStandardPaths::Get();
    wxFileName executableDir(paths.GetExecutablePath());

    // the settings dir is in the same directory as the executable. save
    // settings dir in the local bootstrap file
    if (settingsDir.GetPathWithSep().Find(executableDir.GetPathWithSep()) != wxNOT_FOUND) {
        bootstrapConfigFile.Assign(paths.GetExecutablePath());
        bootstrapConfigFile.SetFullName(wxT(".triumph4php-bootstrap.ini"));
    } else {
        // save settings dire in the global bootstrap config file
        bootstrapConfigFile.AssignDir(paths.GetUserConfigDir());
        bootstrapConfigFile.SetFullName(wxT(".triumph4php-bootstrap.ini"));
    }
    wxString bootstrapFullPath = bootstrapConfigFile.GetFullPath();
    wxFileConfig bootstrapConfig(wxT("bootstrap"), wxEmptyString,
                                 bootstrapFullPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
    wxString s = settingsDir.GetPath();
    bootstrapConfig.Write(wxT("SettingsDirectory"), s);
    bootstrapConfig.Flush();
}
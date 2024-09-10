bool FormatOptions::HasConfigForFile(const wxFileName& fileName, const wxString& configName) const
{
    wxFileName configFile(fileName.GetPath(), configName);
    while(configFile.GetDirCount()) {
        if(configFile.FileExists()) {
            return true;
        }
        configFile.RemoveLastDir();
    }
    return false;
}
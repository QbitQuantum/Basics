static wxString GetDefaultPath(const wxFileName& fileName)
{
    wxString str = fileName.GetPath();
    if (str.empty())
        str = wxGetCwd();
    return str;
}
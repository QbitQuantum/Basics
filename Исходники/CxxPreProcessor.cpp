bool
CxxPreProcessor::ExpandInclude(const wxFileName& currentFile, const wxString& includeStatement, wxFileName& outFile)
{
    wxString includeName = includeStatement;
    includeName.Replace("\"", "");
    includeName.Replace("<", "");
    includeName.Replace(">", "");

    // Try the current file's directory first
    wxArrayString paths = m_includePaths;
    paths.Insert(currentFile.GetPath(), 0);

    if(m_noSuchFiles.count(includeStatement)) {
        // wxPrintf("No such file hit\n");
        return false;
    }

    std::map<wxString, wxString>::iterator iter = m_fileMapping.find(includeStatement);
    if(iter != m_fileMapping.end()) {
        // if this file has a mapped file, it means that we either
        // already scanned it or could not find a match for it
        // wxPrintf("File already been scanned\n");
        return false;
    }

    for(size_t i = 0; i < paths.GetCount(); ++i) {
        wxString tmpfile;
        tmpfile << paths.Item(i) << "/" << includeName;
        wxFileName fn(tmpfile);
        tmpfile = fn.GetFullPath();
        // CL_DEBUG(" ... Checking include file: %s\n", fn.GetFullPath());
        struct stat buff;
        if((stat(tmpfile.mb_str(wxConvUTF8).data(), &buff) == 0)) {
            CL_DEBUG1(" ==> Creating scanner for file: %s\n", tmpfile);
            wxFileName fixedFileName(tmpfile);
            if(fixedFileName.FileExists()) {
                fixedFileName.Normalize(wxPATH_NORM_DOTS);
                tmpfile = fixedFileName.GetFullPath();
                m_fileMapping.insert(std::make_pair(includeStatement, tmpfile));
                outFile = fixedFileName;
                return true;
            } else {
                CL_DEBUG("Including a folder :/ : %s", fixedFileName.GetFullPath());
            }
        }
    }

    // remember that we could not locate this include statement
    m_noSuchFiles.insert(includeStatement);
    m_fileMapping.insert(std::make_pair(includeStatement, wxString()));
    return false;
}
/**
 * Doku see wxFileSystemHandler
 */
wxString wxChmFSHandler::FindFirst(const wxString& spec, int flags)
{
    wxString right = GetRightLocation(spec);
    wxString left = GetLeftLocation(spec);
    wxString nativename = wxFileSystem::URLToFileName(left).GetFullPath();

    if ( GetProtocol(left) != _T("file") )
    {
        wxLogError(_("CHM handler currently supports only local files!"));
        return wxEmptyString;
    }

    m_chm = new wxChmTools(wxFileName(nativename));
    m_pattern = right.AfterLast(_T('/'));

    wxString m_found = m_chm->Find(m_pattern);

    // now fake around hhp-files which are not existing in projects...
    if (m_found.empty() &&
        m_pattern.Contains(_T(".hhp")) &&
        !m_pattern.Contains(_T(".hhp.cached")))
    {
        m_found.Printf(_T("%s#chm:%s.hhp"),
                       left.c_str(), m_pattern.BeforeLast(_T('.')).c_str());
    }

    return m_found;

}
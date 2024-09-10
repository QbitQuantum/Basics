wxString PHPWorkspace::GetProjectFromFile(const wxFileName& filename) const
{
    PHPProject::Map_t::const_iterator iter =
        std::find_if(m_projects.begin(), m_projects.end(), [&](const PHPProject::Map_t::value_type& v) {
            wxString path = filename.GetPath();
            return path.StartsWith(v.second->GetFilename().GetPath());
        });

    if(iter != m_projects.end()) {
        return iter->second->GetName();
    }
    return wxEmptyString;
}
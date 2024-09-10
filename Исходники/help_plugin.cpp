void HelpPlugin::SetManPageDirs(MANFrame *manFrame)
{
    const wxString man_prefix = _T("man:");
    wxString all_man_dirs(man_prefix);

    for (HelpCommon::HelpFilesVector::const_iterator i = m_Vector.begin(); i != m_Vector.end(); ++i)
    {
        if (i->second.name.Mid(0, man_prefix.size()).CmpNoCase(man_prefix) == 0)
        {
            // only add ; if a dir is already set
            if (all_man_dirs.Length() > man_prefix.Length())
                all_man_dirs += _T(";");

            all_man_dirs += i->second.name.Mid(man_prefix.Length());
        }
    }
    manFrame->SetDirs(all_man_dirs);
}
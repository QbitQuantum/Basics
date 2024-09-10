void ClassWizardDlg::DoForceDirectory(const wxFileName & filename)
{
    wxFileName parentname(filename);
    parentname.RemoveLastDir();

    if ((filename != parentname) && (parentname.GetDirCount() >= 1) )
        DoForceDirectory(parentname);

    if (!wxDirExists(filename.GetPath()))
        wxMkdir(filename.GetPath());
}
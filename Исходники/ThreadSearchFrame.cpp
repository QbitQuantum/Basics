// ----------------------------------------------------------------------------
bool ThreadSearchFrame::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files)
// ----------------------------------------------------------------------------
{
    bool success = true; // Safe case initialisation

    // first check to see if a workspace is passed. If so, only this will be loaded
    wxString foundWorkspace;
    for (unsigned int i = 0; i < files.GetCount(); ++i)
    {
        FileType ft = FileTypeOf(files[i]);
        if (ft == ftCodeBlocksWorkspace || ft == ftMSVC6Workspace || ft == ftMSVC7Workspace)
        {
            foundWorkspace = files[i];
            break;
        }
    }

    if (!foundWorkspace.IsEmpty())
      success &= OpenGeneric(foundWorkspace);
    else
    {
        wxBusyCursor useless;
        wxPaintEvent e;
        ProcessEvent(e);

        Freeze();
        for (unsigned int i = 0; i < files.GetCount(); ++i)
          success &= OpenGeneric(files[i]);
        Thaw();
    }
    return success;
}
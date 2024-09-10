void SigUIFrame::OnChange(wxFileSystemWatcherEvent &event)
{
    if (event.IsError()) {
	wxLogVerbose("fswatcher error: %s", event.GetErrorDescription());
	return;
    }
    wxLogVerbose("event on %s", event.GetPath().GetFullPath());
    switch (event.GetChangeType()) {
	default:
	    break;
	case wxFSW_EVENT_CREATE:
	case wxFSW_EVENT_MODIFY:
	    wxFileName filename = event.GetPath();
	    if (filename.GetName() != "lastupd")
		return;
	    show_db(false);
	    break;
    }
}
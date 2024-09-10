void t4p::FileWatcherFeatureClass::OnFsWatcher(wxFileSystemWatcherEvent& event) {
    LastWatcherEventTime = wxDateTime::Now();
    wxString path = event.GetPath().GetFullPath();
    wxFileName fileName = event.GetPath();
    if (wxFSW_EVENT_MODIFY == event.GetChangeType()) {
        PathsExternallyModified[path] = 1;
    } else if (wxFSW_EVENT_CREATE == event.GetChangeType()) {
        PathsExternallyCreated[path] = 1;
    } else if (wxFSW_EVENT_DELETE == event.GetChangeType()) {
        PathsExternallyDeleted[path] = 1;
    } else if (wxFSW_EVENT_RENAME == event.GetChangeType()) {
        PathsExternallyRenamed[path] = event.GetNewPath().GetFullPath();
    } else if (wxFSW_EVENT_WARNING == event.GetChangeType()) {
        // too many files being added/removed
        // this is probably a big directory being added / removed
        // hopefully the root directory is caught
    } else if (wxFSW_EVENT_ERROR == event.GetChangeType()) {
        // in MSW, an error event could be due to the watched directoty being deleted / renamed.
        // in this case, we need to restart the watch
        IsWatchError = true;
        wxASSERT_MSG(false, event.GetErrorDescription());
    }
}
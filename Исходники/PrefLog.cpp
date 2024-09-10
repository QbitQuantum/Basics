void LogPrefsView::_DeleteLogs(BEntry* dir_entry)
{
    BEntry entry;
    BDirectory dir(dir_entry);
    dir.Rewind();
    while (dir.GetNextEntry(&entry) == B_OK) {
        if (entry.IsDirectory())
            _DeleteLogs(&entry);
        else
            entry.Remove();
    }
}
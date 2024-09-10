static BOOL
register_monitoring_entry(WDM_PEntry entry)
{
    BOOL success;
    DWORD bytes;
    bytes = 0; // Not used because the process callback gets passed the written bytes

    success = ReadDirectoryChangesW(
        entry->dir_handle,                  // handle to directory
        entry->buffer,                      // read results buffer
        WDM_BUFFER_SIZE,                    // length of buffer
        entry->user_data->watch_childeren,  // monitoring option
        entry->user_data->flags,            // filter conditions
        &bytes,                             // bytes returned
        &entry->event_container,            // overlapped buffer
        &handle_entry_change                // process callback
    );

    if ( ! success ) {
        WDM_DEBUG("ReadDirectoryChangesW failed with error (%d): %s", GetLastError(), rb_w32_strerror(GetLastError()));
        return FALSE;
    }

    return TRUE;
}
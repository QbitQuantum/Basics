static unsigned int __stdcall
tr_watchdir_win32_thread (void * context)
{
  const tr_watchdir_t handle = context;
  tr_watchdir_win32 * const backend = BACKEND_UPCAST (tr_watchdir_get_backend (handle));
  DWORD bytes_transferred;

  while (tr_get_overlapped_result_ex (backend->fd, &backend->overlapped, &bytes_transferred,
                                      INFINITE, FALSE))
    {
      PFILE_NOTIFY_INFORMATION info = (PFILE_NOTIFY_INFORMATION) backend->buffer;

      while (info->NextEntryOffset != 0)
        *((BYTE **) &info) += info->NextEntryOffset;

      info->NextEntryOffset = bytes_transferred - ((BYTE *) info - (BYTE *) backend->buffer);

      send (backend->notify_pipe[1], (const char *) backend->buffer, bytes_transferred, 0);

      if (!ReadDirectoryChangesW (backend->fd, backend->buffer, sizeof (backend->buffer), FALSE,
                                  WIN32_WATCH_MASK, NULL, &backend->overlapped, NULL))
        {
          log_error ("Failed to read directory changes");
          return 0;
        }
    }

  if (GetLastError () != ERROR_OPERATION_ABORTED)
    log_error ("Failed to wait for directory changes");

  return 0;
}
void
gum_process_enumerate_threads (GumFoundThreadFunc func,
                               gpointer user_data)
{
  DWORD this_process_id;
  HANDLE snapshot;
  THREADENTRY32 entry;

  this_process_id = GetCurrentProcessId ();

  snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPTHREAD, 0);
  if (snapshot == INVALID_HANDLE_VALUE)
    goto beach;

  entry.dwSize = sizeof (entry);
  if (!Thread32First (snapshot, &entry))
    goto beach;

  do
  {
    if (RTL_CONTAINS_FIELD (&entry, entry.dwSize, th32OwnerProcessID) &&
        entry.th32OwnerProcessID == this_process_id)
    {
      GumThreadDetails details;

      if (gum_windows_get_thread_details (entry.th32ThreadID, &details))
      {
        if (!func (&details, user_data))
          break;
      }
    }

    entry.dwSize = sizeof (entry);
  }
  while (Thread32Next (snapshot, &entry));

beach:
  if (snapshot != INVALID_HANDLE_VALUE)
    CloseHandle (snapshot);
}
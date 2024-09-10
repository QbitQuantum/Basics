/* real hardware */
static GList *
get_connected_drives (GVolumeMonitor *volume_monitor)
{
  GList *list = NULL;

#if 0
  HANDLE  find_handle;
  BOOL    found;
  wchar_t wc_name[MAX_PATH+1];
  
  find_handle = FindFirstVolumeW (wc_name, MAX_PATH);
  found = (find_handle != INVALID_HANDLE_VALUE);
  while (found)
    {
      /* I don't know what this code is supposed to do; clearly it now
       * does nothing, the returned GList is always NULL. But what was
       * this code supposed to be a start of? The volume names that
       * the FindFirstVolume/FindNextVolume loop iterates over returns
       * device names like
       *
       *   \Device\HarddiskVolume1
       *   \Device\HarddiskVolume2
       *   \Device\CdRom0
       *
       * No DOS devices there, so I don't see the point with the
       * QueryDosDevice call below. Probably this code is confusing volumes
       * with something else that does contain the mapping from DOS devices
       * to volumes.
       */
      wchar_t wc_dev_name[MAX_PATH+1];
      guint trailing = wcslen (wc_name) - 1;

      /* remove trailing backslash and leading \\?\\ */
      wc_name[trailing] = L'\0';
      if (QueryDosDeviceW (&wc_name[4], wc_dev_name, MAX_PATH))
        {
          gchar *name = g_utf16_to_utf8 (wc_dev_name, -1, NULL, NULL, NULL);
          g_print ("%s\n", name);
	  g_free (name);
	}

      found = FindNextVolumeW (find_handle, wc_name, MAX_PATH);
    }
  if (find_handle != INVALID_HANDLE_VALUE)
    FindVolumeClose (find_handle);
#endif

  return list;
}
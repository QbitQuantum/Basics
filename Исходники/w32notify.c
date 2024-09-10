/* Worker routine for the watch thread.  */
static DWORD WINAPI
watch_worker (LPVOID arg)
{
  struct notification *dirwatch = (struct notification *)arg;
  BOOL bErr;
  DWORD _bytes = 0;
  DWORD status;

  if (dirwatch->dir)
    {
      bErr = ReadDirectoryChangesW (dirwatch->dir, dirwatch->buf,
				    DIRWATCH_BUFFER_SIZE, dirwatch->subtree,
				    dirwatch->filter, &_bytes,
				    dirwatch->io_info, watch_completion);
      if (!bErr)
	{
	  DebPrint (("ReadDirectoryChangesW: %lu\n", GetLastError ()));
	  /* We cannot remove the dirwatch object from watch_list,
	     because we are in a separate thread.  For the same
	     reason, we also cannot free memory consumed by the
	     buffers allocated for the dirwatch object.  So we close
	     the directory handle, but do not free the object itself
	     or its buffers.  We also don't touch the signature.  This
	     way, remove_watch can still identify the object, remove
	     it, and free its memory.  */
	  CloseHandle (dirwatch->dir);
	  dirwatch->dir = NULL;
	  return 1;
	}
    }

  do {
    status = WaitForSingleObjectEx(dirwatch->terminate, INFINITE, TRUE);
  } while (status == WAIT_IO_COMPLETION);

  /* The thread is about to terminate, so we clean up the dir handle.  */
  CloseHandle (dirwatch->dir);
  dirwatch->dir = NULL;

  return 0;
}
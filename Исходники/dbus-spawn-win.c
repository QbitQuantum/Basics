static unsigned __stdcall
babysitter (void *parameter)
{
  DBusBabysitter *sitter = (DBusBabysitter *) parameter;
  int fd;
  PING();
  _dbus_babysitter_ref (sitter);

  if (sitter->child_setup)
    {
      PING();
      (*sitter->child_setup) (sitter->user_data);
    }

  _dbus_verbose ("babysitter: spawning %s\n", sitter->executable);

  PING();
  if (sitter->envp != NULL)
    sitter->child_handle = (HANDLE) spawnve (P_NOWAIT, sitter->executable,
                           (const char * const *) sitter->argv,
                           (const char * const *) sitter->envp);
  else
    sitter->child_handle = (HANDLE) spawnv (P_NOWAIT, sitter->executable,
                                            (const char * const *) sitter->argv);

  PING();
  if (sitter->child_handle == (HANDLE) -1)
    {
      sitter->child_handle = NULL;
      sitter->have_spawn_errno = TRUE;
      sitter->spawn_errno = errno;
    }

  PING();
  SetEvent (sitter->start_sync_event);

  if (sitter->child_handle != NULL)
    {
      int ret;
      DWORD status;

      PING();
      WaitForSingleObject (sitter->child_handle, INFINITE);

      PING();
      ret = GetExitCodeProcess (sitter->child_handle, &status);

      sitter->child_status = status;
      sitter->have_child_status = TRUE;

      CloseHandle (sitter->child_handle);
      sitter->child_handle = NULL;
    }

#ifdef DBUS_BUILD_TESTS
  SetEvent (sitter->end_sync_event);
#endif

  PING();
  send (sitter->socket_to_main, " ", 1, 0);

  _dbus_babysitter_unref (sitter);

  return 0;
}
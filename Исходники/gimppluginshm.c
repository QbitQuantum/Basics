GimpPlugInShm *
gimp_plug_in_shm_new (void)
{
  /* allocate a piece of shared memory for use in transporting tiles
   *  to plug-ins. if we can't allocate a piece of shared memory then
   *  we'll fall back on sending the data over the pipe.
   */

  GimpPlugInShm *shm = g_slice_new0 (GimpPlugInShm);

  shm->shm_ID = -1;

#if defined(USE_SYSV_SHM)

  /* Use SysV shared memory mechanisms for transferring tile data. */
  {
    shm->shm_ID = shmget (IPC_PRIVATE, TILE_MAP_SIZE, IPC_CREAT | 0600);

    if (shm->shm_ID != -1)
      {
        shm->shm_addr = (guchar *) shmat (shm->shm_ID, NULL, 0);

        if (shm->shm_addr == (guchar *) -1)
          {
            g_printerr ("shmat() failed: %s\n" ERRMSG_SHM_DISABLE,
                        g_strerror (errno));
            shmctl (shm->shm_ID, IPC_RMID, NULL);
            shm->shm_ID = -1;
          }

#ifdef IPC_RMID_DEFERRED_RELEASE
        if (shm->shm_addr != (guchar *) -1)
          shmctl (shm->shm_ID, IPC_RMID, NULL);
#endif
      }
    else
      {
        g_printerr ("shmget() failed: %s\n" ERRMSG_SHM_DISABLE,
                    g_strerror (errno));
      }
  }

#elif defined(USE_WIN32_SHM)

  /* Use Win32 shared memory mechanisms for transferring tile data. */
  {
    gint  pid;
    gchar fileMapName[MAX_PATH];

    /* Our shared memory id will be our process ID */
    pid = GetCurrentProcessId ();

    /* From the id, derive the file map name */
    g_snprintf (fileMapName, sizeof (fileMapName), "GIMP%d.SHM", pid);

    /* Create the file mapping into paging space */
    shm->shm_handle = CreateFileMapping (INVALID_HANDLE_VALUE, NULL,
                                         PAGE_READWRITE, 0,
                                         TILE_MAP_SIZE,
                                         fileMapName);

    if (shm->shm_handle)
      {
        /* Map the shared memory into our address space for use */
        shm->shm_addr = (guchar *) MapViewOfFile (shm->shm_handle,
                                                  FILE_MAP_ALL_ACCESS,
                                                  0, 0, TILE_MAP_SIZE);

        /* Verify that we mapped our view */
        if (shm->shm_addr)
          {
            shm->shm_ID = pid;
          }
        else
          {
            g_printerr ("MapViewOfFile error: %d... " ERRMSG_SHM_DISABLE,
                        GetLastError ());
          }
      }
    else
      {
        g_printerr ("CreateFileMapping error: %d... " ERRMSG_SHM_DISABLE,
                    GetLastError ());
      }
  }

#elif defined(USE_POSIX_SHM)

  /* Use POSIX shared memory mechanisms for transferring tile data. */
  {
    gint  pid;
    gchar shm_handle[32];
    gint  shm_fd;

    /* Our shared memory id will be our process ID */
    pid = gimp_get_pid ();

    /* From the id, derive the file map name */
    g_snprintf (shm_handle, sizeof (shm_handle), "/gimp-shm-%d", pid);

    /* Create the file mapping into paging space */
    shm_fd = shm_open (shm_handle, O_RDWR | O_CREAT, 0600);

    if (shm_fd != -1)
      {
        if (ftruncate (shm_fd, TILE_MAP_SIZE) != -1)
          {
            /* Map the shared memory into our address space for use */
            shm->shm_addr = (guchar *) mmap (NULL, TILE_MAP_SIZE,
                                             PROT_READ | PROT_WRITE, MAP_SHARED,
                                             shm_fd, 0);

            /* Verify that we mapped our view */
            if (shm->shm_addr != MAP_FAILED)
              {
                shm->shm_ID = pid;
              }
            else
              {
                g_printerr ("mmap() failed: %s\n" ERRMSG_SHM_DISABLE,
                            g_strerror (errno));

                shm_unlink (shm_handle);
              }
          }
        else
          {
            g_printerr ("ftruncate() failed: %s\n" ERRMSG_SHM_DISABLE,
                        g_strerror (errno));

            shm_unlink (shm_handle);
          }

        close (shm_fd);
      }
    else
      {
        g_printerr ("shm_open() failed: %s\n" ERRMSG_SHM_DISABLE,
                    g_strerror (errno));
      }
  }

#endif

  if (shm->shm_ID == -1)
    {
      g_slice_free (GimpPlugInShm, shm);
      shm = NULL;
    }
  else
    {
      GIMP_LOG (SHM, "attached shared memory segment ID = %d", shm->shm_ID);
    }

  return shm;
}
/*
 * QueueOpen
 *
 * Open existing queue which has given key.  If there is no queue with given
 * key, or matched shared memory segment is not created by pgut, error occurs
 * and never return.
 */
Queue *
QueueOpen(unsigned key)
{
    Queue		   *self;
    ShmemHandle		handle;
    QueueHeader	   *header;

#ifdef WIN32
    char	shmemName[MAX_PATH];

    win32_shmemName(shmemName, lengthof(shmemName), key);

    handle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, shmemName);
    if (handle == NULL)
        elog(ERROR, "OpenFileMapping(%s) failed: errcode=%lu", shmemName, GetLastError());

    header = MapViewOfFile(handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (header == NULL)
        elog(ERROR, "MapViewOfFile failed: errcode=%lu", GetLastError());
#else
    handle = shmget(key, 0, 0);
    if (handle < 0)
        elog(ERROR, "shmget(id=%d) failed: %m", key);

    /* OK, should be able to attach to the segment */
    header = shmat(handle, NULL, PG_SHMAT_FLAGS);
    /* failed: must be some other app's */
    if (header == (void *) -1)
        elog(ERROR, "shmat(id=%d) failed: %m", key);
#endif

    /* check magic number */
    if (header->magic != PGUTShmemMagic)
    {
#ifdef WIN32
        UnmapViewOfFile(header);
        CloseHandle(handle);
#else
        shmdt(header);
        shmctl(handle, IPC_RMID, NULL);
#endif
        elog(ERROR, "segment belongs to a non-pgut app");
    }

    self = palloc(sizeof(Queue));
    self->handle = handle;
    self->header = header;
    self->size = header->size;
    return self;
}
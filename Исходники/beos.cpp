/*
 * This function is lifted from Simple Directmedia Layer (SDL):
 *  http://www.libsdl.org/
 */
static void tryDir(const char *d, PHYSFS_StringCallback callback, void *data)
{
    BDirectory dir;
    dir.SetTo(d);
    if (dir.InitCheck() != B_NO_ERROR)
        return;

    dir.Rewind();
    BEntry entry;
    while (dir.GetNextEntry(&entry) >= 0)
    {
        BPath path;
        const char *name;
        entry_ref e;

        if (entry.GetPath(&path) != B_NO_ERROR)
            continue;

        name = path.Path();

        if (entry.GetRef(&e) != B_NO_ERROR)
            continue;

        if (entry.IsDirectory())
        {
            if (strcmp(e.name, "floppy") != 0)
                tryDir(name, callback, data);
        } /* if */

        else
        {
            bool add_it = false;
            int devfd;
            device_geometry g;

            if (strcmp(e.name, "raw") == 0)  /* ignore partitions. */
            {
                int devfd = open(name, O_RDONLY);
                if (devfd >= 0)
                {
                    if (ioctl(devfd, B_GET_GEOMETRY, &g, sizeof(g)) >= 0)
                    {
                        if (g.device_type == B_CD)
                        {
                            char *mntpnt = getMountPoint(name);
                            if (mntpnt != NULL)
                            {
                                callback(data, mntpnt);
                                allocator.Free(mntpnt);  /* !!! FIXME: lose this malloc! */
                            } /* if */
                        } /* if */
                    } /* if */
                } /* if */
            } /* if */

            close(devfd);
        } /* else */
    } /* while */
} /* tryDir */
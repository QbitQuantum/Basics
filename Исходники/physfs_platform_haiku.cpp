    /*
     * This function is lifted from Simple Directmedia Layer (SDL):
     *  https://www.libsdl.org/  ... this is zlib-licensed code, too.
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
            continue;
        } /* if */

        const int devfd = open(name, O_RDONLY);
        if (devfd < 0)
            continue;

        device_geometry g;
        const int rc = ioctl(devfd, B_GET_GEOMETRY, &g, sizeof (g));
        close(devfd);
        if (rc < 0)
            continue;

        if (g.device_type != B_CD)
            continue;

        char mntpnt[B_FILE_NAME_LENGTH];
        if (getMountPoint(name, mntpnt, sizeof (mntpnt)))
            callback(data, mntpnt);
    } /* while */
} /* tryDir */
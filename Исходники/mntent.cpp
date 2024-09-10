    int
    getmntent_haiku(int* cookie, struct mnttab* mp)
    {
        static BLocker mntent_locker;
        mntent_locker.Lock();

        int ret = -1;
        BVolumeRoster roster;
        char buf[B_PATH_NAME_LENGTH];
        int buflen = 0;
        BVolume volume;
        BDirectory rootDir;
        BEntry rootDirEntry;
        BPath rootDirPath;

        roster.Rewind();
        for (int i = 0; i <= *cookie; i++)
            if (roster.GetNextVolume(&volume) != B_NO_ERROR)
                goto bail;

        // volume name
        volume.GetName(buf);
        buflen = strlen(buf);

        if (buflen == 0) {
            buflen = strlen(MNTENT_MP_UNKNOWN);
            strlcpy(buf, MNTENT_MP_UNKNOWN, buflen + 1);
        }

        mp->mnt_special = (char* )malloc(sizeof(char) * (buflen+1));
        strlcpy(mp->mnt_special, buf, buflen+1);

        // mount point
        if (volume.GetRootDirectory(&rootDir) != B_OK ||
                rootDir.GetEntry(&rootDirEntry) != B_OK   ||
                rootDirEntry.GetPath(&rootDirPath) != B_OK)
            goto bail;

        buflen = strlen(rootDirPath.Path());
        mp->mnt_mountp = (char* )malloc(sizeof(char) * (buflen+1));
        strlcpy(mp->mnt_mountp, rootDirPath.Path(), buflen + 1);

        // partition type.
        fs_info info;
        if (fs_stat_dev(volume.Device(), &info) != B_OK)
            goto bail;

        buflen = strlen(info.fsh_name);
        mp->mnt_fstype = (char* )malloc(sizeof(char) * (buflen+1));
        strlcpy(mp->mnt_fstype, info.fsh_name, buflen+1);

        // fs options. set default options for all file systems for now.
        buflen = strlen(MNTENT_MP_DEFAULT_OPTS);
        mp->mnt_mntopts = (char* )malloc(sizeof(char) * (buflen+2+1)); // extra space for ro/rw
        strlcpy(mp->mnt_mntopts, MNTENT_MP_DEFAULT_OPTS, buflen + 2 + 1);
        strcat(mp->mnt_mntopts, volume.IsReadOnly() ? ",ro":",rw");

        // mount time. no idea how i can get this. set it to 0 for now.
        buflen = 1;
        mp->mnt_time = (char* )malloc(sizeof(char) * (buflen+1));
        strlcpy(mp->mnt_time, "0", buflen + 1);

        (*cookie)++;
        ret = 0; /* success! */

bail:
        mntent_locker.Unlock();
        return ret;
    }
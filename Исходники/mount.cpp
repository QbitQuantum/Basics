/* mounts, creating the device if needed+possible */
int my_mount(const char *dev, const char *location, const char *fs, int force_rw)
{
    unsigned long flags = MS_MGC_VAL | (force_rw ? 0 : MS_RDONLY);
    char * opts = NULL;
    struct stat buf;
    int rc;

    if (strcmp(fs, "nfs")) {
        rc = ensure_dev_exists(dev);
        if (rc != 0) {
            log_message("could not create required device file");
            return -1;
        }
    }

    log_message("mounting %s on %s as type %s", dev, location, fs);

    if (stat(location, &buf)) {
        if (mkdir(location, 0755)) {
            log_perror("could not create location dir");
            return -1;
        }
    } else if (!S_ISDIR(buf.st_mode)) {
        log_message("not a dir %s, will unlink and mkdir", location);
        if (unlink(location)) {
            log_perror("could not unlink");
            return -1;
        }
        if (mkdir(location, 0755)) {
            log_perror("could not create location dir");
            return -1;
        }
    }

#ifndef DISABLE_MEDIAS
    if (!strcmp(fs, "vfat")) {
        my_modprobe("nls_cp437", ANY_DRIVER_TYPE, NULL);
        my_modprobe("nls_iso8859_1", ANY_DRIVER_TYPE, NULL);
        my_modprobe("vfat", ANY_DRIVER_TYPE, NULL);
        opts = (char*)"check=relaxed";
    }

    if (!strcmp(fs, "ntfs")) {
        my_modprobe("ntfs", ANY_DRIVER_TYPE, NULL);
    }

    if (!strcmp(fs, "reiserfs"))
        my_modprobe("reiserfs", ANY_DRIVER_TYPE, NULL);

    if (!strcmp(fs, "reiser4"))
        my_modprobe("reiser4", ANY_DRIVER_TYPE, NULL);

    if (!strcmp(fs, "jfs"))
        my_modprobe("jfs", ANY_DRIVER_TYPE, NULL);

    if (!strcmp(fs, "xfs"))
        my_modprobe("xfs", ANY_DRIVER_TYPE, NULL);

    if (!strcmp(fs, "ext4"))
        my_modprobe("ext4", ANY_DRIVER_TYPE, NULL);

    if (!strcmp(fs, "btrfs"))
        my_modprobe("btrfs", ANY_DRIVER_TYPE, NULL);

#endif
    if (!strcmp(fs, "iso9660"))
        my_modprobe("isofs", ANY_DRIVER_TYPE, NULL);

#ifndef DISABLE_NETWORK
    if (!strcmp(fs, "nfs")) {
        my_modprobe("nfs", ANY_DRIVER_TYPE, NULL);
        log_message("preparing nfsmount for %s", dev);
        rc = nfsmount_prepare(dev, &opts);
        if (rc != 0)
            return rc;
    }
#endif

    rc = mount(dev, location, fs, flags, opts);
    if (rc != 0) {
        log_perror("mount failed");
        rmdir(location);
    }

    return rc;
}
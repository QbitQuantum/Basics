int tagpopen() {

    dev_t devt;
	struct stat     st;
    int    rc = 0;

    devt = makedev(TAGP_MAJOR, 0);

    if (rc) {
        if (errno == ENOENT) {
            /* dev node does not exist. */
            rc = mkdir(DEVICE_NAME, (S_IFDIR | S_IRWXU |
                                                S_IRGRP | S_IXGRP |
                                                S_IROTH | S_IXOTH));
        } else {
            printf("ERROR: Problem with Base dev directory.  Error code from stat() is %d\n\n", errno);
        }

    } else {
        if (!(st.st_mode & S_IFDIR)) {
            rc = unlink(DEVICE_NAME);
            if (!rc) {
                rc = mkdir(DEVICE_NAME, (S_IFDIR | S_IRWXU |
                                                S_IRGRP | S_IXGRP |
                                                S_IROTH | S_IXOTH));
            }
        }
    }

    /*
     * Check for the /dev/tbase node, and create if it does not
     * exist.
     */
    rc = stat(DEVICE_NAME, &st);
    if (rc) {
        if (errno == ENOENT) {
            /* dev node does not exist */
            rc = mknod(DEVICE_NAME, (S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP), devt);
        } else {
            printf("ERROR:Problem with tbase device node directory.  Error code form stat() is %d\n\n", errno);
        }

    } else {
        /*
         * /dev/tbase CHR device exists.  Check to make sure it is for a
         * block device and that it has the right major and minor.
         */
        if ((!(st.st_mode & S_IFCHR)) ||
             (st.st_rdev != devt)) {

            /* Recreate the dev node. */
            rc = unlink(DEVICE_NAME);
            if (!rc) {
                rc = mknod(DEVICE_NAME, (S_IFCHR | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP), devt);
            }
        }
    }

    tagp_fd = open(DEVICE_NAME, O_RDWR);

    if (tagp_fd < 0) {
        printf("ERROR: Open of device %s failed %d errno = %d\n", DEVICE_NAME,tagp_fd, errno);
        return errno;
    }
    else {
        printf("Device opened successfully \n");
      return 0;
    }

}
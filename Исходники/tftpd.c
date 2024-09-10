/*
 * Validate file access.  Since we
 * have no uid or gid, for now require
 * file to exist and be publicly
 * readable/writable.
 * If we were invoked with arguments
 * from inetd then the file must also be
 * in one of the given directory prefixes.
 * Note also, full path name must be
 * given as we have no login directory.
 */
int
validate_access(int peer, char **filep, int mode)
{
    struct stat stbuf;
    int	fd;
    int	error;
    struct dirlist *dirp;
    static char pathname[MAXPATHLEN];
    char *filename = *filep;

    /*
     * Prevent tricksters from getting around the directory restrictions
     */
    if (strstr(filename, "/../"))
        return (EACCESS);

    if (*filename == '/') {
        /*
         * Allow the request if it's in one of the approved locations.
         * Special case: check the null prefix ("/") by looking
         * for length = 1 and relying on the arg. processing that
         * it's a /.
         */
        for (dirp = dirs; dirp->name != NULL; dirp++) {
            if (dirp->len == 1 ||
                    (!strncmp(filename, dirp->name, dirp->len) &&
                     filename[dirp->len] == '/'))
                break;
        }
        /* If directory list is empty, allow access to any file */
        if (dirp->name == NULL && dirp != dirs)
            return (EACCESS);
        if (stat(filename, &stbuf) < 0)
            return (errno == ENOENT ? ENOTFOUND : EACCESS);
        if ((stbuf.st_mode & S_IFMT) != S_IFREG)
            return (ENOTFOUND);
        if (mode == RRQ) {
            if ((stbuf.st_mode & S_IROTH) == 0)
                return (EACCESS);
        } else {
            if ((stbuf.st_mode & S_IWOTH) == 0)
                return (EACCESS);
        }
    } else {
        int err;

        /*
         * Relative file name: search the approved locations for it.
         * Don't allow write requests that avoid directory
         * restrictions.
         */

        if (!strncmp(filename, "../", 3))
            return (EACCESS);

        /*
         * If the file exists in one of the directories and isn't
         * readable, continue looking. However, change the error code
         * to give an indication that the file exists.
         */
        err = ENOTFOUND;
        for (dirp = dirs; dirp->name != NULL; dirp++) {
            snprintf(pathname, sizeof(pathname), "%s/%s",
                     dirp->name, filename);
            if (stat(pathname, &stbuf) == 0 &&
                    (stbuf.st_mode & S_IFMT) == S_IFREG) {
                if ((stbuf.st_mode & S_IROTH) != 0) {
                    break;
                }
                err = EACCESS;
            }
        }
        if (dirp->name != NULL)
            *filep = filename = pathname;
        else if (mode == RRQ)
            return (err);
    }

    /*
     * This option is handled here because it (might) require(s) the
     * size of the file.
     */
    option_tsize(peer, NULL, mode, &stbuf);

    if (mode == RRQ)
        fd = open(filename, O_RDONLY);
    else {
        if (create_new) {
            if (increase_name) {
                error = find_next_name(filename, &fd);
                if (error > 0)
                    return (error + 100);
            } else
                fd = open(filename,
                          O_WRONLY | O_TRUNC | O_CREAT,
                          S_IRUSR | S_IWUSR | S_IRGRP |
                          S_IWGRP | S_IROTH | S_IWOTH );
        } else
            fd = open(filename, O_WRONLY | O_TRUNC);
    }
    if (fd < 0)
        return (errno + 100);
    file = fdopen(fd, (mode == RRQ)? "r":"w");
    if (file == NULL) {
        close(fd);
        return (errno + 100);
    }
    return (0);
}
/* If a pidfile has been configured, creates it and stores the running
 * process's pid in it.  Ensures that the pidfile will be deleted when the
 * process exits. */
static void
make_pidfile(void)
{
    int error;

    error = GetFileAttributes(pidfile);
    if (error != INVALID_FILE_ATTRIBUTES) {
        /* pidfile exists. Try to unlink() it. */
        error = unlink(pidfile);
        if (error) {
            VLOG_FATAL("Failed to delete existing pidfile %s (%s)", pidfile,
                       ovs_strerror(errno));
        }
    }

    filep_pidfile = fopen(pidfile, "w");
    if (filep_pidfile == NULL) {
        VLOG_FATAL("failed to open %s (%s)", pidfile, ovs_strerror(errno));
    }

    fatal_signal_add_hook(unlink_pidfile, NULL, NULL, true);

    fprintf(filep_pidfile, "%d\n", _getpid());
    if (fflush(filep_pidfile) == EOF) {
        VLOG_FATAL("Failed to write into the pidfile %s", pidfile);
    }

    /* Don't close the pidfile till the process exits. */
}
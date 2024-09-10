static int
virLXCProcessReadLogOutputData(virDomainObjPtr vm,
                               int fd,
                               char *buf,
                               size_t buflen)
{
    int retries = 10;
    int got = 0;
    int ret = -1;
    char *filter_next = buf;

    buf[0] = '\0';

    while (retries) {
        ssize_t bytes;
        bool isdead = false;
        char *eol;

        if (vm->pid <= 0 ||
            (kill(vm->pid, 0) == -1 && errno == ESRCH))
            isdead = true;

        /* Any failures should be detected before we read the log, so we
         * always have something useful to report on failure. */
        bytes = saferead(fd, buf+got, buflen-got-1);
        if (bytes < 0) {
            virReportSystemError(errno, "%s",
                                 _("Failure while reading log output"));
            goto cleanup;
        }

        got += bytes;
        buf[got] = '\0';

        /* Filter out debug messages from intermediate libvirt process */
        while ((eol = strchr(filter_next, '\n'))) {
            *eol = '\0';
            if (virLXCProcessIgnorableLogLine(filter_next)) {
                memmove(filter_next, eol + 1, got - (eol - buf));
                got -= eol + 1 - filter_next;
            } else {
                filter_next = eol + 1;
                *eol = '\n';
            }
        }

        if (got == buflen-1) {
            virReportError(VIR_ERR_INTERNAL_ERROR,
                           _("Out of space while reading log output: %s"),
                           buf);
            goto cleanup;
        }

        if (isdead) {
            ret = got;
            goto cleanup;
        }

        usleep(100*1000);
        retries--;
    }

    virReportError(VIR_ERR_INTERNAL_ERROR,
                   _("Timed out while reading log output: %s"),
                   buf);

 cleanup:
    return ret;
}
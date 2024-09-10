static int setup_machine_raw(uint64_t size, sd_bus_error *error) {
        _cleanup_free_ char *tmp = NULL;
        _cleanup_close_ int fd = -1;
        struct statvfs ss;
        pid_t pid = 0;
        int r;

        /* We want to be able to make use of btrfs-specific file
         * system features, in particular subvolumes, reflinks and
         * quota. Hence, if we detect that /var/lib/machines.raw is
         * not located on btrfs, let's create a loopback file, place a
         * btrfs file system into it, and mount it to
         * /var/lib/machines. */

        fd = open("/var/lib/machines.raw", O_RDWR|O_CLOEXEC|O_NONBLOCK|O_NOCTTY);
        if (fd >= 0)
                return TAKE_FD(fd);

        if (errno != ENOENT)
                return sd_bus_error_set_errnof(error, errno, "Failed to open /var/lib/machines.raw: %m");

        r = tempfn_xxxxxx("/var/lib/machines.raw", NULL, &tmp);
        if (r < 0)
                return r;

        (void) mkdir_p_label("/var/lib", 0755);
        fd = open(tmp, O_RDWR|O_CREAT|O_EXCL|O_NOCTTY|O_CLOEXEC, 0600);
        if (fd < 0)
                return sd_bus_error_set_errnof(error, errno, "Failed to create /var/lib/machines.raw: %m");

        if (fstatvfs(fd, &ss) < 0) {
                r = sd_bus_error_set_errnof(error, errno, "Failed to determine free space on /var/lib/machines.raw: %m");
                goto fail;
        }

        if (ss.f_bsize * ss.f_bavail < VAR_LIB_MACHINES_FREE_MIN) {
                r = sd_bus_error_setf(error, SD_BUS_ERROR_FAILED, "Not enough free disk space to set up /var/lib/machines.");
                goto fail;
        }

        if (ftruncate(fd, size) < 0) {
                r = sd_bus_error_set_errnof(error, errno, "Failed to enlarge /var/lib/machines.raw: %m");
                goto fail;
        }

        r = safe_fork("(mkfs)", FORK_RESET_SIGNALS|FORK_DEATHSIG, &pid);
        if (r < 0) {
                sd_bus_error_set_errnof(error, r, "Failed to fork mkfs.btrfs: %m");
                goto fail;
        }
        if (r == 0) {

                /* Child */

                fd = safe_close(fd);

                execlp("mkfs.btrfs", "-Lvar-lib-machines", tmp, NULL);
                if (errno == ENOENT)
                        _exit(99);

                _exit(EXIT_FAILURE);
        }

        r = wait_for_terminate_and_check("mkfs", pid, 0);
        pid = 0;

        if (r < 0) {
                sd_bus_error_set_errnof(error, r, "Failed to wait for mkfs.btrfs: %m");
                goto fail;
        }
        if (r == 99) {
                r = sd_bus_error_set_errnof(error, ENOENT, "Cannot set up /var/lib/machines, mkfs.btrfs is missing");
                goto fail;
        }
        if (r != EXIT_SUCCESS) {
                r = sd_bus_error_setf(error, SD_BUS_ERROR_FAILED, "mkfs.btrfs failed with error code %i", r);
                goto fail;
        }

        r = rename_noreplace(AT_FDCWD, tmp, AT_FDCWD, "/var/lib/machines.raw");
        if (r < 0) {
                sd_bus_error_set_errnof(error, r, "Failed to move /var/lib/machines.raw into place: %m");
                goto fail;
        }

        return TAKE_FD(fd);

fail:
        unlink_noerrno(tmp);

        if (pid > 1)
                kill_and_sigcont(pid, SIGKILL);

        return r;
}
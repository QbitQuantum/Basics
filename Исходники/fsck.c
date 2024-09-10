int main(int argc, char *argv[]) {
        const char *cmdline[9];
        int i = 0, r = EXIT_FAILURE, q;
        pid_t pid;
        siginfo_t status;
        _cleanup_udev_unref_ struct udev *udev = NULL;
        _cleanup_udev_device_unref_ struct udev_device *udev_device = NULL;
        const char *device, *type;
        bool root_directory;
        int progress_pipe[2] = { -1, -1 };
        char dash_c[2+10+1];
        struct stat st;

        if (argc > 2) {
                log_error("This program expects one or no arguments.");
                return EXIT_FAILURE;
        }

        log_set_target(LOG_TARGET_AUTO);
        log_parse_environment();
        log_open();

        umask(0022);

        parse_proc_cmdline(parse_proc_cmdline_item);
        test_files();

        if (!arg_force && arg_skip)
                return 0;

        udev = udev_new();
        if (!udev) {
                log_oom();
                return EXIT_FAILURE;
        }

        if (argc > 1) {
                device = argv[1];
                root_directory = false;

                if (stat(device, &st) < 0) {
                        log_error("Failed to stat '%s': %m", device);
                        return EXIT_FAILURE;
                }

                udev_device = udev_device_new_from_devnum(udev, 'b', st.st_rdev);
                if (!udev_device) {
                        log_error("Failed to detect device %s", device);
                        return EXIT_FAILURE;
                }
        } else {
                struct timespec times[2];

                /* Find root device */

                if (stat("/", &st) < 0) {
                        log_error("Failed to stat() the root directory: %m");
                        return EXIT_FAILURE;
                }

                /* Virtual root devices don't need an fsck */
                if (major(st.st_dev) == 0)
                        return EXIT_SUCCESS;

                /* check if we are already writable */
                times[0] = st.st_atim;
                times[1] = st.st_mtim;
                if (utimensat(AT_FDCWD, "/", times, 0) == 0) {
                        log_info("Root directory is writable, skipping check.");
                        return EXIT_SUCCESS;
                }

                udev_device = udev_device_new_from_devnum(udev, 'b', st.st_dev);
                if (!udev_device) {
                        log_error("Failed to detect root device.");
                        return EXIT_FAILURE;
                }

                device = udev_device_get_devnode(udev_device);
                if (!device) {
                        log_error("Failed to detect device node of root directory.");
                        return EXIT_FAILURE;
                }

                root_directory = true;
        }

        type = udev_device_get_property_value(udev_device, "ID_FS_TYPE");
        if (type) {
                r = fsck_exists(type);
                if (r == -ENOENT) {
                        log_info("fsck.%s doesn't exist, not checking file system on %s", type, device);
                        return EXIT_SUCCESS;
                } else if (r < 0)
                        log_warning("fsck.%s cannot be used for %s: %s", type, device, strerror(-r));
        }

        if (arg_show_progress)
                if (pipe(progress_pipe) < 0) {
                        log_error("pipe(): %m");
                        return EXIT_FAILURE;
                }

        cmdline[i++] = "/sbin/fsck";
        cmdline[i++] =  arg_repair;
        cmdline[i++] = "-T";
        cmdline[i++] = "-l";

        if (!root_directory)
                cmdline[i++] = "-M";

        if (arg_force)
                cmdline[i++] = "-f";

        if (progress_pipe[1] >= 0) {
                snprintf(dash_c, sizeof(dash_c), "-C%i", progress_pipe[1]);
                char_array_0(dash_c);
                cmdline[i++] = dash_c;
        }

        cmdline[i++] = device;
        cmdline[i++] = NULL;

        pid = fork();
        if (pid < 0) {
                log_error("fork(): %m");
                goto finish;
        } else if (pid == 0) {
                /* Child */
                if (progress_pipe[0] >= 0)
                        safe_close(progress_pipe[0]);
                execv(cmdline[0], (char**) cmdline);
                _exit(8); /* Operational error */
        }

        progress_pipe[1] = safe_close(progress_pipe[1]);

        if (progress_pipe[0] >= 0) {
                process_progress(progress_pipe[0]);
                progress_pipe[0] = -1;
        }

        q = wait_for_terminate(pid, &status);
        if (q < 0) {
                log_error("waitid(): %s", strerror(-q));
                goto finish;
        }

        if (status.si_code != CLD_EXITED || (status.si_status & ~1)) {

                if (status.si_code == CLD_KILLED || status.si_code == CLD_DUMPED)
                        log_error("fsck terminated by signal %s.", signal_to_string(status.si_status));
                else if (status.si_code == CLD_EXITED)
                        log_error("fsck failed with error code %i.", status.si_status);
                else
                        log_error("fsck failed due to unknown reason.");

                if (status.si_code == CLD_EXITED && (status.si_status & 2) && root_directory)
                        /* System should be rebooted. */
                        start_target(SPECIAL_REBOOT_TARGET);
                else if (status.si_code == CLD_EXITED && (status.si_status & 6))
                        /* Some other problem */
                        start_target(SPECIAL_EMERGENCY_TARGET);
                else {
                        r = EXIT_SUCCESS;
                        log_warning("Ignoring error.");
                }

        } else
                r = EXIT_SUCCESS;

        if (status.si_code == CLD_EXITED && (status.si_status & 1))
                touch("/run/systemd/quotacheck");

finish:
        safe_close_pair(progress_pipe);

        return r;
}
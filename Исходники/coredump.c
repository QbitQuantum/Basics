static int save_external_coredump(
                const char *context[_CONTEXT_MAX],
                int input_fd,
                char **ret_filename,
                int *ret_node_fd,
                int *ret_data_fd,
                uint64_t *ret_size,
                bool *ret_truncated) {

        _cleanup_free_ char *fn = NULL, *tmp = NULL;
        _cleanup_close_ int fd = -1;
        uint64_t rlimit, process_limit, max_size;
        struct stat st;
        uid_t uid;
        int r;

        assert(context);
        assert(ret_filename);
        assert(ret_node_fd);
        assert(ret_data_fd);
        assert(ret_size);

        r = parse_uid(context[CONTEXT_UID], &uid);
        if (r < 0)
                return log_error_errno(r, "Failed to parse UID: %m");

        r = safe_atou64(context[CONTEXT_RLIMIT], &rlimit);
        if (r < 0)
                return log_error_errno(r, "Failed to parse resource limit '%s': %m", context[CONTEXT_RLIMIT]);
        if (rlimit < page_size()) {
                /* Is coredumping disabled? Then don't bother saving/processing the coredump.
                 * Anything below PAGE_SIZE cannot give a readable coredump (the kernel uses
                 * ELF_EXEC_PAGESIZE which is not easily accessible, but is usually the same as PAGE_SIZE. */
                return log_info_errno(SYNTHETIC_ERRNO(EBADSLT),
                                      "Resource limits disable core dumping for process %s (%s).",
                                      context[CONTEXT_PID], context[CONTEXT_COMM]);
        }

        process_limit = MAX(arg_process_size_max, storage_size_max());
        if (process_limit == 0)
                return log_debug_errno(SYNTHETIC_ERRNO(EBADSLT),
                                       "Limits for coredump processing and storage are both 0, not dumping core.");

        /* Never store more than the process configured, or than we actually shall keep or process */
        max_size = MIN(rlimit, process_limit);

        r = make_filename(context, &fn);
        if (r < 0)
                return log_error_errno(r, "Failed to determine coredump file name: %m");

        (void) mkdir_p_label("/var/lib/systemd/coredump", 0755);

        fd = open_tmpfile_linkable(fn, O_RDWR|O_CLOEXEC, &tmp);
        if (fd < 0)
                return log_error_errno(fd, "Failed to create temporary file for coredump %s: %m", fn);

        r = copy_bytes(input_fd, fd, max_size, 0);
        if (r < 0) {
                log_error_errno(r, "Cannot store coredump of %s (%s): %m", context[CONTEXT_PID], context[CONTEXT_COMM]);
                goto fail;
        }
        *ret_truncated = r == 1;
        if (*ret_truncated)
                log_struct(LOG_INFO,
                           LOG_MESSAGE("Core file was truncated to %zu bytes.", max_size),
                           "SIZE_LIMIT=%zu", max_size,
                           "MESSAGE_ID=" SD_MESSAGE_TRUNCATED_CORE_STR);

        if (fstat(fd, &st) < 0) {
                log_error_errno(errno, "Failed to fstat core file %s: %m", coredump_tmpfile_name(tmp));
                goto fail;
        }

        if (lseek(fd, 0, SEEK_SET) == (off_t) -1) {
                log_error_errno(errno, "Failed to seek on %s: %m", coredump_tmpfile_name(tmp));
                goto fail;
        }

#if HAVE_XZ || HAVE_LZ4
        /* If we will remove the coredump anyway, do not compress. */
        if (arg_compress && !maybe_remove_external_coredump(NULL, st.st_size)) {

                _cleanup_free_ char *fn_compressed = NULL, *tmp_compressed = NULL;
                _cleanup_close_ int fd_compressed = -1;

                fn_compressed = strappend(fn, COMPRESSED_EXT);
                if (!fn_compressed) {
                        log_oom();
                        goto uncompressed;
                }

                fd_compressed = open_tmpfile_linkable(fn_compressed, O_RDWR|O_CLOEXEC, &tmp_compressed);
                if (fd_compressed < 0) {
                        log_error_errno(fd_compressed, "Failed to create temporary file for coredump %s: %m", fn_compressed);
                        goto uncompressed;
                }

                r = compress_stream(fd, fd_compressed, -1);
                if (r < 0) {
                        log_error_errno(r, "Failed to compress %s: %m", coredump_tmpfile_name(tmp_compressed));
                        goto fail_compressed;
                }

                r = fix_permissions(fd_compressed, tmp_compressed, fn_compressed, context, uid);
                if (r < 0)
                        goto fail_compressed;

                /* OK, this worked, we can get rid of the uncompressed version now */
                if (tmp)
                        unlink_noerrno(tmp);

                *ret_filename = TAKE_PTR(fn_compressed);     /* compressed */
                *ret_node_fd = TAKE_FD(fd_compressed);      /* compressed */
                *ret_data_fd = TAKE_FD(fd);                 /* uncompressed */
                *ret_size = (uint64_t) st.st_size; /* uncompressed */

                return 0;

        fail_compressed:
                if (tmp_compressed)
                        (void) unlink(tmp_compressed);
        }

uncompressed:
#endif

        r = fix_permissions(fd, tmp, fn, context, uid);
        if (r < 0)
                goto fail;

        *ret_filename = TAKE_PTR(fn);
        *ret_data_fd = TAKE_FD(fd);
        *ret_node_fd = -1;
        *ret_size = (uint64_t) st.st_size;

        return 0;

fail:
        if (tmp)
                (void) unlink(tmp);
        return r;
}
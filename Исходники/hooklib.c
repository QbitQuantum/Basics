char *get_backtrace(const char *dump_dir_name, unsigned timeout_sec, const char *debuginfo_dirs)
{
    INITIALIZE_LIBABRT();

    struct dump_dir *dd = dd_opendir(dump_dir_name, /*flags:*/ 0);
    if (!dd)
        return NULL;
    char *executable = dd_load_text(dd, FILENAME_EXECUTABLE);
    dd_close(dd);

    /* Let user know what's going on */
    log(_("Generating backtrace"));

    unsigned i = 0;
    char *args[25];
    args[i++] = (char*)"gdb";
    args[i++] = (char*)"-batch";
    struct strbuf *set_debug_file_directory = strbuf_new();
    unsigned auto_load_base_index = 0;
    if(debuginfo_dirs == NULL)
    {
        // set non-existent debug file directory to prevent resolving
        // function names - we need offsets for core backtrace.
        strbuf_append_str(set_debug_file_directory, "set debug-file-directory /");
    }
    else
    {
        strbuf_append_str(set_debug_file_directory, "set debug-file-directory /usr/lib/debug");

        struct strbuf *debug_directories = strbuf_new();
        const char *p = debuginfo_dirs;
        while (1)
        {
            while (*p == ':')
                p++;
            if (*p == '\0')
                break;
            const char *colon_or_nul = strchrnul(p, ':');
            strbuf_append_strf(debug_directories, "%s%.*s/usr/lib/debug", (debug_directories->len == 0 ? "" : ":"),
                                                                          (int)(colon_or_nul - p), p);
            p = colon_or_nul;
        }

        strbuf_append_strf(set_debug_file_directory, ":%s", debug_directories->buf);

        args[i++] = (char*)"-iex";
        auto_load_base_index = i;
        args[i++] = xasprintf("add-auto-load-safe-path %s", debug_directories->buf);
        args[i++] = (char*)"-iex";
        args[i++] = xasprintf("add-auto-load-scripts-directory %s", debug_directories->buf);

        strbuf_free(debug_directories);
    }

    args[i++] = (char*)"-ex";
    const unsigned debug_dir_cmd_index = i++;
    args[debug_dir_cmd_index] = strbuf_free_nobuf(set_debug_file_directory);

    /* "file BINARY_FILE" is needed, without it gdb cannot properly
     * unwind the stack. Currently the unwind information is located
     * in .eh_frame which is stored only in binary, not in coredump
     * or debuginfo.
     *
     * Fedora GDB does not strictly need it, it will find the binary
     * by its build-id.  But for binaries either without build-id
     * (= built on non-Fedora GCC) or which do not have
     * their debuginfo rpm installed gdb would not find BINARY_FILE
     * so it is still makes sense to supply "file BINARY_FILE".
     *
     * Unfortunately, "file BINARY_FILE" doesn't work well if BINARY_FILE
     * was deleted (as often happens during system updates):
     * gdb uses specified BINARY_FILE
     * even if it is completely unrelated to the coredump.
     * See https://bugzilla.redhat.com/show_bug.cgi?id=525721
     *
     * TODO: check mtimes on COREFILE and BINARY_FILE and not supply
     * BINARY_FILE if it is newer (to at least avoid gdb complaining).
     */
    args[i++] = (char*)"-ex";
    const unsigned file_cmd_index = i++;
    args[file_cmd_index] = xasprintf("file %s", executable);
    free(executable);

    args[i++] = (char*)"-ex";
    const unsigned core_cmd_index = i++;
    args[core_cmd_index] = xasprintf("core-file %s/"FILENAME_COREDUMP, dump_dir_name);

    args[i++] = (char*)"-ex";
    const unsigned bt_cmd_index = i++;
    /*args[9] = ... see below */
    args[i++] = (char*)"-ex";
    args[i++] = (char*)"info sharedlib";
    /* glibc's abort() stores its message in __abort_msg variable */
    args[i++] = (char*)"-ex";
    args[i++] = (char*)"print (char*)__abort_msg";
    args[i++] = (char*)"-ex";
    args[i++] = (char*)"print (char*)__glib_assert_msg";
    args[i++] = (char*)"-ex";
    args[i++] = (char*)"info all-registers";
    args[i++] = (char*)"-ex";
    const unsigned dis_cmd_index = i++;
    args[dis_cmd_index] = (char*)"disassemble";
    args[i++] = NULL;

    /* Get the backtrace, but try to cap its size */
    /* Limit bt depth. With no limit, gdb sometimes OOMs the machine */
    unsigned bt_depth = 1024;
    const char *thread_apply_all = "thread apply all -ascending";
    const char *full = " full";
    char *bt = NULL;
    while (1)
    {
        args[bt_cmd_index] = xasprintf("%s backtrace %u%s", thread_apply_all, bt_depth, full);
        bt = exec_vp(args, /*redirect_stderr:*/ 1, timeout_sec, NULL);
        free(args[bt_cmd_index]);
        if ((bt && strnlen(bt, 256*1024) < 256*1024) || bt_depth <= 32)
        {
            break;
        }

        bt_depth /= 2;
        if (bt)
            log("Backtrace is too big (%u bytes), reducing depth to %u",
                        (unsigned)strlen(bt), bt_depth);
        else
            /* (NB: in fact, current impl. of exec_vp() never returns NULL) */
            log("Failed to generate backtrace, reducing depth to %u",
                        bt_depth);
        free(bt);

        /* Replace -ex disassemble (which disasms entire function $pc points to)
         * to a version which analyzes limited, small patch of code around $pc.
         * (Users reported a case where bare "disassemble" attempted to process
         * entire .bss).
         * TODO: what if "$pc-N" underflows? in my test, this happens:
         * Dump of assembler code from 0xfffffffffffffff0 to 0x30:
         * End of assembler dump.
         * (IOW: "empty" dump)
         */
        args[dis_cmd_index] = (char*)"disassemble $pc-20, $pc+64";

        if (bt_depth <= 64 && thread_apply_all[0] != '\0')
        {
            /* This program likely has gazillion threads, dont try to bt them all */
            bt_depth = 128;
            thread_apply_all = "";
        }
        if (bt_depth <= 64 && full[0] != '\0')
        {
            /* Looks like there are gigantic local structures or arrays, disable "full" bt */
            bt_depth = 128;
            full = "";
        }
    }

    if (auto_load_base_index > 0)
    {
        free(args[auto_load_base_index]);
        free(args[auto_load_base_index + 2]);
    }

    free(args[debug_dir_cmd_index]);
    free(args[file_cmd_index]);
    free(args[core_cmd_index]);
    return bt;
}
void os_spawn_process(const char *exe, const List<ByteBuffer> &args, bool detached) {
    pid_t pid = fork();
    if (pid == -1)
        panic("fork failed");
    if (pid != 0)
        return;
    if (detached) {
        if (setsid() == -1)
            panic("process detach failed");
    }

    const char **argv = ok_mem(allocate_zero<const char *>(args.length() + 2));
    argv[0] = exe;
    argv[args.length() + 1] = nullptr;
    for (int i = 0; i < args.length(); i += 1) {
        argv[i + 1] = args.at(i).raw();
    }
    execvp(exe, const_cast<char * const *>(argv));
    panic("execvp failed: %s", strerror(errno));
}
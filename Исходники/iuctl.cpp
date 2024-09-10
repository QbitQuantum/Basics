int join_iuctl() {
    struct stat info;
    Stat(QUEUE_PATH, &info);
    int fd = open(QUEUE_PATH, O_RDONLY);
    
    if (fd == -1) {
        return errno;
    }
    char server_pid_str[32];
    Read(fd, server_pid_str, min<size_t>(sizeof(server_pid_str),info.st_size));
    Close(fd);
    server_pid = atoi(server_pid_str);
    assert(server_pid > 0);
    if(kill(server_pid, 0) != 0) {
        return errno;
    }
    self_pid = getpid();
    assert(self_pid > 0);
    init_iuctl(false);
    return 0;
}
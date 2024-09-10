/* Start the reader thread and do all the file handle/descriptor redirection.
   Returns nonzero on success, zero on error. */
int win_stdin_start_thread(void) {
    int stdin_fd;
    int stdin_fmode;

    assert(stdin_thread == NULL);
    assert(stdin_pipe_r == NULL);
    assert(stdin_pipe_w == NULL);
    assert(thread_stdin_handle == NULL);

    /* Create the pipe that win_stdin_thread_func writes to. We reassign the
       read end to be the new stdin that the rest of the program sees. */
    if (CreatePipe(&stdin_pipe_r, &stdin_pipe_w, NULL, 0) == 0)
        return 0;

    /* Make a copy of the stdin handle to be used by win_stdin_thread_func.  It
       will remain a reference to the the true stdin after we fake stdin to read
       from the pipe instead. */
    if (DuplicateHandle(GetCurrentProcess(), GetStdHandle(STD_INPUT_HANDLE),
                        GetCurrentProcess(), &thread_stdin_handle,
                        0, FALSE, DUPLICATE_SAME_ACCESS) == 0) {
        CloseHandle(stdin_pipe_r);
        CloseHandle(stdin_pipe_w);
        return 0;
    }

    /* Set the stdin handle to read from the pipe. */
    if (SetStdHandle(STD_INPUT_HANDLE, stdin_pipe_r) == 0) {
        CloseHandle(stdin_pipe_r);
        CloseHandle(stdin_pipe_w);
        CloseHandle(thread_stdin_handle);
        return 0;
    }
    /* Need to redirect file descriptor 0 also. _open_osfhandle makes a new file
       descriptor from an existing handle. */
    /* Remember the newline translation mode (_O_TEXT or _O_BINARY), and
       restore it in the new file descriptor. */
    stdin_fmode = _getmode(STDIN_FILENO);
    stdin_fd = _open_osfhandle((intptr_t) GetStdHandle(STD_INPUT_HANDLE), _O_RDONLY | stdin_fmode);
    if (stdin_fd == -1) {
        CloseHandle(stdin_pipe_r);
        CloseHandle(stdin_pipe_w);
        CloseHandle(thread_stdin_handle);
        return 0;
    }
    dup2(stdin_fd, STDIN_FILENO);

    /* Finally, start up the thread. We don't bother keeping a reference to it
       because it runs until program termination. From here on out all reads
       from the stdin handle or file descriptor 0 will be reading from the
       anonymous pipe that is fed by the thread. */
    stdin_thread = CreateThread(NULL, 0, win_stdin_thread_func, NULL, 0, NULL);
    if (stdin_thread == NULL) {
        CloseHandle(stdin_pipe_r);
        CloseHandle(stdin_pipe_w);
        CloseHandle(thread_stdin_handle);
        return 0;
    }

    return 1;
}
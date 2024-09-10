static void dummy_pause_job(void) {
    ASYNC_JOB *job;
    ASYNC_WAIT_CTX *waitctx;
    OSSL_ASYNC_FD pipefds[2] = {0, 0};
    OSSL_ASYNC_FD *writefd;
#if defined(ASYNC_WIN)
    DWORD numwritten, numread;
    char buf = DUMMY_CHAR;
#elif defined(ASYNC_POSIX)
    char buf = DUMMY_CHAR;
#endif

    if ((job = ASYNC_get_current_job()) == NULL)
        return;

    waitctx = ASYNC_get_wait_ctx(job);

    if (ASYNC_WAIT_CTX_get_fd(waitctx, engine_dasync_id, &pipefds[0],
                              (void **)&writefd)) {
        pipefds[1] = *writefd;
    } else {
        writefd = OPENSSL_malloc(sizeof(*writefd));
        if (writefd == NULL)
            return;
#if defined(ASYNC_WIN)
        if (CreatePipe(&pipefds[0], &pipefds[1], NULL, 256) == 0) {
            OPENSSL_free(writefd);
            return;
        }
#elif defined(ASYNC_POSIX)
        if (pipe(pipefds) != 0) {
            OPENSSL_free(writefd);
            return;
        }
#endif
        *writefd = pipefds[1];

        if (!ASYNC_WAIT_CTX_set_wait_fd(waitctx, engine_dasync_id, pipefds[0],
                                        writefd, wait_cleanup)) {
            wait_cleanup(waitctx, engine_dasync_id, pipefds[0], writefd);
            return;
        }
    }
    /*
     * In the Dummy async engine we are cheating. We signal that the job
     * is complete by waking it before the call to ASYNC_pause_job(). A real
     * async engine would only wake when the job was actually complete
     */
#if defined(ASYNC_WIN)
    WriteFile(pipefds[1], &buf, 1, &numwritten, NULL);
#elif defined(ASYNC_POSIX)
    if (write(pipefds[1], &buf, 1) < 0)
        return;
#endif

    /* Ignore errors - we carry on anyway */
    ASYNC_pause_job();

    /* Clear the wake signal */
#if defined(ASYNC_WIN)
    ReadFile(pipefds[0], &buf, 1, &numread, NULL);
#elif defined(ASYNC_POSIX)
    if (read(pipefds[0], &buf, 1) < 0)
        return;
#endif
}
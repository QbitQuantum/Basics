static bool spawn_worker_thread(const _TCHAR *ip, socket_t sockfd, dyarr_t workers)
{
    size_t slot = INVALID_SOCKET;
    size_t i;
    worker_context_t *ctx;
    HANDLE thread;
    unsigned thread_id;

    assert(ip != NULL);
    assert(sockfd != INVALID_SOCKET);
    assert(workers != NULL);

    for (i = 0; i < dyarr_size(workers); ++i)
    {
        worker_context_t *elem = dyarr_at(workers, i);
        if (is_idle_worker_context_slot(elem, NULL))
        {
            if (elem->handle != NULL)
            {
                printf("Waiting for worker thread exiting...\n");
                WaitForSingleObject(elem->handle, INFINITE);
                CloseHandle(elem->handle);
                elem->handle = NULL;
            }

            if (elem->sockfd != INVALID_SOCKET)
            {
                closesock(elem->sockfd);
                elem->sockfd = INVALID_SOCKET;
            }

            slot = i;
            break;
        }
    }

    if (slot == INVALID_INDEX)
    {
        if (!dyarr_resize(workers, dyarr_size(workers) + 1))
        {
            fprintf(stderr, "No enough memory!\n");
            return false;
        }

        slot = dyarr_size(workers) - 1;
    }

    ctx = dyarr_at(workers, slot);

    thread = (HANDLE)_beginthreadex(
        NULL,
        0,
        (_beginthreadex_proc_type)worker_routine,
        ctx,
        CREATE_SUSPENDED,
        &thread_id);
    if (thread == NULL)
    {
        fprintf(stderr, "Failed to create worker thread!\n");
        return false;
    }

    ctx->handle = thread;
    ctx->sockfd = sockfd;
    ctx->running = 1;
    _tcscpy(ctx->ipstr, ip);

    printf("Starting working thread [%u]...\n", thread_id);
    printf("Now we have %zu worker threads.\n", dyarr_size(workers));

    ResumeThread(thread);

    return true;
}
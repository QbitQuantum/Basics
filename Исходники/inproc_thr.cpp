int main (int argc, char *argv [])
{
#if defined XS_HAVE_WINDOWS
    HANDLE local_thread;
#else
    pthread_t local_thread;
#endif
    void *ctx;
    void *s;
    int rc;
    int i;
    xs_msg_t msg;
    void *watch;
    unsigned long elapsed;
    unsigned long throughput;
    double megabits;

    if (argc != 3) {
        printf ("usage: thread_thr <message-size> <message-count>\n");
        return 1;
    }

    message_size = atoi (argv [1]);
    message_count = atoi (argv [2]);

    ctx = xs_init ();
    if (!ctx) {
        printf ("error in xs_init: %s\n", xs_strerror (errno));
        return -1;
    }

    s = xs_socket (ctx, XS_PULL);
    if (!s) {
        printf ("error in xs_socket: %s\n", xs_strerror (errno));
        return -1;
    }

    rc = xs_bind (s, "inproc://thr_test");
    if (rc == -1) {
        printf ("error in xs_bind: %s\n", xs_strerror (errno));
        return -1;
    }

#if defined XS_HAVE_WINDOWS
    local_thread = (HANDLE) _beginthreadex (NULL, 0,
        worker, ctx, 0 , NULL);
    if (local_thread == 0) {
        printf ("error in _beginthreadex\n");
        return -1;
    }
#else
    rc = pthread_create (&local_thread, NULL, worker, ctx);
    if (rc != 0) {
        printf ("error in pthread_create: %s\n", xs_strerror (rc));
        return -1;
    }
#endif

    rc = xs_msg_init (&msg);
    if (rc != 0) {
        printf ("error in xs_msg_init: %s\n", xs_strerror (errno));
        return -1;
    }

    printf ("message size: %d [B]\n", (int) message_size);
    printf ("message count: %d\n", (int) message_count);

    rc = xs_recvmsg (s, &msg, 0);
    if (rc < 0) {
        printf ("error in xs_recvmsg: %s\n", xs_strerror (errno));
        return -1;
    }
    if (xs_msg_size (&msg) != message_size) {
        printf ("message of incorrect size received\n");
        return -1;
    }

    watch = xs_stopwatch_start ();

    for (i = 0; i != message_count - 1; i++) {
        rc = xs_recvmsg (s, &msg, 0);
        if (rc < 0) {
            printf ("error in xs_recvmsg: %s\n", xs_strerror (errno));
            return -1;
        }
        if (xs_msg_size (&msg) != message_size) {
            printf ("message of incorrect size received\n");
            return -1;
        }
    }

    elapsed = xs_stopwatch_stop (watch);
    if (elapsed == 0)
        elapsed = 1;

    rc = xs_msg_close (&msg);
    if (rc != 0) {
        printf ("error in xs_msg_close: %s\n", xs_strerror (errno));
        return -1;
    }

#if defined XS_HAVE_WINDOWS
    DWORD rc2 = WaitForSingleObject (local_thread, INFINITE);
    if (rc2 == WAIT_FAILED) {
        printf ("error in WaitForSingleObject\n");
        return -1;
    }
    BOOL rc3 = CloseHandle (local_thread);
    if (rc3 == 0) {
        printf ("error in CloseHandle\n");
        return -1;
    }
#else
    rc = pthread_join (local_thread, NULL);
    if (rc != 0) {
        printf ("error in pthread_join: %s\n", xs_strerror (rc));
        return -1;
    }
#endif

    rc = xs_close (s);
    if (rc != 0) {
        printf ("error in xs_close: %s\n", xs_strerror (errno));
        return -1;
    }

    rc = xs_term (ctx);
    if (rc != 0) {
        printf ("error in xs_term: %s\n", xs_strerror (errno));
        return -1;
    }

    throughput = (unsigned long)
        ((double) message_count / (double) elapsed * 1000000);
    megabits = (double) (throughput * message_size * 8) / 1000000;

    printf ("mean throughput: %d [msg/s]\n", (int) throughput);
    printf ("mean throughput: %.3f [Mb/s]\n", (double) megabits);

    return 0;
}
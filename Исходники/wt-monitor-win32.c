static void *
wt_monitor_job_win32 (void *vmonitor)
{
    SeafWTMonitor *monitor = vmonitor;
    SeafWTMonitorPriv *priv = monitor->priv;
    /* 2 * sizeof(inotify_event) + 256, should be large enough for one event.*/
    RepoWatchInfo *info;


    DWORD bytesRead = 0;
    ULONG_PTR key = 0;
    OVERLAPPED *ol = NULL;

    /* Use I/O Completion Port to watch asynchronous events on:

     * 1) dir watch handles(events created by ReadDirectoryChangesW)
     * 2) the cmd pipe (which is a socket indeed)
     
     */

    if (!add_all_to_iocp(monitor)) {
        seaf_warning("Failed to add all to iocp\n");
        return NULL;
    }
    
    while (1) {

        BOOL ret = GetQueuedCompletionStatus
            (priv->iocp_handle,           /* iocp handle */
             &bytesRead,                  /* length of info */
             &key,                        /* completion key */
             &ol,                         /* OVERLAPPED */
             INFINITE);                   /* timeout */

        static int retry;

        if (!ret) {
            seaf_warning ("GetQueuedCompletionStatus failed, "
                          "error code %lu", GetLastError());

            if (retry++ < 3)
                continue;
            else
                break;
        } else {
            /* clear the retry counter on success */
            retry = 0;
        }

        if (key == (ULONG_PTR)monitor->cmd_pipe[0]) {     
            /* Triggered by a cmd pipe event */

            if (bytesRead != sizeof(WatchCommand)) {
                seaf_warning ("broken cmd from pipe: get"
                              " %d(expected: %d) bytes\n",
                              (int)bytesRead, sizeof(WatchCommand));
                continue;
            }

            seaf_debug ("recevied a pipe cmd, type %d for repo %s\n",
                        priv->cmd.type, priv->cmd.repo_id);

            handle_watch_command (monitor, &priv->cmd);

            reset_overlapped(ol);
            start_watch_cmd_pipe (monitor, ol);

        } else {
            /* Trigger by one of the dir watch handles */

            HANDLE hTriggered = (HANDLE)key;
            info = (RepoWatchInfo *)g_hash_table_lookup
                (priv->info_hash, (gconstpointer)hTriggered); 

            if (info) {
                DirWatchAux *aux = g_hash_table_lookup (priv->buf_hash,
                                                        (gconstpointer)hTriggered);

                process_events (info->status->repo_id, info, aux->buf, bytesRead);

                reset_overlapped(ol);
                if (!start_watch_dir_change(priv, hTriggered)) {

                    seaf_warning ("start_watch_dir_change failed"
                                  "for repo %s, error code %lu\n",
                                  info->status->repo_id, GetLastError());
                }
            } else {
                /* A previously unwatched dir_handle's DirWatchAux buf was
                   scheduled to be freed. */
                DirWatchAux *aux = g_hash_table_lookup (priv->buf_hash, (gconstpointer)hTriggered);
                if (aux && aux->unused)
                    g_free (aux);
                g_hash_table_remove (priv->buf_hash, (gconstpointer)hTriggered);
            }
        }
    }
    return NULL;
}
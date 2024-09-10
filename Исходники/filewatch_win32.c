void resman_check_watch(struct resman *rman)
{
    struct watch_dir *wdir;
    unsigned int idx;

    unsigned int num_handles = dynarr_size(rman->watch_handles);
    if(!num_handles) {
        return;
    }

    idx = WaitForMultipleObjectsEx(num_handles, rman->watch_handles, FALSE, 0, TRUE);
    if(idx == WAIT_FAILED) {
        unsigned int err = GetLastError();
        fprintf(stderr, "failed to check for file modification: %u\n", err);
        return;
    }
    if(idx >= WAIT_OBJECT_0 && idx < WAIT_OBJECT_0 + num_handles) {
        if(!(wdir = rb_find(rman->wdirbyev, rman->watch_handles[idx]))) {
            fprintf(stderr, "got change handle, but failed to find corresponding watch_dir!\n");
            return;
        }

        handle_event(rman, rman->watch_handles[idx], wdir);

        /* restart the watch call */
        ReadDirectoryChangesW(wdir->handle, wdir->buf, RES_BUF_SIZE, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE, 0, &wdir->over, 0);
    }
}
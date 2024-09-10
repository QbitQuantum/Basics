/*---------------------------------------------------------------------------*/
hg_return_t
hg_proc_set_size(hg_proc_t proc, hg_size_t req_buf_size)
{
    struct hg_proc *hg_proc = (struct hg_proc *) proc;
    hg_size_t new_buf_size;
    hg_size_t page_size;
    ptrdiff_t current_pos;
    hg_return_t ret = HG_SUCCESS;

#ifdef _WIN32
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    page_size = system_info.dwPageSize;
#else
    page_size = sysconf(_SC_PAGE_SIZE);
#endif
    new_buf_size = ((hg_size_t)(req_buf_size / page_size) + 1) * page_size;

    if (new_buf_size <= hg_proc_get_size(proc)) {
        HG_LOG_ERROR("Buffer is already of the size requested");
        ret = HG_SIZE_ERROR;
        goto done;
    }

    /* If was not using extra buffer init extra buffer */
    if (!hg_proc->extra_buf.buf) {
        /* Save current position */
        current_pos = (char *) hg_proc->proc_buf.buf_ptr -
                (char *) hg_proc->proc_buf.buf;

        /* Allocate buffer */
        hg_proc->extra_buf.buf = malloc(new_buf_size);
        if (!hg_proc->extra_buf.buf) {
            HG_LOG_ERROR("Could not allocate buffer");
            ret = HG_NOMEM_ERROR;
            goto done;
        }

        /* Copy proc_buf (should be small) */
        memcpy(hg_proc->extra_buf.buf, hg_proc->proc_buf.buf, current_pos);
        hg_proc->extra_buf.size = new_buf_size;
        hg_proc->extra_buf.buf_ptr = (char *) hg_proc->extra_buf.buf + current_pos;
        hg_proc->extra_buf.size_left = hg_proc->extra_buf.size - current_pos;
        hg_proc->extra_buf.is_mine = 1;

        /* Switch buffer */
        hg_proc->current_buf = &hg_proc->extra_buf;
    } else {
        void *new_buf = NULL;

        /* Save current position */
        current_pos = (char *) hg_proc->extra_buf.buf_ptr - (char *) hg_proc->extra_buf.buf;

        /* Reallocate buffer */
        new_buf = realloc(hg_proc->extra_buf.buf, new_buf_size);
        if (!new_buf) {
            HG_LOG_ERROR("Could not reallocate buffer");
            ret = HG_NOMEM_ERROR;
            goto done;
        }
        hg_proc->extra_buf.buf = new_buf;
        hg_proc->extra_buf.size = new_buf_size;
        hg_proc->extra_buf.buf_ptr = (char *) hg_proc->extra_buf.buf + current_pos;
        hg_proc->extra_buf.size_left = hg_proc->extra_buf.size - current_pos;
    }

done:
    return ret;
}
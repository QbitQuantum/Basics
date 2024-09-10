static afs_int32
rewindFile(struct butm_tapeInfo *info)
{
    struct progress *p;
    afs_int32 code = 0;
    afs_int32 error;

    p = (struct progress *)info->tmRock;

    POLL();

    error = Rewind(p->fid);

    POLL();

    if (error) {
	info->status |= BUTM_STATUS_SEEKERROR;
	ERROR_EXIT(BUTM_IOCTL);
    }

    info->position = (isafile ? 0 : 1);
    info->kBytes = info->nBytes = 0;
    info->nFiles = info->nRecords = 0;
    p->reading = p->writing = 0;

  error_exit:
    if (error)
	info->error = error;
    return (code);
}
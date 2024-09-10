/***********************************
 * API - Close a mailbox
 * IN:
 *  mb_id - handle for the mailbox
 ***********************************/
mb_error_t
mb_close(mb_id_t mb_id)
{
    mb_handle_t* mbhdl;
    mb_hdr_t*    mbhdr;

    mbhdl = (mb_handle_t*) mb_id;
    if (MB_BAD(mbhdl)) {
        _set_errno(EINVAL);
        return (MB_ERROR);
    }
    if (lockf(mbhdl->fd, F_LOCK, 0) == -1) {
        return (MB_ERROR);
    }
    mbhdr = (mb_hdr_t*) mbhdl->maddr;
    munmap(mbhdl->maddr, mbhdr->ttSize);
    mbhdl->valid = 0;
    close(mbhdl->fd);
    free(mbhdl);

    return (MB_OK);
}
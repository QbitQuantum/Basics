static_inline void
_VUnlockFd(struct VLockFile *lf, afs_uint32 offset)
{
    OVERLAPPED lap;

    memset(&lap, 0, sizeof(lap));
    lap.Offset = offset;

    UnlockFileEx(lf->fd, 0, 1, 0, &lap);
}
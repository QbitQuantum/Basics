/*
 * Returns true iff the specified sector is present in the disk image. Drivers
 * not implementing the functionality are assumed to not support backing files,
 * hence all their sectors are reported as allocated.
 *
 * If 'sector_num' is beyond the end of the disk image the return value is 0
 * and 'pnum' is set to 0.
 *
 * 'pnum' is set to the number of sectors (including and immediately following
 * the specified sector) that are known to be in the same
 * allocated/unallocated state.
 *
 * 'nb_sectors' is the max value 'pnum' should be set to.  If nb_sectors goes
 * beyond the end of the disk image it will be clamped.
 */
static int coroutine_fn raw_co_is_allocated(BlockDriverState *bs,
                                            int64_t sector_num,
                                            int nb_sectors, int *pnum)
{
    off_t start, data, hole;
    int ret;

    ret = fd_open(bs);
    if (ret < 0) {
        return ret;
    }

    start = sector_num * BDRV_SECTOR_SIZE;

#ifdef CONFIG_FIEMAP

    BDRVRawState *s = bs->opaque;
    struct {
        struct fiemap fm;
        struct fiemap_extent fe;
    } f;

    f.fm.fm_start = start;
    f.fm.fm_length = (int64_t)nb_sectors * BDRV_SECTOR_SIZE;
    f.fm.fm_flags = 0;
    f.fm.fm_extent_count = 1;
    f.fm.fm_reserved = 0;
    if (ioctl(s->fd, FS_IOC_FIEMAP, &f) == -1) {
        /* Assume everything is allocated.  */
        *pnum = nb_sectors;
        return 1;
    }

    if (f.fm.fm_mapped_extents == 0) {
        /* No extents found, data is beyond f.fm.fm_start + f.fm.fm_length.
         * f.fm.fm_start + f.fm.fm_length must be clamped to the file size!
         */
        off_t length = lseek(s->fd, 0, SEEK_END);
        hole = f.fm.fm_start;
        data = MIN(f.fm.fm_start + f.fm.fm_length, length);
    } else {
        data = f.fe.fe_logical;
        hole = f.fe.fe_logical + f.fe.fe_length;
    }

#elif defined SEEK_HOLE && defined SEEK_DATA

    BDRVRawState *s = bs->opaque;

    hole = lseek(s->fd, start, SEEK_HOLE);
    if (hole == -1) {
        /* -ENXIO indicates that sector_num was past the end of the file.
         * There is a virtual hole there.  */
        assert(errno != -ENXIO);

        /* Most likely EINVAL.  Assume everything is allocated.  */
        *pnum = nb_sectors;
        return 1;
    }

    if (hole > start) {
        data = start;
    } else {
        /* On a hole.  We need another syscall to find its end.  */
        data = lseek(s->fd, start, SEEK_DATA);
        if (data == -1) {
            data = lseek(s->fd, 0, SEEK_END);
        }
    }
#else
    *pnum = nb_sectors;
    return 1;
#endif

    if (data <= start) {
        /* On a data extent, compute sectors to the end of the extent.  */
        *pnum = MIN(nb_sectors, (hole - start) / BDRV_SECTOR_SIZE);
        return 1;
    } else {
        /* On a hole, compute sectors to the beginning of the next extent.  */
        *pnum = MIN(nb_sectors, (data - start) / BDRV_SECTOR_SIZE);
        return 0;
    }
}
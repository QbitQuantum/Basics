static int
_sis1100_write(struct sis1100_softc* sc, struct sis1100_fdata* fd,
    size_t count, size_t* count_written, u_int32_t addr,
    const char __user *data)
{
    int32_t am;
    int datasize;
    int space, fifo;
    int res;

#if 0
    pERROR(sc, "sis1100_write data=%p addr=%08x count=%llu size=%d",
        data, addr, (unsigned long long)count, fd->vmespace_datasize);
#endif
    switch (fd->subdev) {
    case sis1100_subdev_ram:
        am=-1;
        datasize=4;
        space=6;
        fifo=0;
        break;
    case sis1100_subdev_remote:
        am=fd->vmespace_am;
        datasize=fd->vmespace_datasize;
        space=1;
        fifo=fd->fifo_mode;
        break;
    case sis1100_subdev_dsp:
        am=-1;
        datasize=4;
        space=6;
        fifo=0;
        break;
    case sis1100_subdev_ctrl:
        return sis1100_write_irq(sc, fd, count, count_written, data);
    default:
        return ENOTTY;
    }

    if (count%datasize)
        return EINVAL;

    res=sis1100_write_block(sc, fd,
        datasize, fifo, count/datasize, count_written, space, am,
        addr, data, &fd->last_prot_err);
    *count_written*=datasize;

    return res;
}
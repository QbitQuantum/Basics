int rpmcpioStrippedHeaderWrite(rpmcpio_t cpio, int fx, off_t fsize)
{
    struct cpioStrippedPhysicalHeader hdr_s;
    struct cpioStrippedPhysicalHeader * hdr = &hdr_s;
    char field[64];
    size_t written;
    int rc = 0;

    if ((cpio->mode & O_ACCMODE) != O_WRONLY) {
        return RPMERR_WRITE_FAILED;
    }

    if (cpio->fileend != cpio->offset) {
        return RPMERR_WRITE_FAILED;
    }

    rc = rpmcpioWritePad(cpio, 4);
    if (rc) {
        return rc;
    }

    SET_NUM_FIELD(hdr->fx, fx, field);

    written = Fwrite(CPIO_STRIPPED_MAGIC, 6, 1, cpio->fd);
    cpio->offset += written;
    if (written != 6) {
        return RPMERR_WRITE_FAILED;
    }

    written = Fwrite(hdr, STRIPPED_PHYS_HDR_SIZE, 1, cpio->fd);
    cpio->offset += written;
    if (written != STRIPPED_PHYS_HDR_SIZE) {
        return RPMERR_WRITE_FAILED;
    }

    rc = rpmcpioWritePad(cpio, 4);

    cpio->fileend = cpio->offset + fsize;

    return rc;
}
int headerWrite(FD_t fd, Header h, int magicp)
{
    ssize_t nb;
    unsigned int length;
    void * uh;

    uh = headerExport(h, &length);
    if (uh == NULL)
	return 1;
    switch (magicp) {
    case HEADER_MAGIC_YES:
	nb = Fwrite(rpm_header_magic, sizeof(uint8_t), sizeof(rpm_header_magic), fd);
	if (nb != sizeof(rpm_header_magic))
	    goto exit;
	break;
    case HEADER_MAGIC_NO:
	break;
    }

    nb = Fwrite(uh, sizeof(char), length, fd);

exit:
    free(uh);
    return (nb == length ? 0 : 1);
}
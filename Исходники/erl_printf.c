static int
write_f_add_cr(void *vfp, char* buf, size_t len)
{
    size_t i;
    ASSERT(vfp);
    for (i = 0; i < len; i++) {
	if (buf[i] == '\n' && PUTC('\r', (FILE *) vfp) == EOF)
	    return get_error_result();
	if (PUTC(buf[i], (FILE *) vfp) == EOF)
	    return get_error_result();
    }
    return 0;
}
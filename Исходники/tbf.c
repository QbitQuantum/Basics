static unsigned rpmbfWrite(FD_t fd, rpmbf * bfa, size_t npkgs)
{
    const char * fn = xstrdup(fdGetOPath(fd));
    struct stat sb;
    int ix;
    int xx;

    for (ix = 0; ix < (int) npkgs; ix++) {
	rpmbf bf = bfa[ix];
	static const char _bfmagic[] = "BFL3";
	const unsigned char * _bits = (bf ? bf->bits : NULL);
	uint32_t _n = (bf ? htonl(bf->n) : 0);
	uint32_t _m = (bf ? htonl(bf->m) : 0);
	uint32_t _k = (bf ? htonl(bf->k) : 0);

	if (bf && rpmIsVerbose())
	    fprintf(stderr, "\tbf[%d] %p {%u,%u}[%u] %u bytes\n", ix, bf, (unsigned)bf->n, (unsigned)bf->m, (unsigned)bf->k, (unsigned)(16 + (bf->m+7)/8));
	xx = Fwrite(_bfmagic, 1, 2, fd);
	xx = Fwrite(&_n, 1, sizeof(_n), fd);
	xx = Fwrite(&_m, 1, sizeof(_m), fd);
	xx = Fwrite(&_k, 1, sizeof(_m), fd);
	if (bf && bf->m > 0)
	    xx = Fwrite(bf->bits, 1, (bf->m+7)/8, fd);
    }
    xx = Fclose(fd);
    xx = Stat(fn, &sb);
    xx = Unlink(fn);

    return sb.st_size;
}
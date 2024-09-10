static int check(RBinArch *arch) {
	if (arch && arch->buf && arch->buf->buf)
		if (!memcmp (arch->buf->buf, RARVMHDR, 16))
			return R_TRUE;
	return R_FALSE;
}
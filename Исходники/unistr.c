/**
 * ntfs_mbstoucs - convert a multibyte string to a little endian Unicode string
 * @ins:	input multibyte string buffer
 * @outs:	on return contains the (allocated) output Unicode string
 * @outs_len:	length of output buffer in Unicode characters
 *
 * Convert the input multibyte string @ins, from the current locale into the
 * corresponding little endian, 2-byte Unicode string.
 *
 * If *@outs is NULL, the function allocates the string and the caller is
 * responsible for calling free(*@outs); when finished with it.
 *
 * On success the function returns the number of Unicode characters written to
 * the output string *@outs (>= 0), not counting the terminating Unicode NULL
 * character. If the output string buffer was allocated, *@outs is set to it.
 *
 * On error, -1 is returned, and errno is set to the error code. The following
 * error codes can be expected:
 *	EINVAL		Invalid arguments (e.g. @ins or @outs is NULL).
 *	EILSEQ		The input string cannot be represented as a Unicode
 *			string according to the current locale.
 *	ENAMETOOLONG	Destination buffer is too small for input string.
 *	ENOMEM		Not enough memory to allocate destination buffer.
 */
int ntfs_mbstoucs(const char *ins, ntfschar **outs, int outs_len)
{
	ntfschar *ucs;
	const char *s;
	wchar_t wc;
	int i, o, cnt, ins_len, ucs_len, ins_size;
#ifdef HAVE_MBSINIT
	mbstate_t mbstate;
#endif

	if (!ins || !outs) {
		errno = EINVAL;
		return -1;
	}
	ucs = *outs;
	ucs_len = outs_len;
	if (ucs && !ucs_len) {
		errno = ENAMETOOLONG;
		return -1;
	}
	/* Determine the size of the multi-byte string in bytes. */
	ins_size = strlen(ins);
	/* Determine the length of the multi-byte string. */
	s = ins;
#if defined(HAVE_MBSINIT)
	memset(&mbstate, 0, sizeof(mbstate));
	ins_len = mbsrtowcs(NULL, (const char **)&s, 0, &mbstate);
#ifdef __CYGWIN32__
	if (!ins_len && *ins) {
		/* Older Cygwin had broken mbsrtowcs() implementation. */
		ins_len = strlen(ins);
	}
#endif
#elif !defined(DJGPP)
	ins_len = mbstowcs(NULL, s, 0);
#else
	/* Eeek!!! DJGPP has broken mbstowcs() implementation!!! */
	ins_len = strlen(ins);
#endif
	if (ins_len == -1)
		return ins_len;
#ifdef HAVE_MBSINIT
	if ((s != ins) || !mbsinit(&mbstate)) {
#else
	if (s != ins) {
#endif
		errno = EILSEQ;
		return -1;
	}
	/* Add the NULL terminator. */
	ins_len++;
	if (!ucs) {
		ucs_len = ins_len;
		ucs = (ntfschar*)malloc(ucs_len * sizeof(ntfschar));
		if (!ucs)
			return -1;
	}
#ifdef HAVE_MBSINIT
	memset(&mbstate, 0, sizeof(mbstate));
#else
	mbtowc(NULL, NULL, 0);
#endif
	for (i = o = cnt = 0; i < ins_size; i += cnt, o++) {
		/* Reallocate memory if necessary or abort. */
		if (o >= ucs_len) {
			ntfschar *tc;
			if (ucs == *outs) {
				errno = ENAMETOOLONG;
				return -1;
			}
			/*
			 * We will never get here but hey, it's only a bit of
			 * extra code...
			 */
			ucs_len = (ucs_len * sizeof(ntfschar) + 64) & ~63;
			tc = (ntfschar*)realloc(ucs, ucs_len);
			if (!tc)
				goto err_out;
			ucs = tc;
			ucs_len /= sizeof(ntfschar);
		}
		/* Convert the multibyte character to a wide character. */
#ifdef HAVE_MBSINIT
		cnt = mbrtowc(&wc, ins + i, ins_size - i, &mbstate);
#else
		cnt = mbtowc(&wc, ins + i, ins_size - i);
#endif
		if (!cnt)
			break;
		if (cnt == -1)
			goto err_out;
		if (cnt < -1) {
			ntfs_log_trace("Eeek. cnt = %i\n", cnt);
			errno = EINVAL;
			goto err_out;
		}
		/* Make sure we are not overflowing the NTFS Unicode set. */
		if ((unsigned long)wc >= (unsigned long)(1 <<
				(8 * sizeof(ntfschar)))) {
			errno = EILSEQ;
			goto err_out;
		}
		/* Convert the CPU wide character to a LE Unicode character. */
		ucs[o] = cpu_to_le16(wc);
	}
#ifdef HAVE_MBSINIT
	/* Make sure we are back in the initial state. */
	if (!mbsinit(&mbstate)) {
		ntfs_log_trace("Eeek. mbstate not in initial state!\n");
		errno = EILSEQ;
		goto err_out;
	}
#endif
	/* Now write the NULL character. */
	ucs[o] = cpu_to_le16(L'\0');
	if (*outs != ucs)
		*outs = ucs;
	return o;
err_out:
	if (ucs != *outs) {
		int eo = errno;
		free(ucs);
		errno = eo;
	}
	return -1;
}

/**
 * ntfs_upcase_table_build - build the default upcase table for NTFS
 * @uc:		destination buffer where to store the built table
 * @uc_len:	size of destination buffer in bytes
 *
 * ntfs_upcase_table_build() builds the default upcase table for NTFS and
 * stores it in the caller supplied buffer @uc of size @uc_len.
 *
 * Note, @uc_len must be at least 128kiB in size or bad things will happen!
 */
void ntfs_upcase_table_build(ntfschar *uc, u32 uc_len)
{
	static int uc_run_table[][3] = { /* Start, End, Add */
	{0x0061, 0x007B,  -32}, {0x0451, 0x045D, -80}, {0x1F70, 0x1F72,  74},
	{0x00E0, 0x00F7,  -32}, {0x045E, 0x0460, -80}, {0x1F72, 0x1F76,  86},
	{0x00F8, 0x00FF,  -32}, {0x0561, 0x0587, -48}, {0x1F76, 0x1F78, 100},
	{0x0256, 0x0258, -205}, {0x1F00, 0x1F08,   8}, {0x1F78, 0x1F7A, 128},
	{0x028A, 0x028C, -217}, {0x1F10, 0x1F16,   8}, {0x1F7A, 0x1F7C, 112},
	{0x03AC, 0x03AD,  -38}, {0x1F20, 0x1F28,   8}, {0x1F7C, 0x1F7E, 126},
	{0x03AD, 0x03B0,  -37}, {0x1F30, 0x1F38,   8}, {0x1FB0, 0x1FB2,   8},
	{0x03B1, 0x03C2,  -32}, {0x1F40, 0x1F46,   8}, {0x1FD0, 0x1FD2,   8},
	{0x03C2, 0x03C3,  -31}, {0x1F51, 0x1F52,   8}, {0x1FE0, 0x1FE2,   8},
	{0x03C3, 0x03CC,  -32}, {0x1F53, 0x1F54,   8}, {0x1FE5, 0x1FE6,   7},
	{0x03CC, 0x03CD,  -64}, {0x1F55, 0x1F56,   8}, {0x2170, 0x2180, -16},
	{0x03CD, 0x03CF,  -63}, {0x1F57, 0x1F58,   8}, {0x24D0, 0x24EA, -26},
	{0x0430, 0x0450,  -32}, {0x1F60, 0x1F68,   8}, {0xFF41, 0xFF5B, -32},
	{0}
	};
	static int uc_dup_table[][2] = { /* Start, End */
	{0x0100, 0x012F}, {0x01A0, 0x01A6}, {0x03E2, 0x03EF}, {0x04CB, 0x04CC},
	{0x0132, 0x0137}, {0x01B3, 0x01B7}, {0x0460, 0x0481}, {0x04D0, 0x04EB},
	{0x0139, 0x0149}, {0x01CD, 0x01DD}, {0x0490, 0x04BF}, {0x04EE, 0x04F5},
	{0x014A, 0x0178}, {0x01DE, 0x01EF}, {0x04BF, 0x04BF}, {0x04F8, 0x04F9},
	{0x0179, 0x017E}, {0x01F4, 0x01F5}, {0x04C1, 0x04C4}, {0x1E00, 0x1E95},
	{0x018B, 0x018B}, {0x01FA, 0x0218}, {0x04C7, 0x04C8}, {0x1EA0, 0x1EF9},
	{0}
	};
	static int uc_byte_table[][2] = { /* Offset, Value */
	{0x00FF, 0x0178}, {0x01AD, 0x01AC}, {0x01F3, 0x01F1}, {0x0269, 0x0196},
	{0x0183, 0x0182}, {0x01B0, 0x01AF}, {0x0253, 0x0181}, {0x026F, 0x019C},
	{0x0185, 0x0184}, {0x01B9, 0x01B8}, {0x0254, 0x0186}, {0x0272, 0x019D},
	{0x0188, 0x0187}, {0x01BD, 0x01BC}, {0x0259, 0x018F}, {0x0275, 0x019F},
	{0x018C, 0x018B}, {0x01C6, 0x01C4}, {0x025B, 0x0190}, {0x0283, 0x01A9},
	{0x0192, 0x0191}, {0x01C9, 0x01C7}, {0x0260, 0x0193}, {0x0288, 0x01AE},
	{0x0199, 0x0198}, {0x01CC, 0x01CA}, {0x0263, 0x0194}, {0x0292, 0x01B7},
	{0x01A8, 0x01A7}, {0x01DD, 0x018E}, {0x0268, 0x0197},
	{0}
	};
	int i, r;

	memset((char*)uc, 0, uc_len);
	uc_len >>= 1;
	if (uc_len > 65536)
		uc_len = 65536;
	for (i = 0; (u32)i < uc_len; i++)
		uc[i] = i;
	for (r = 0; uc_run_table[r][0]; r++)
		for (i = uc_run_table[r][0]; i < uc_run_table[r][1]; i++)
			uc[i] += uc_run_table[r][2];
	for (r = 0; uc_dup_table[r][0]; r++)
		for (i = uc_dup_table[r][0]; i < uc_dup_table[r][1]; i += 2)
			uc[i + 1]--;
	for (r = 0; uc_byte_table[r][0]; r++)
		uc[uc_byte_table[r][0]] = uc_byte_table[r][1];
}

/**
 * ntfs_str2ucs - convert a string to a valid NTFS file name
 * @s:		input string
 * @len:	length of output buffer in Unicode characters
 *
 * Convert the input @s string into the corresponding little endian,
 * 2-byte Unicode string. The length of the converted string is less 
 * or equal to the maximum length allowed by the NTFS format (255).
 *
 * If @s is NULL then return AT_UNNAMED.
 *
 * On success the function returns the Unicode string in an allocated 
 * buffer and the caller is responsible to free it when it's not needed
 * anymore.
 *
 * On error NULL is returned and errno is set to the error code.
 */
ntfschar *ntfs_str2ucs(const char *s, int *len)
{
	ntfschar *ucs = NULL;

	if (s && ((*len = ntfs_mbstoucs(s, &ucs, 0)) == -1)) {
		ntfs_log_perror("Couldn't convert '%s' to Unicode", s);
		return NULL;
	}
	if (*len > 0xff) {
		free(ucs);
		errno = ENAMETOOLONG;
		return NULL;
	}
	if (!ucs || !*len) {
		ucs  = AT_UNNAMED;
		*len = 0;
	}
	return ucs;
}
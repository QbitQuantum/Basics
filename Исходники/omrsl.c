static void
convertWithMBTOWC(struct OMRPortLibrary *portLibrary, const char *error, char *errBuf, uintptr_t bufLen)
{
	char *out = errBuf;
	char *end = &errBuf[bufLen - 1];
	const char *walk = error;
	wchar_t ch = '\0';
	int ret = 0;

	/* reset the shift state */
	ret = mbtowc(NULL, NULL, 0);

	while ('\0' != *walk) {
		ret = mbtowc(&ch, walk, MB_CUR_MAX);
		if (ret < 0) {
			ch = *walk++;
		} else if (0 == ret) {
			break;
		} else {
			walk += ret;
		}

		if ('\r' == ch) {
			continue;
		}
		if ('\n' == ch) {
			ch = ' ';
		}
		if (ch < 0x80) {
			if ((out + 1) > end) {
				break;
			}
			*out++ = (char)ch;
		} else if (ch < 0x800) {
			if ((out + 2) > end) {
				break;
			}
			*out++ = (char)(0xc0 | ((ch >> 6) & 0x1f));
			*out++ = (char)(0x80 | (ch & 0x3f));
		} else {
			if ((out + 3) > end) {
				break;
			}
			*out++ = (char)(0xe0 | ((ch >> 12) & 0x0f));
			*out++ = (char)(0x80 | ((ch >> 6) & 0x3f));
			*out++ = (char)(0x80 | (ch & 0x3f));
		}
	}
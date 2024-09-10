/* This function returns a newly allocated wide string containing the USB
   device string numbered by the index. The returned string must be freed
   by using free(). */
static wchar_t *get_usb_string(libusb_device_handle *dev, uint8_t idx)
{
	char buf[512];
	int len;
	wchar_t *str = NULL;

#ifndef __ANDROID__ /* we don't use iconv on Android */
	wchar_t wbuf[256];
	/* iconv variables */
	iconv_t ic;
	size_t inbytes;
	size_t outbytes;
	size_t res;
#ifdef __FreeBSD__
	const char *inptr;
#else
	char *inptr;
#endif
	char *outptr;
#endif

	/* Determine which language to use. */
	uint16_t lang;
	lang = get_usb_code_for_current_locale();
	if (!is_language_supported(dev, lang))
		lang = get_first_language(dev);

	/* Get the string from libusb. */
	len = libusb_get_string_descriptor(dev,
			idx,
			lang,
			(unsigned char*)buf,
			sizeof(buf));
	if (len < 0)
		return NULL;

#ifdef __ANDROID__

	/* Bionic does not have iconv support nor wcsdup() function, so it
	   has to be done manually.  The following code will only work for
	   code points that can be represented as a single UTF-16 character,
	   and will incorrectly convert any code points which require more
	   than one UTF-16 character.

	   Skip over the first character (2-bytes).  */
	len -= 2;
	str = malloc((len / 2 + 1) * sizeof(wchar_t));
	int i;
	for (i = 0; i < len / 2; i++) {
		str[i] = buf[i * 2 + 2] | (buf[i * 2 + 3] << 8);
	}
	str[len / 2] = 0x00000000;

#else

	/* buf does not need to be explicitly NULL-terminated because
	   it is only passed into iconv() which does not need it. */

	/* Initialize iconv. */
	ic = iconv_open("WCHAR_T", "UTF-16LE");
	if (ic == (iconv_t)-1) {
		LOG("iconv_open() failed\n");
		return NULL;
	}

	/* Convert to native wchar_t (UTF-32 on glibc/BSD systems).
	   Skip the first character (2-bytes). */
	inptr = buf+2;
	inbytes = len-2;
	outptr = (char*) wbuf;
	outbytes = sizeof(wbuf);
	res = iconv(ic, &inptr, &inbytes, &outptr, &outbytes);
	if (res == (size_t)-1) {
		LOG("iconv() failed\n");
		goto err;
	}

	/* Write the terminating NULL. */
	wbuf[sizeof(wbuf)/sizeof(wbuf[0])-1] = 0x00000000;
	if (outbytes >= sizeof(wbuf[0]))
		*((wchar_t*)outptr) = 0x00000000;

	/* Allocate and copy the string. */
	str = wcsdup(wbuf);

err:
	iconv_close(ic);

#endif

	return str;
}
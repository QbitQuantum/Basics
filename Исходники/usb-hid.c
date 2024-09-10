/* This function returns a newly allocated wide string containing the USB
   device string numbered by the index. The returned string must be freed
   by using free(). */
static wchar_t *get_usb_string(libusb_device_handle *dev, uint8_t idx)
{
	char buf[512];
	int len;
	wchar_t *str = NULL;
	wchar_t wbuf[256];

	/* iconv variables */
	iconv_t ic;
	size_t inbytes;
	size_t outbytes;
	size_t res;
	char *inptr;
	char *outptr;

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
	
	buf[sizeof(buf)-1] = '\0';
	
	if (len+1 < sizeof(buf))
		buf[len+1] = '\0';
	
	/* Initialize iconv. */
	ic = iconv_open("UTF-32", "UTF-16");
	if (ic == (iconv_t)-1)
		return NULL;
	
	/* Convert to UTF-32 (wchar_t on glibc systems).
	   Skip the first character (2-bytes). */
	inptr = buf+2;
	inbytes = len-2;
	outptr = (char*) wbuf;
	outbytes = sizeof(wbuf);
	res = iconv(ic, &inptr, &inbytes, &outptr, &outbytes);
	if (res == (size_t)-1)
		goto err;

	/* Write the terminating NULL. */
	wbuf[sizeof(wbuf)/sizeof(wbuf[0])-1] = 0x00000000;
	if (outbytes >= sizeof(wbuf[0]))
		*((wchar_t*)outptr) = 0x00000000;
	
	/* Allocate and copy the string. */
	str = wcsdup(wbuf+1);

err:
	iconv_close(ic);
	
	return str;
}
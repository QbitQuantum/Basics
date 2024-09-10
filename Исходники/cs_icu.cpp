bool CSICU_charset_init(charset* cs,
						const ASCII* charSetName)
{
	UErrorCode status = U_ZERO_ERROR;
	UConverter* conv = ucnv_open(charSetName, &status);

	if (U_SUCCESS(status))
	{
		// charSetName comes from stack. Copy it.
		ASCII* p = new ASCII[strlen(charSetName) + 1];
		cs->charset_name = p;
		strcpy(p, charSetName);

		cs->charset_version = CHARSET_VERSION_1;
		cs->charset_flags |= CHARSET_ASCII_BASED;
		cs->charset_min_bytes_per_char = ucnv_getMinCharSize(conv);
		cs->charset_max_bytes_per_char = ucnv_getMaxCharSize(conv);
		cs->charset_fn_destroy = charset_destroy;
		cs->charset_fn_well_formed = NULL;

		const UChar unicodeSpace = 32;

		BYTE* p2 = new BYTE[cs->charset_max_bytes_per_char];
		cs->charset_space_character = p2;
		cs->charset_space_length = ucnv_fromUChars(conv, reinterpret_cast<char*>(p2),
			cs->charset_max_bytes_per_char, &unicodeSpace, 1, &status);
		fb_assert(U_SUCCESS(status));

		ucnv_close(conv);

		CVICU_convert_init(cs);
	}

	return U_SUCCESS(status);
}
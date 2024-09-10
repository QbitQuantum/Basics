static void _add_punycode_if_needed(UIDNA *idna, _psl_vector_t *v, _psl_entry_t *e)
{
	if (_str_is_ascii(e->label_buf))
		return;

	/* IDNA2008 UTS#46 punycode conversion */
	if (idna) {
		char lookupname[128] = "";
		UErrorCode status = 0;
		UIDNAInfo info = UIDNA_INFO_INITIALIZER;
		UChar utf16_dst[128], utf16_src[128];
		int32_t utf16_src_length;

		u_strFromUTF8(utf16_src, sizeof(utf16_src)/sizeof(utf16_src[0]), &utf16_src_length, e->label_buf, -1, &status);
		if (U_SUCCESS(status)) {
			int32_t dst_length = uidna_nameToASCII(idna, utf16_src, utf16_src_length, utf16_dst, sizeof(utf16_dst)/sizeof(utf16_dst[0]), &info, &status);
			if (U_SUCCESS(status)) {
				u_strToUTF8(lookupname, sizeof(lookupname), NULL, utf16_dst, dst_length, &status);
				if (U_SUCCESS(status)) {
					if (strcmp(e->label_buf, lookupname)) {
						_psl_entry_t suffix, *suffixp;

						/* fprintf(stderr, "libicu '%s' -> '%s'\n", e->label_buf, lookupname); */
						_suffix_init(&suffix, lookupname, strlen(lookupname));
						suffix.wildcard = e->wildcard;
						suffixp = _vector_get(v, _vector_add(v, &suffix));
						suffixp->label = suffixp->label_buf; /* set label to changed address */
					} /* else ignore */
				} /* else
					fprintf(stderr, "Failed to convert UTF-16 to UTF-8 (status %d)\n", status); */
			} /* else
				fprintf(stderr, "Failed to convert to ASCII (status %d)\n", status); */
		} /* else
			fprintf(stderr, "Failed to convert UTF-8 to UTF-16 (status %d)\n", status); */
	}
}
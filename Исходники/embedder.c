// returns 0 on success, non zero on error
int get_full_path(char* src, char* dst, size_t dst_size)
{
#if defined(_WIN32)
	DWORD r;
	char* src_copy = NULL;
#else
	char *dn, *bn;
#endif
	if ((src == NULL) || (dst == NULL) || (dst_size == 0)) {
		return 1;
	}
#if defined(_WIN32)
	if ((src_copy = malloc(strlen(src) + 1)) == NULL) return 1;
	memcpy(src_copy, src, strlen(src) + 1);
	handle_separators(src_copy);
	r = GetFullPathNameA(src_copy, (DWORD)dst_size, dst, NULL);
	safe_free(src_copy);
	if ((r != 0) || (r <= dst_size)) {
		return 0;
	}
#else
	if ( (basename_split(src, &dn, &bn) == 0)
	  && (realpath(dn, dst) != NULL)
	  && (strlen(dst) + strlen(bn) + 2 < dst_size) ) {
		strcat(dst, "/");
		strcat(dst, bn);
		basename_free(src);
		return 0;
	}
	basename_free(src);
#endif
	fprintf(stderr, "Unable to get full path for '%s'.\n", src);
	return 1;
}
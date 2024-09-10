void md_util_fn_split(CHAR *f_name, CHAR *f_ext, const CHAR *asciiz_fn) {

	CHAR* ext = "\0";
	size_t ext_len = 0;

	memset(f_name, ' ', 8);
	memset(f_ext, ' ', 3);
	if(strcmp(asciiz_fn, ".") && strcmp(asciiz_fn, ".."))	{
		ext = PathFindExtensionA(asciiz_fn);
		ext_len = strlen(ext);
	}
	memcpy(f_name, asciiz_fn, strlen(asciiz_fn) - ext_len);
	if(ext[0] != '\0')	{
		memcpy(f_ext, ext + 1, strlen(ext) - 1);
	}
}
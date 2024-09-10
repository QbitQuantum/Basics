int BLI_copy(const char *file, const char *to)
{
	int err;

	/* windows doesn't support copying to a directory
	 * it has to be 'cp filename filename' and not
	 * 'cp filename destdir' */

	BLI_strncpy(str, to, sizeof(str));
	/* points 'to' to a directory ? */
	if (BLI_last_slash(str) == (str + strlen(str) - 1)) {
		if (BLI_last_slash(file) != NULL) {
			strcat(str, BLI_last_slash(file) + 1);
		}
	}

	UTF16_ENCODE(file);
	UTF16_ENCODE(str);
	err = !CopyFileW(file_16, str_16, false);
	UTF16_UN_ENCODE(str);
	UTF16_UN_ENCODE(file);

	if (err) {
		callLocalErrorCallBack("Unable to copy file!");
		printf(" Copy from '%s' to '%s' failed\n", file, str);
	}

	return err;
}
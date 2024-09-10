void FileAccessWindows::close() {

	if (!f)
		return;

	fclose(f);
	f = NULL;

	if (save_path != "") {

		bool rename_error = true;
		int attempts = 4;
		while (rename_error && attempts) {
			// This workaround of trying multiple times is added to deal with paranoid Windows
			// antiviruses that love reading just written files even if they are not executable, thus
			// locking the file and preventing renaming from happening.

#ifdef UWP_ENABLED
			// UWP has no PathFileExists, so we check attributes instead
			DWORD fileAttr;

			fileAttr = GetFileAttributesW(save_path.c_str());
			if (INVALID_FILE_ATTRIBUTES == fileAttr) {
#else
			if (!PathFileExistsW(save_path.c_str())) {
#endif
				//creating new file
				rename_error = _wrename((save_path + ".tmp").c_str(), save_path.c_str()) != 0;
			} else {
				//atomic replace for existing file
				rename_error = !ReplaceFileW(save_path.c_str(), (save_path + ".tmp").c_str(), NULL, 2 | 4, NULL, NULL);
			}
			if (rename_error) {
				attempts--;
				OS::get_singleton()->delay_usec(100000); // wait 100msec and try again
			}
		}

		if (rename_error) {
			if (close_fail_notify) {
				close_fail_notify(save_path);
			}

			ERR_EXPLAIN("Safe save failed. This may be a permissions problem, but also may happen because you are running a paranoid antivirus. If this is the case, please switch to Windows Defender or disable the 'safe save' option in editor settings. This makes it work, but increases the risk of file corruption in a crash.");
		}

		save_path = "";

		ERR_FAIL_COND(rename_error);
	}
}

String FileAccessWindows::get_path() const {

	return path_src;
}

String FileAccessWindows::get_path_absolute() const {

	return path;
}

bool FileAccessWindows::is_open() const {

	return (f != NULL);
}
void FileAccessWindows::seek(size_t p_position) {

	ERR_FAIL_COND(!f);
	last_error = OK;
	if (fseek(f, p_position, SEEK_SET))
		check_errors();
}
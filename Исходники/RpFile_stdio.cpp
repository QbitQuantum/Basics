/**
 * Common initialization function for RpFile's constructors.
 * Filename must be set in m_filename.
 */
void RpFile::init(void)
{
	const mode_str_t *mode_str = mode_to_str(m_mode);
	if (!mode_str) {
		m_lastError = EINVAL;
		return;
	}

	// TODO: On Windows, prepend "\\\\?\\" for super-long filenames?

#if defined(_WIN32)
	// Windows: Use RP2W_s() to convert the filename to wchar_t.

	// If this is an absolute path, make sure it starts with
	// "\\?\" in order to support filenames longer than MAX_PATH.
	wstring filenameW;
	if (m_filename.size() > 3 &&
	    isascii(m_filename[0]) && isalpha(m_filename[0]) &&
	    m_filename[1] == ':' && m_filename[2] == '\\')
	{
		// Absolute path. Prepend "\\?\" to the path.
		filenameW = L"\\\\?\\";
		filenameW += RP2W_s(m_filename);
	} else {
		// Not an absolute path, or "\\?\" is already
		// prepended. Use it as-is.
		filenameW = RP2W_s(m_filename);
	}

	m_file.reset(_wfopen(filenameW.c_str(), mode_str), myFile_deleter());
#else /* !_WIN32 */
	// Linux: Use UTF-8 filenames directly.
	m_file.reset(fopen(m_filename.c_str(), mode_str), myFile_deleter());
#endif /* _WIN32 */

	if (!m_file) {
		// An error occurred while opening the file.
		m_lastError = errno;
	}
}
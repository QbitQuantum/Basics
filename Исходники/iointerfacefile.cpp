/*! \brief Create an empty file
	\param filename The desired (path+)name of the file
	\returns XRV_OK if the file was created successfully
*/
XsResultValue IoInterfaceFile::create(const XsString& filename)
{
	if (m_handle) return m_lastResult = XRV_ALREADYOPEN;

//! \test does this work for non-existing files? Or do we need a check and
//! create?
#ifdef _WIN32
	m_handle = _wfopen(
		filename.toStdWString().c_str(), L"w+b");  // open for update (r/w)
#else
	m_handle = fopen(filename.c_str(), "w+b");  // open for update (r/w)
#endif
	if (m_handle == nullptr) return m_lastResult = XRV_OUTPUTCANNOTBEOPENED;

	bool fail = false;
#ifdef _WIN32
	wchar_t fullpath[XS_MAX_FILENAME_LENGTH];
	if (_wfullpath(
			fullpath, filename.toStdWString().c_str(),
			XS_MAX_FILENAME_LENGTH) == nullptr)
		fail = true;
#else
	// based on the assumption that this doesn't concern the serial port, handle
	// it the same way using realpath(). Apparently realpath() doesn't require a
	// maximum length. One would possibly want to write a wrapper for it.
	char fullpath[XS_MAX_FILENAME_LENGTH * 2];
	if (realpath(filename.c_str(), fullpath) == nullptr) fail = true;
#endif
	m_filename = XsString(fullpath);

	if (fail)
	{
		fclose(m_handle);
#ifdef _WIN32
		_wunlink(m_filename.toStdWString().c_str());
#else
		unlink(m_filename.c_str());
#endif
		m_handle = 0;
		return m_lastResult = XRV_INVALIDPARAM;
	}

	m_readPos = 0;
	m_writePos = 0;
	m_fileSize = 0;
	m_reading = true;
	m_readOnly = false;
	return m_lastResult = XRV_OK;
}
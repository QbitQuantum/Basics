/*!	\relates XsFile
	\brief Reopens a file
	\param filename Name of the file to open after the current one has been close
	\param mode Mode to reopen the file with
	\returns 0 if a file is open, another value otherwise
*/
XsResultValue XsFile_reopen(struct XsFile *thisPtr, const struct XsString* filename, const struct XsString* mode)
{
#ifdef _WIN32
	wchar_t filenameW[XS_MAX_FILENAME_LENGTH];
	wchar_t modeW[16];

	(void)XsString_copyToWCharArray(filename, filenameW, XS_MAX_FILENAME_LENGTH);
	(void)XsString_copyToWCharArray(mode, modeW, 16);

	thisPtr->m_handle = _wfreopen(filenameW, modeW, thisPtr->m_handle);
#else
	thisPtr->m_handle = freopen(filename->m_data, mode->m_data, thisPtr->m_handle);
#endif

	if (thisPtr->m_handle == NULL)
		return XRV_OUTPUTCANNOTBEOPENED;
	else
		return XRV_OK;
}
/*----------------------------------------------------------------------------------------------
	Get the status of an open IStream (file).
	If the caller uses the value STATFLAG_DEFAULT for grfStatFlag then the user must free
	the memory which this method allocates for the file name at pstatstg->pwcsName.
----------------------------------------------------------------------------------------------*/
STDMETHODIMP FileStream::Stat(STATSTG * pstatstg, DWORD grfStatFlag)
{
	BEGIN_COM_METHOD;
	ChkComArgPtr(pstatstg);

#if WIN32
		if (m_hfile == NULL)
		ThrowHr(WarnHr(E_UNEXPECTED));

	BY_HANDLE_FILE_INFORMATION bhfi;

	if (!GetFileInformationByHandle(m_hfile, &bhfi))
	{
		// The caller does not have sufficient permissions for accessing statistics for this
		// stream object.
		ThrowHr(WarnHr(STG_E_ACCESSDENIED));
	}
#else
	if (m_file < 0)
		ThrowHr(WarnHr(E_UNEXPECTED));

	struct stat filestats;

	//errno = 0;
	if (fstat(m_file, &filestats)) {
		//int err = errno;
		//std::cerr << "Error number " << err << " - " << strerror(err) << '\n';
		ThrowHr(WarnHr(STG_E_ACCESSDENIED));
	}
#endif

	pstatstg->pwcsName = NULL;

	switch (grfStatFlag)
	{
		case STATFLAG_DEFAULT:
		{
			// Requests that the statistics include the pwcsName member of the STATSTG structure.
			StrUniBufPath stubpName = m_staPath.Chars();

			pstatstg->pwcsName = (wchar *)CoTaskMemAlloc(
				(stubpName.Length() + 1) * isizeof(wchar));
			if (NULL == pstatstg->pwcsName)
				ThrowHr(WarnHr(STG_E_INSUFFICIENTMEMORY));

			memcpy(pstatstg->pwcsName, stubpName.Chars(), stubpName.Length() * isizeof(wchar));
			pstatstg->pwcsName[stubpName.Length()] = 0;
		}
		// Fall Through.

		case STATFLAG_NONAME:
			// Requests that the statistics not include the pwcsName member of the STATSTG
			// structure. If the name is omitted, there is no need for the Stat methods to allocate
			// and free memory for the string value for the name and the method can save an Alloc
			// and the caller a Free operation.
			pstatstg->type = STGTY_STREAM;
#if WIN32
			pstatstg->cbSize.HighPart = bhfi.nFileSizeHigh;
			pstatstg->cbSize.LowPart = bhfi.nFileSizeLow;
			pstatstg->mtime = bhfi.ftLastWriteTime;
			pstatstg->ctime = bhfi.ftCreationTime;
			pstatstg->atime = bhfi.ftLastAccessTime;
#else
			pstatstg->cbSize.QuadPart = filestats.st_size;
			time_tToFiletime(filestats.st_mtime, &(pstatstg->mtime));
			time_tToFiletime(filestats.st_ctime, &(pstatstg->ctime));
			time_tToFiletime(filestats.st_atime, &(pstatstg->atime));
#endif
			pstatstg->grfMode = m_grfstgm;
			pstatstg->grfLocksSupported = 0;
			pstatstg->clsid = CLSID_NULL;
			pstatstg->grfStateBits = 0;
			return S_OK;

	default:
		ThrowHr(WarnHr(STG_E_INVALIDFLAG));

	}
	END_COM_METHOD(g_fact, IID_IStream);
}
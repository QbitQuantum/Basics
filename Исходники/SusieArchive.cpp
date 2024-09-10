//---------------------------------------------------------------------------
tTJSBinaryStream * tTVPSusieArchivePlugin::CreateStream(std::wstring localname,
	unsigned long pos, unsigned long size)
{
	HLOCAL memhandle = NULL;
	int errorcode = 0xff & GetFile(const_cast<LPSTR>(ttstr(localname).AsNarrowStdString().c_str()), pos, (LPSTR)(void*)&memhandle,
		0x0100, (FARPROC)ProgressCallback, 0);
	if(errorcode || memhandle == NULL)
	{
		TVPThrowExceptionMessage(TVPSusiePluginError,
			ttstr(TJS_W("tTVPSusieArchivePlugin::GetFile failed, errorcode = ")) +
			ttstr((tjs_int)errorcode));
	}

	tTVPMemoryStream *memstream = new tTVPMemoryStream;
	void *memblock = NULL;

	try
	{
		memblock = LocalLock(memhandle);
		if(memblock == NULL)
		{
			TVPThrowExceptionMessage(TVPSusiePluginError,
				ttstr(TJS_W("tTVPSusieArchivePlugin::GetFile failed : invalid memory block.")));
		}

		// write to on-memory stream
		memstream->WriteBuffer(memblock, size);
		memstream->SetPosition(0);
	}
	catch(...)
	{
		if(memblock) LocalUnlock(memhandle);
		LocalFree(memhandle);
		delete memstream;
		throw;
	}

	if(memblock) LocalUnlock(memhandle);
	LocalFree(memhandle);
	return memstream;
}
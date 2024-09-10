TRY_CATCH
	/// Check up pointers
	if(!var.get() || (NULL == size))
		MCException(_T("Invalid pointer."));

	/// Init local variables
	SPCharBuf buf;
	IStream* stream;
	HRESULT result = S_OK;
	ULARGE_INTEGER count;
	LARGE_INTEGER pos;
	pos.QuadPart = 0;
	ULONG read;

	/// Create stream in the memory
	result = CreateStreamOnHGlobal(NULL, TRUE, &stream);
	if(S_OK != result)
		throw MCException(Format(_T("Failed to CreateStreamOnHGlobal (%X)."), result));

	/// Write variant to stream
	result = var->WriteToStream(stream);
	if(S_OK != result)
		throw MCException(Format(_T("Failed to WriteToStream (%X)."), result));

	/// Calculate size of data
	result = stream->Seek(pos, STREAM_SEEK_END, &count);
	if(S_OK != result)
		throw MCException(Format(_T("Failed to IStream->Seek (%X)."), result));

	/// Check up size
	if(count.HighPart > 0)
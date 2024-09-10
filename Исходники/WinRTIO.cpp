long long WRT_ftelli64(WRT_FILE * _File)
{
	if (!_File || _File->sig != _SIGNATURE) return _ftelli64((FILE*)_File);

	CriticalSection cs(_File->cs);
	unsigned long long pos;
	return SUCCEEDED(_File->stream->Seek(liZero, STREAM_SEEK_CUR, (PULARGE_INTEGER)&pos)) ? pos : -1;
}
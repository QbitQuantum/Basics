size_t vorbis_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	IFS* FS = (IFS*)datasource;
	size_t ActualSize = size * nmemb;

	size_t MaxReadSize = (size_t)(FS->GetFileSize() - FS->GetOffset());
	if(ActualSize > MaxReadSize)
	{
		nmemb = MaxReadSize / size;
		ActualSize = size * nmemb;
	}

	if(FS->GetData(ptr, ActualSize) == ActualSize)
		return nmemb;

	return 0;
}
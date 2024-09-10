TsStreamFileSource*
TsStreamFileSource::createNew(UsageEnvironment& env, wchar_t const* fileName,
							  unsigned preferredFrameSize,
							  unsigned playTimePerFrame, 
							  int channelType) 
{
	LogDebug(L"ts:open %s", fileName);  
	FileReader* reader;
	if (wcsstr(fileName, L".tsbuffer")!=NULL)
	{
      //MultiFileReader::MultiFileReader(BOOL useFileNext, BOOL useDummyWrites, CCritSec* pFilterLock, BOOL useRandomAccess, BOOL extraLogging):
    reader = new MultiFileReader(FALSE, FALSE, NULL, TRUE, FALSE);
    reader->SetTimeshift(true);
	}
	else
	{
		reader = new FileReader();
    reader->SetTimeshift(false);
	}
	reader->SetFileName(fileName);
	reader->OpenFile();


	Boolean deleteFidOnClose = true;
	TsStreamFileSource* newSource = new TsStreamFileSource(env, (FILE*)reader, deleteFidOnClose, preferredFrameSize, playTimePerFrame, channelType);
  __int64 fileSize = reader->GetFileSize();
	if (fileSize < 0) fileSize = 0;  
	newSource->fFileSize = fileSize;
	LogDebug("ts:size %I64d", fileSize);  
	return newSource;
}
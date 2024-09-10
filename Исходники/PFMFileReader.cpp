EStatusCode PFMFileReader::Read(const string& inPFMFilePath)
{
	EStatusCode status = PDFHummus::eSuccess;
	mInternalReadStatus = PDFHummus::eSuccess;
	InputFile pfmFile;

	status = pfmFile.OpenFile(inPFMFilePath);
	if(status != PDFHummus::eSuccess)
	{
		TRACE_LOG1("PFMFileReader::Read, unable to open PFM file in %s",inPFMFilePath.c_str());
		return status;
	}

	do
	{
		mReaderStream = pfmFile.GetInputStream();

		status = ReadHeader();
		if(status != PDFHummus::eSuccess)
			break;

		status = ReadExtension();
		if(status != PDFHummus::eSuccess)
			break;

		status = ReadExtendedFontMetrics();
		if(status != PDFHummus::eSuccess)
			break;
		
	}while(false);

	pfmFile.CloseFile();
	return status;
}
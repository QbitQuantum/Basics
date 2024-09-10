EStatusCode OpenTypeFileInput::ReadOpenTypeFile(const std::string& inFontFilePath, unsigned short inFaceIndex)
{
	InputFile fontFile;

	EStatusCode status = fontFile.OpenFile(inFontFilePath);
	if(status != PDFHummus::eSuccess)
	{
		TRACE_LOG1("OpenTypeFileInput::ReadOpenTypeFile, cannot open true type font file at %s",inFontFilePath.c_str());
		return status;
	}

	status = ReadOpenTypeFile(fontFile.GetInputStream(), inFaceIndex);
	fontFile.CloseFile();
	return status;
}
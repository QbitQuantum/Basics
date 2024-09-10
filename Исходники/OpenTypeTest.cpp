EStatusCode OpenTypeTest::SaveCharstringCode(unsigned short inFontIndex,unsigned short inGlyphIndex,CFFFileInput* inCFFFileInput)
{
	OutputFile glyphFile;

	EStatusCode status = glyphFile.OpenFile(string("C:\\PDFLibTests\\glyphCFF")  + Long(inFontIndex).ToString() + "_" + inCFFFileInput->GetGlyphName(0,inGlyphIndex) + ".txt");

	do
	{
		if(status != PDFHummus::eSuccess)
			break;
		
		CharStringType2Tracer tracer;

		status = tracer.TraceGlyphProgram(inFontIndex,inGlyphIndex,inCFFFileInput,glyphFile.GetOutputStream());

	}while(false);

	glyphFile.CloseFile();

	return status;
}
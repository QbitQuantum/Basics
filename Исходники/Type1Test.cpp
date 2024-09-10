EStatusCode Type1Test::SaveCharstringCode(const TestConfiguration& inTestConfiguration,const string& inCharStringName,Type1Input* inType1Input)
{
	OutputFile glyphFile;

    
	EStatusCode status = glyphFile.OpenFile(
                                            RelativeURLToLocalPath(inTestConfiguration.mSampleFileBase,string("glyphType1_") + inCharStringName + "_.txt"));

	do
	{
		if(status != PDFHummus::eSuccess)
			break;
		
		CharStringType1Tracer tracer;

		status = tracer.TraceGlyphProgram(inCharStringName,inType1Input,glyphFile.GetOutputStream());

	}while(false);

	glyphFile.CloseFile();

	return status;

}
EStatusCode parsePDF() 
{
	PDFParser parser;
	InputFile pdfFile;

	EStatusCode status = pdfFile.OpenFile(scBasePath + "XObjectContent.PDF");
	if(status != eSuccess) 
		return status;

	status = parser.StartPDFParsing(pdfFile.GetInputStream());
	if(status != eSuccess) 
		return status;

	showPDFinfo(parser); // Just wcout some info (no iteration)

	showPagesInfo(parser,pdfFile,status);

	return status;
}
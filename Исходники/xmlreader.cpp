Node *
ReadFile
(
   const char * fileName
)
{
   IStream * pStream;
   IXmlReader * pReader;

   HANDLE fileHandle = CreateFile(fileName, FILE_GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
   if (fileHandle == INVALID_HANDLE_VALUE)
   {
      Fatal("Cannot open XML file %s", fileName);
   }

   if (FAILED(CreateStreamOnHandle(fileHandle, &pStream)))
   {
      Fatal("Cannot create stream from file");
   }

   if (FAILED(CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, nullptr)))
   {
      Fatal("Cannot create XML reader");
   }

   if (FAILED(pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
   {
      Fatal("Cannot prohibit DTD processing");
   }

   if (FAILED(pReader->SetInput(pStream)))
   {
      Fatal("Cannot set XML reader input");
   }

   Node * topNode;
   if (FAILED(ParseXml(pReader, &topNode)))
   {
      unsigned int line, linePos;
      pReader->GetLineNumber(&line);
      pReader->GetLinePosition(&linePos);
      fprintf(
         stderr,
         "Error on line %d, position %d in \"%s\".\n",
         line,
         linePos,
         fileName);
      Fatal("Error parsing XML");
   }

   SAFERELEASE(pReader);
   SAFERELEASE(pStream);
   CloseHandle(fileHandle);

   return topNode;
}
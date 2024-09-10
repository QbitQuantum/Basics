bool Utils::xmlopen(IStream **pFileStream, IXmlReader **pReader,WCHAR* filename) {
	HRESULT hr;

	if (FAILED(hr = SHCreateStreamOnFile(filename, STGM_READ, &(*pFileStream)))) {
      wprintf(L"Error creating file reader, error is %08.8lx", hr);
      return false;
   }

   if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) pReader, NULL))) {
      wprintf(L"Error creating xml reader, error is %08.8lx", hr);
      return false;
   }

   if (FAILED(hr = (*pReader)->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit))) {
      wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
      return false;
   }

   if (FAILED(hr = (*pReader)->SetInput(*pFileStream))) {
      wprintf(L"Error setting input for reader, error is %08.8lx", hr);
      return false;
   }
   return true;
}
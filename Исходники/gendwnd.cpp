void OpGenericDownload::OnDownloadSuccess()
{
	// get a pointer to the OpParam so that I can retrieve some useful information
	GenericDownloadParam* pGenericParam = (GenericDownloadParam*) pParam;

	String_256 GenericFile = (pGenericParam->file).GetFileName();
	if (IsUserName("Olivier"))
		TRACE1("OpGenericDownload::OnDownloadSuccess(), file = %s\n", (TCHAR*)GenericFile);

	Filter* pFilter = pGenericParam->m_pFilter;
	PathName Path = pGenericParam->file;
	String_256 URL = pGenericParam->strURL;
	SelOperation* Op = pGenericParam->m_Op;

	// call the DoImport function from OpMenuImport class
	((OpMenuImport*)Op)->DoImport(Path, pFilter, &URL);

	// remove the temporary file
	remove((TCHAR*) (String_256) Path.GetPath());
}
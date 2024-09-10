BOOL OpBevel::ImportURL(WebAddress urlToGet)
{
	//First, set up some variables. We must do this now because I'm 
	//going to use a goto in a moment
	GenericDownloadParam* Param;
	OpDescriptor* pOpDesc;
	PathName pthTemp;

	//We want to import urlToGet using the best available filter

	//To get the best available filter, we simply download to the "All" filter
	//So get a pointer to the All filter
	Filter* pAllFilter=GetAllFilter();

	//Check we found it
	if (pAllFilter==NULL)
		goto ReturnError;

	//Now, get ready to download the file. This is rather complex.

	//First create a new set of download parameters
	//This object will be deleted when the download finishes
	Param = new GenericDownloadParam;
	
	//Now find the generic download OpDescriptor
	pOpDesc = OpDescriptor::FindOpDescriptor(OPTOKEN_OPGENERICDOWNLOAD);

	//And check we found it
	if (pOpDesc==NULL)
		goto ReturnError;
  
	//Now, create a temporary file to download to
	pthTemp=FileUtil::GetTemporaryPathName();

	//And now fill in our parameters
	Param->type = TYPE_HTML;
	Param->priority = AsynchDownload::PRIORITY_NORMAL;
	Param->strDescription = String_256(_R(IDS_HTMLIMPORT_FILEDOWNLOAD));
	Param->file = pthTemp.GetPath();

	Param->strURL = urlToGet.GetWebAddress();
				
	Param->Output = NULL;

	Param->m_pFilter = pAllFilter;
	Param->m_Op = this;						
	Param->pDoc = Document::GetCurrent();

	//And, finally, start the download going, if we've got a URL to download
	if (!Param->strURL.IsEmpty())
		pOpDesc->Invoke((OpParam*) Param);
	
	//And return TRUE
	return TRUE;

ReturnError:
	if (Param)
		delete Param;

	return FALSE;
}
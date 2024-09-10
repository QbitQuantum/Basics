BOOL CFemmplotDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// clear out any old metafile;
	DeleteEnhMetaFile(hMetaPlot);
	HasBoundingBox=FALSE;
	HENHMETAFILE hMetaPlotFile = GetEnhMetaFile(lpszPathName);
	if (hMetaPlotFile!=NULL){
		DWORD len =(DWORD) GetEnhMetaFileBits(hMetaPlotFile,NULL,NULL);
		unsigned char *buff=(unsigned char *) malloc(len);
		if(GetEnhMetaFileBits(hMetaPlotFile,len,buff)==0)
			MsgBox("MetaFile not copied");
		hMetaPlot=SetEnhMetaFileBits(len,buff);
	}
	else MsgBox("Problem opening specified file");

	DeleteEnhMetaFile(hMetaPlotFile);

	// TODO: Add your specialized creation code here
	
	return TRUE;
}
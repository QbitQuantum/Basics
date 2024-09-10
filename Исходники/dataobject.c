/**************************************************************************
*  IDataObject_Constructor
*/
LPDATAOBJECT IDataObject_Constructor(HWND hwndOwner, LPITEMIDLIST pMyPidl, LPITEMIDLIST * apidl, UINT cidl)
{
	IDataObjectImpl* dto;

	dto = (IDataObjectImpl*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDataObjectImpl));

	if (dto)
	{
	  dto->ref = 1;
	  ICOM_VTBL(dto) = &dtovt;
	  dto->pidl = ILClone(pMyPidl);
	  dto->apidl = _ILCopyaPidl(apidl, cidl);
	  dto->cidl = cidl;

	  dto->cfShellIDList = RegisterClipboardFormatA(CFSTR_SHELLIDLIST);
	  dto->cfFileName = RegisterClipboardFormatA(CFSTR_FILENAMEA);
	  InitFormatEtc(dto->pFormatEtc[0], dto->cfShellIDList, TYMED_HGLOBAL);
	  InitFormatEtc(dto->pFormatEtc[1], CF_HDROP, TYMED_HGLOBAL);
	  InitFormatEtc(dto->pFormatEtc[2], dto->cfFileName, TYMED_HGLOBAL);

	  shell32_ObjCount++;
	}

	TRACE("(%p)->(apidl=%p cidl=%u)\n",dto, apidl, cidl);
	return (LPDATAOBJECT)dto;
}
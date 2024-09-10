//IDropTarget methods
STDMETHODIMP CDropTarget::DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
#ifdef _DEBUG
	printf("IDropTarget::DragEnter\n");
#endif //_DEBUG
	pDataObj = pDataObject;
	pDataObject->AddRef();
	hdrop_present = false;
	if (hexwnd.prefer_CF_HDROP)
	{
		FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, 0xffffffff };
		STGMEDIUM stm;
		if (S_OK == pDataObject->QueryGetData(&fe))
		{
			hdrop_present = true;
			*pdwEffect = DROPEFFECT_COPY;
			return S_OK;
		}
		else if (S_OK == pDataObject->GetData(&fe, &stm))
		{
			hdrop_present = true;
			ReleaseStgMedium(&stm);
			*pdwEffect = DROPEFFECT_COPY;
			return S_OK;
		}
	}

	hexwnd.pwnd->CreateCaret((HBITMAP)1, 2, hexwnd.cyChar);

	return DragOver(grfKeyState, pt, pdwEffect);
}
static BOOL
PxImageView_OpenFileDialog(PxImageViewObject* self)
{
	OPENFILENAME ofn;
	wchar_t szFilter[] = L"Bitmap (*.BMP)\0*.bmp\0";
	wchar_t szOpenFileNamePath[MAX_PATH];

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g.hWin;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = szOpenFileNamePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL; //L"Select File"
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; //OFN_HIDEREADONLY | OFN_CREATEPROMPT ;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = L"bmp";
	ofn.lCustData = 0L;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	OutputDebugString(L"PxImageView_OpenFileDialog\n");
	if (GetOpenFileNameW(&ofn)) {
		OutputDebugString(L"iv4!\n");
		LPCSTR sOpenFileNamePath = toU8(szOpenFileNamePath);
		MessageBoxA(NULL, sOpenFileNamePath, "jj", NULL);
		PyObject* pyArgs = Py_BuildValue("s", sOpenFileNamePath);
		PyObject* pyImage;
		PxASSIGN(pyImage = PyObject_CallObject((PyObject*)&PxImageType, pyArgs));
		XX(pyImage);
		Py_DECREF(pyArgs);
		PyMem_RawFree(sOpenFileNamePath);
		PxImageView_SetData(self, pyImage);
		Py_DECREF(pyImage);
	}
	return TRUE;
}
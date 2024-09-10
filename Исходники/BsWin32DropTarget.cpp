	/**	Gets a file list from data. Caller must ensure that the data actually contains a file list. */
	Vector<Path>* Win32DropTarget::getFileListFromData(IDataObject* data)
	{
		FORMATETC fmtetc = { CF_HDROP, 0, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
		STGMEDIUM stgmed;

		Vector<Path>* files = bs_new<Vector<Path>>();
		if(data->GetData(&fmtetc, &stgmed) == S_OK)
		{
			PVOID data = GlobalLock(stgmed.hGlobal);

			HDROP hDrop = (HDROP)data;
			UINT numFiles = DragQueryFileW(hDrop, 0xFFFFFFFF, nullptr, 0);

			files->resize(numFiles);
			for(UINT i = 0; i < numFiles; i++)
			{
				UINT numChars = DragQueryFileW(hDrop, i, nullptr, 0) + 1;
				wchar_t* buffer = (wchar_t*)bs_alloc((UINT32)numChars * sizeof(wchar_t));

				DragQueryFileW(hDrop, i, buffer, numChars);

				(*files)[i] = UTF8::fromWide(WString(buffer));

				bs_free(buffer);
			}

			GlobalUnlock(stgmed.hGlobal);
			ReleaseStgMedium(&stgmed);
		}

		return files;
	}
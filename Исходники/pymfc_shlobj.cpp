	static PyObject *getSubItems(TypeInstance *obj, PyObject *args, PyObject *kwds) {
		PyMFC_PROLOGUE("PyMFCPIDL::getSubItems");

//todo: release GIL.

		BOOL folder=1, nonfolder=0, hidden=0;
		PyDTObject wnd;
		static char *kwlist[] = {"folder", "nonfolder", "hidden", "wnd", NULL};


		if (!PyArg_ParseTupleAndKeywords(args, kwds, 
				"|iiiO", kwlist, &folder, &nonfolder, &hidden, wnd.getBuf()))
			return NULL;
		DWORD attr = getAttribute(obj, SFGAO_FILESYSANCESTOR|SFGAO_HASSUBFOLDER);
		if (!(attr)) {
			// No sub folder
			return PyDTTuple(0).detach();
		}

		int f = 0;
		f |= folder ? SHCONTF_FOLDERS:0;
		f |= nonfolder ? SHCONTF_NONFOLDERS:0;
		f |= hidden ? SHCONTF_INCLUDEHIDDEN:0;

		CComPtr<IShellFolder> ifolder;
		if (!obj->pidl->mkid.cb) {
			// Desktop folder
			ifolder = m_desktopFolder;
		}
		else{
			HRESULT err = m_desktopFolder->BindToObject(
					obj->pidl, NULL, IID_IShellFolder, (void**)&ifolder);
			if (err == E_NOTIMPL) {
				// This object doesn't support IShellFolder.
				return PyDTTuple(0).detach();
			}
			if (FAILED(err)) {
				throw PyMFC_WIN32ERRCODE(err);
			}
		}

		HWND hWnd = NULL;
		if (!wnd.isNull()) {
			hWnd = (HWND)PyMFCHandle::asHandle(wnd.callMethod("getHwnd", "").get());
		}

		std::vector<ITEMIDLIST *> ids;
		{
			PyMFCLeavePython clp;

			CComPtr<IEnumIDList> ienum;
			HRESULT err = ifolder->EnumObjects(hWnd, f, &ienum);
			if (FAILED(err)) {
				throw PyMFC_WIN32ERRCODE(err);
			}
			
			ITEMIDLIST *child;
			while (true) {
				err = ienum->Next(1, &child, NULL);
				if (err == S_FALSE) {
					break;
				}
				if (FAILED(err)) {
					throw PyMFC_WIN32ERRCODE(err);
				}
				
				ITEMIDLIST *absid = pidl_concat(m_malloc, obj->pidl, child);
				ids.push_back(absid);

				m_malloc->Free(child);
			}
		}

		PyDTTuple ret(ids.size());
		int i = 0;
		for (std::vector<ITEMIDLIST *>::iterator iter = ids.begin(); iter != ids.end(); iter++, i++) {
			PyDTObject o((PyObject *)newInstance(*iter), true); // newInstance() steals ITEMIDLIST.
			ret.setItem(i, o);
		}
		return ret.detach();
		
		PyMFC_EPILOGUE(NULL);
	}
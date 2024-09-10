rt_private DWORD WINAPI c_browse_for_folder (LPVOID param)
	/* Main routine of thread that will create BrowseForFolder dialog. */
{
	LPITEMIDLIST id_list;
	struct EIF_BROWSE *browse = (struct EIF_BROWSE *) param;
	HRESULT hr;
	LPMALLOC imalloc;

		/* First initialize COM with single threaded appartment. */
	hr = CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);

	id_list = SHBrowseForFolder (browse->info);

	if (id_list) {
		if (SHGetPathFromIDList (id_list, browse->name)) {
			hr = SHGetMalloc (&imalloc);
			if (hr == NOERROR) {
				imalloc->lpVtbl->Free (imalloc, id_list);
			}
		}
	} else {
		browse->cancelled = 1;
	}

		/* No need for COM anymore */
	CoUninitialize();
	ExitThread(0);

	return 0;
}
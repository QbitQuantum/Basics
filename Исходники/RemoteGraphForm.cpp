void CRemoteGraphForm::OnRefreshClick()
{
	// let's load objects from ROT
	CComPtr<IRunningObjectTable>	rot;
	HRESULT							hr;

	graphs.RemoveAll();
	list_graphs.ResetContent();
	sel_graph = NULL;

	hr = GetRunningObjectTable(0, &rot);
	if (FAILED(hr)) return ;

	// scan through running objects
	CComPtr<IEnumMoniker>			emon;
	CComPtr<IMoniker>				moniker;
	CComPtr<IBindCtx>				bindctx;
	ULONG							f;

	hr = CreateBindCtx(0, &bindctx);
	if (FAILED(hr)) {
		rot = NULL;
		return ;
	}


	rot->EnumRunning(&emon);
	emon->Reset();
	while (emon->Next(1, &moniker, &f) == NOERROR) {
		
		// is this a graph object ?
		LPOLESTR	displayname;
		moniker->GetDisplayName(bindctx, NULL, &displayname);

		CString		name(displayname);
		if (name.Find(_T("!FilterGraph")) == 0) {
			RemoteGraph	gr;
			gr.name = name;
			gr.moniker = moniker;
			gr.moniker->AddRef();

			list_graphs.AddString(name);
			graphs.Add(gr);

			if (graphs.GetCount() == 1) {
				list_graphs.SetCurSel(0);
				OnLbnSelchangeListGraphs();
			}
		}

		if (displayname) {
			CComPtr<IMalloc>	alloc;
			if (SUCCEEDED(CoGetMalloc(0, &alloc))) {
				alloc->Free(displayname);
			}
			alloc = NULL;
		}
		moniker = NULL;
	}
	emon = NULL;
	bindctx = NULL;

	rot = NULL;
}
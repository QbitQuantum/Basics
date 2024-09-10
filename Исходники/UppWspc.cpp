void WorkspaceWork::ScanWorkspace() {
	Workspace wspc;
	if(main.GetCount())
		wspc.Scan(main);
	actualpackage.Clear();
	actualfileindex = -1;
	filelist.Clear();
	package.Clear();
	Vector<String> pks;
	speed.Clear();
	for(int i = 0; i < wspc.package.GetCount(); i++) {
		pks.Add(wspc.package.GetKey(i));
		speed.Add(wspc.GetPackage(i).optimize_speed);
	}
	if(sort && wspc.GetCount()) {
		PackageOrder po;
		po.mainpath = PackagePath(pks[0]);
		IndexSort(pks.Begin() + 1, pks.End(), speed.Begin() + 1, po);
	}
	for(int i = 0; i < wspc.package.GetCount(); i++) {
		String pk = pks[i];
		Font fnt = ListFont();
		if(i == 0)
			fnt.Bold();
		PackageInfo pi = GetPackageInfo(pk);
		if(pi.bold)
			fnt.Bold();
		if(pi.italic)
			fnt.Italic();
		package.Add(pk, Null, fnt, Nvl(pi.ink, SColorText()), false, 0, Null, SColorMark);
	}
	if(!organizer) {
		if(main.GetCount())
			package.Add(prjaux, IdeImg::PrjAux(), ListFont(), Magenta);
		package.Add(ideaux, IdeImg::IdeAux(), ListFont(), Magenta);
		package.Add(tempaux, IdeImg::TempAux(), ListFont(), Magenta);
		if(main.GetCount())
			package.Add(METAPACKAGE, IdeImg::Meta(), ListFont(), Red);
	}
	package.SetCursor(0);
	
	SyncErrorPackages();
}
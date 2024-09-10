void MakeBuild::SaveMakeFile(const String& fn, bool exporting)
{
	BeginBuilding(false, true);

	VectorMap<String, String> bm = GetMethodVars(method);
	One<Host> host = CreateHost(false);
	One<Builder> b = CreateBuilder(~host);
	
	if(!b)
		return;
	
	const TargetMode& tm = GetTargetMode();

	String makefile;

	Vector<String> uppdirs = GetUppDirs();
	String uppout = exporting ? host->GetHostPath(GetVar("OUTPUT")) : "_out/";
	String inclist;

	Index<String> allconfig = PackageConfig(GetIdeWorkspace(), 0, bm, mainconfigparam, *host, *b);
	bool win32 = allconfig.Find("WIN32") >= 0;

	Workspace wspc;
	wspc.Scan(GetMain(), allconfig.GetKeys());

	for(int i = 1; i < wspc.GetCount(); i++) {
		Index<String> modconfig = PackageConfig(wspc, i, bm, mainconfigparam, *host, *b);
		for(int a = allconfig.GetCount(); --a >= 0;)
			if(modconfig.Find(allconfig[a]) < 0)
				allconfig.Remove(a);
	}

	if(!exporting)
		for(int i = 0; i < uppdirs.GetCount(); i++) {
			String srcdir = GetMakePath(AdjustMakePath(host->GetHostPath(AppendFileName(uppdirs[i], ""))), win32);
			makefile << "UPPDIR" << (i + 1) << " = " << srcdir << "\n";
			inclist << " -I$(UPPDIR" << (i + 1) << ")";
		}
	else
		inclist << "-I./";
	Vector<String> includes = SplitDirs(bm.Get("INCLUDE",""));
	for(int i = 0; i < includes.GetCount(); i++)
		inclist << " -I" << includes[i];

	makefile << "\n"
		"UPPOUT = " << (exporting ? "_out/" : GetMakePath(AdjustMakePath(host->GetHostPath(AppendFileName(uppout, ""))), win32)) << "\n"
		"CINC = " << inclist << "\n"
		"Macro = ";

	for(int i = 0; i < allconfig.GetCount(); i++)
		makefile << " -Dflag" << allconfig[i];
	makefile << "\n";

	String output, config, install, rules, linkdep, linkfiles, linkfileend;

	for(int i = 0; i < wspc.GetCount(); i++) {
		b->config = PackageConfig(wspc, i, bm, mainconfigparam, *host, *b);
		b->version = tm.version;
		b->method = method;
		MakeFile mf;
		b->AddMakeFile(mf, wspc[i], GetAllUses(wspc, i),
		               GetAllLibraries(wspc, i, bm, mainconfigparam, *host, *b), allconfig,
		               exporting);
		if(!i) {
			String tdir = mf.outdir;
			String trg;
			if(tm.target_override) {
				trg = GetMakePath(AdjustMakePath(tm.target), win32);
				if(!trg.IsEmpty() && *trg.Last() == (win32 ? '\\' : '/'))
					trg << mf.outfile;
				else if(trg.Find(win32 ? '\\' : '/') < 0)
					trg.Insert(0, "$(OutDir)");
			}
			output = Nvl(trg, mf.output);
			if(exporting)
				output = wspc[i] + ".out";
			install << "\n"
				"OutDir = " << tdir << "\n"
				"OutFile = " << output << "\n"
				"\n"
				".PHONY: all\n"
				"all: prepare $(OutFile)\n"
				"\n"
				".PHONY: prepare\n"
				"prepare:\n";
		}
		config << mf.config;
		install << mf.install;
		rules << mf.rules;
		linkdep << mf.linkdep;
		linkfiles << mf.linkfiles;
		linkfileend << mf.linkfileend;
	}

	makefile
		<< config
		<< install
		<< "\n"
		"$(OutFile): " << linkdep << "\n\t" << linkfiles << linkfileend << " -Wl,--end-group\n\n"
		<< rules
		<< ".PHONY: clean\n"
		<< "clean:\n"
		<< "\tif [ -d $(UPPOUT) ]; then rm -rf $(UPPOUT); fi;\n";

	bool sv = ::SaveFile(fn, makefile);
	if(!exporting)
		if(sv)
			PutConsole(NFormat("%s(1): makefile generation complete", fn));
		else
			PutConsole(NFormat("%s: error writing makefile", fn));

	EndBuilding(true);
}
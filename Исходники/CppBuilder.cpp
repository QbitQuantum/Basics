Vector<String> CppBuilder::CustomStep(const String& pf, const String& package_, bool& error)
{
	String package = Nvl(package_, mainpackage);
	String path = (*pf == '.' && pf[1] != '.') ? target : SourcePath(package, pf);
	String file = GetHostPath(path);
	String ext = ToLower(GetFileExt(pf));
	if(ext == ".ext") {
		Vector<String> files;
		Vector<String> dirs;
		sGatherAllExt(files, dirs, GetFileFolder(path), "");
		
		Index<String> pkg_files;
		Package pkg;
		pkg.Load(PackagePath(package));
		for(int i = 0; i < pkg.GetCount(); i++)
			pkg_files.Add(pkg[i]);
		
		Index<String> out;
		Index<String> include_path;
		String f = LoadFile(path);
		try {
			CParser p(f);
			while(!p.IsEof()) {
				if(p.Id("files")) {
					Vector<String> e = ReadPatterns(p);
					for(int i = 0; i < files.GetCount(); i++)
						for(int j = 0; j < e.GetCount(); j++) {
							String f = files[i];
							if(PatternMatch(e[j], f) && pkg_files.Find(f) < 0)
								out.FindAdd(f);
						}
				}
				if(p.Id("exclude")) {
					ExtExclude(p, out);
				}
				if(p.Id("include_path")) {
					Vector<String> e = ReadPatterns(p);
					for(int j = 0; j < e.GetCount(); j++) {
						String ee = e[j];
						if(ee.Find('*') >= 0)
							for(int i = 0; i < dirs.GetCount(); i++) {
								String d = dirs[i];
								if(PatternMatch(e[j], d)) {
									include_path.FindAdd(d);
								}
							}
						else
							include_path.Add(ee);
					}
				}
				if(p.Id("exclude_path")) {
					ExtExclude(p, include_path);
				}
				if(p.Id("includes")) {
					Vector<String> e = ReadPatterns(p);
					for(int i = 0; i < files.GetCount(); i++)
						for(int j = 0; j < e.GetCount(); j++) {
							String f = files[i];
							if(PatternMatch(e[j], f) && pkg_files.Find(f) < 0)
								include_path.FindAdd(GetFileFolder(f));
						}
				}
			}
		}
		catch(CParser::Error) {
			PutConsole("Invalid .ext file");
			error = true;
			return Vector<String>();
		}
		
		for(int i = 0; i < include_path.GetCount(); i++)
			include.Add(NormalizePath(include_path[i], GetFileFolder(path)));
		
		Vector<String> o;
		for(int i = 0; i < out.GetCount(); i++)
			o.Add(SourcePath(package, out[i]));
		return o;
	}
	for(int i = 0; i < wspc.GetCount(); i++) {
		const Array< ::CustomStep >& mv = wspc.GetPackage(i).custom;
		for(int j = 0; j < mv.GetCount(); j++) {
			const ::CustomStep& m = mv[j];
			if(MatchWhen(m.when, config.GetKeys()) && m.MatchExt(ext)) {
				VectorMap<String, String> mac;
				AddPath(mac, "PATH", file);
				AddPath(mac, "RELPATH", pf);
				AddPath(mac, "DIR", GetFileFolder(PackagePath(package)));
				AddPath(mac, "FILEDIR", GetFileFolder(file));
				AddPath(mac, "PACKAGE", package);
				mac.Add("FILE", GetFileName(file));
				mac.Add("TITLE", GetFileTitle(file));
				AddPath(mac, "EXEPATH", GetHostPath(target));
				AddPath(mac, "EXEDIR", GetHostPath(GetFileFolder(target)));
				mac.Add("EXEFILE", GetFileName(target));
				mac.Add("EXETITLE", GetFileTitle(target));
				AddPath(mac, "OUTDIR", GetHostPath(outdir));
				//BW
				AddPath(mac, "OUTDIR", GetHostPath(GetFileFolder(target)));
				AddPath(mac, "OUTFILE", GetHostPath(GetFileName(target)));
				AddPath(mac, "OUTTITLE", GetHostPath(GetFileTitle(target)));

				mac.Add("INCLUDE", Join(include, ";"));

				Vector<String> out = Cuprep(m.output, mac, include);
				bool dirty = out.IsEmpty();
				for(int i = 0; !dirty && i < out.GetCount(); i++)
					dirty = (GetFileTime(file) > GetFileTime(out[i]));
				if(dirty) {
					HdependTimeDirty();
					PutConsole(GetFileName(file));
					Vector<String> cmd = Cuprep(m.command, mac, include);
					String cmdtext;
					for(int c = 0; c < cmd.GetCount(); c++) {
						PutVerbose(cmd[c]);
						if(!Cd(cmd[c]) && !Cp(cmd[c], package, error)) {
							String ctext = cmd[c];
							const char *cm = ctext;
							if(*cm == '?')
								cm++;
							if(*ctext != '?' && Execute(cm)) {
								for(int t = 0; t < out.GetCount(); t++)
									DeleteFile(out[t]);
								PutConsole("FAILED: " + ctext);
								error = true;
								return Vector<String>();
							}
						}
					}
				}
				return out;
			}
		}
	}
	Vector<String> out;
	out.Add(path);
	return out;
}
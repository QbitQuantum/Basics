static void LoadIniStream(Stream& in, VectorMap<String, String>& key, const char *sfile)
{
	bool env = false;
	while(!in.IsEof()) {
		String line = in.GetLine();
		CParser p(line);
		if(p.IsId()) {
			String k = p.ReadId();
			if(p.Char('=')) {
				String h = TrimBoth((String)p.GetSpacePtr());
				if(env) {
					String hh;
					const char *s = ~h;
					while(*s) {
						if(*s == '$') {
							s++;
							if(*s == '$') {
								hh.Cat('$');
								s++;
							}
							else {
								String id;
								if (*s == '{') {
									while(*++s != '}')
										id.Cat(*s);
									s++;
								} else {
									while(iscid(*s))
										id.Cat(*s++);
								}
								hh.Cat(GetEnv(id));
							}
						}
						else
							hh.Cat(*s++);
					}
					key.Add(k, hh);
				}
				else
					key.Add(k, h);
			}
		}
		else
		if(p.Char('@')) {
			if(p.Id("include")) {
				String fn = p.GetPtr();
				if(!IsFullPath(fn) && sfile)
					fn = AppendFileName(GetFileFolder(GetFullPath(sfile)), fn);
				LoadIniFile(fn, key);
			}
			else
			if(p.Id("end"))
				return;
			else
			if(p.Id("replace-env"))
				env = true;
			else
			if(p.Id("ignore-env"))
				env = false;
		}
	}
}
bool CgiParams::ResolveInvalidFile(String &path, String &uri, String &value, Context &ctx) {
	StartTrace(CgiParams.ResolveInvalidFile);
	Trace("path :" << path << ": uri :" << uri << ":");
	long ixslash = uri.StrChr('/');
	if (ixslash >= 1) {
		String pgm = path;
		pgm << uri.SubString(0, ixslash - 1);
		if (coast::system::IsRegularFile(pgm)) {
			value = pgm;
			// should store additional arguments in query....here?
			return true;
		}
	}
	return URI2FileNameMapper::ResolveInvalidFile(path, uri, value, ctx);
}
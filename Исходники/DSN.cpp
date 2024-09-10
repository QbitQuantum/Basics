void DSN::loadAttributesFromRegistry()
{
	char buf[65536];
	const char* filename = "ODBC.INI";
	if (getName().size() == 0) return; // don't load from registry if this dsn does not have a name.
	SQLGetPrivateProfileString(getName().c_str(), "url", getUrl().c_str(), buf, 65536, filename);
	setUrl(buf);
	SQLGetPrivateProfileString(getName().c_str(), "uid", getUser().c_str(), buf, 65536, filename);
	setUser(buf);
	SQLGetPrivateProfileString(getName().c_str(), "pwd", getPassword().c_str(), buf, 65536, filename);
	setPassword(buf);
}
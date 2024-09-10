bool ConfigFile::isValidName(const String &name) {
	const char *p = name.c_str();
	while (*p && (isAlnum(*p) || *p == '-' || *p == '_' || *p == '.'))
		p++;
	return *p == 0;
}
String pathByAppendingComponent(const String& path, const String& component)
{
#ifdef _WIN32_WCE
	String res = path;
	res.replace('/', '\\');
	if (res.endsWith("\\"))
		return (res + component);
	else
		return (res + "\\" + component);
#else
	Vector<UChar> buffer(MAX_PATH);

	if (path.length() + 1 > buffer.size())
		return String();

	memcpy(buffer.data(), path.characters(), path.length() * sizeof(UChar));
	buffer[path.length()] = '\0';

	String componentCopy = component;
	if (!PathAppendW(buffer.data(), componentCopy.charactersWithNullTermination()))
		return String();

	buffer.resize(wcslen(buffer.data()));

	return String::adopt(buffer);
#endif
}
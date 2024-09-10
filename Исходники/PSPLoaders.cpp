static std::string NormalizePath(const std::string &path)
{
#ifdef _WIN32
	char buf[512] = {0};
	if (GetFullPathNameA(path.c_str(), sizeof(buf) - 1, buf, NULL) == 0)
		return "";
#else
	char buf[PATH_MAX + 1];
	if (realpath(path.c_str(), buf) == NULL)
		return "";
#endif
	return buf;
}
bool os_path_absolute(const std::string& path)
{
	return PathIsRelativeW(ConvertToWchar(path).c_str())==FALSE;
}
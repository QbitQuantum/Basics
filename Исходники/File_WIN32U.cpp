void FileImpl::copyToImpl(const std::string& path) const
{
	poco_assert (!_path.empty());

	std::wstring upath;
	UnicodeConverter::toUTF16(path, upath);
	if (CopyFileW(_upath.c_str(), upath.c_str(), FALSE) == 0)
		handleLastErrorImpl(_path);
}
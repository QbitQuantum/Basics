bool UMPath::remove_file(const umstring& file_path)
{
	std::wstring path = UMStringUtil::utf16_to_wstring(file_path);
	if (UMPath::exists(file_path) && !UMPath::is_folder(file_path))
	{
		_wremove(path.c_str());
		return true;
	}
	return false;
}
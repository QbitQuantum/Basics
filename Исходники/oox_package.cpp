void simple_element::write(const std::wstring & RootPath)
{
	std::wstring name_ = RootPath + FILE_SEPARATOR_STR + file_name_;

	NSFile::CFileBinary file;
	if ( file.CreateFileW(name_) == true)
	{
		if (bXml)
		{
			std::string root = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
			file.WriteFile((BYTE*)root.c_str(), root.length());
		}
		file.WriteFile((BYTE*)content_utf8_.c_str(), content_utf8_.length());
		file.CloseFile();
	}
}
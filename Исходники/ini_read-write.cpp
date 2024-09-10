void IniStream::edit(std::wstring const& section, std::wstring const& key, std::wstring const& str) {
	clearErr();
	if (false == WritePrivateProfileString(section.c_str(), key.c_str(), str.c_str(), this->filefullpath.c_str())) {
		throw std::runtime_error("IniStream::edit : " + getLastErrorText());
	}
}
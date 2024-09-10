/*
This function is still a proof of concept, it's probably rife with bugs, below
is a short (and incomplete) todo
 * "Basic" checks (Read/Write/File/Dir) checks for FAT32 filesystems which
   requires detecting the filesystem being used.
*/
void Check(fs::path const& file, acs::Type type) {
	DWORD file_attr = GetFileAttributes(file.c_str());
	if ((file_attr & INVALID_FILE_ATTRIBUTES) == INVALID_FILE_ATTRIBUTES) {
		switch (GetLastError()) {
			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				throw fs::FileNotFound(file);
			case ERROR_ACCESS_DENIED:
				throw fs::ReadDenied(file);
			default:
				throw fs::FileSystemUnknownError(str(boost::format("Unexpected error when getting attributes for \"%s\": %s") % file % util::ErrorString(GetLastError())));
		}
	}

	switch (type) {
		case FileRead:
		case FileWrite:
			if ((file_attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
				throw fs::NotAFile(file);
			break;
		case DirRead:
		case DirWrite:
			if ((file_attr & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
				throw fs::NotADirectory(file);
			break;
	}

	SECURITY_INFORMATION info = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	DWORD len = 0;
	GetFileSecurity(file.c_str(), info, nullptr, 0, &len);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		LOG_W("acs/check") << "GetFileSecurity: fatal: " << util::ErrorString(GetLastError());

	std::vector<uint8_t> sd_buff(len);
	SECURITY_DESCRIPTOR *sd = (SECURITY_DESCRIPTOR *)&sd_buff[0];

	if (!GetFileSecurity(file.c_str(), info, sd, len, &len))
		LOG_W("acs/check") << "GetFileSecurity failed: " << util::ErrorString(GetLastError());

	ImpersonateSelf(SecurityImpersonation);
	HANDLE client_token;
	if (!OpenThreadToken(GetCurrentThread(), TOKEN_ALL_ACCESS, TRUE, &client_token))
		LOG_W("acs/check") << "OpenThreadToken failed: " << util::ErrorString(GetLastError());

	if (!check_permission(true, sd, client_token))
		throw fs::ReadDenied(file);
	if ((type == DirWrite || type == FileWrite) && !check_permission(false, sd, client_token))
		throw fs::WriteDenied(file);
}
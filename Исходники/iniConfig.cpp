iniConfig::iniConfig(LPCSTR fileName)
{
	this->fileName = fileName;

	SetLastError(ERROR_SUCCESS);
	GetPrivateProfileSectionNamesA(buffer, sizeof buffer, fileName);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
		logFile << "Config: file not found!" << std::endl;
}
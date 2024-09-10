std::string CSystem::getComputerName()
{
	char computerName[256] = {};
	DWORD length = 256;
	GetComputerNameA(computerName, &length);
	return computerName;
}
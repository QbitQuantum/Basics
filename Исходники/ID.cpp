std::string ID::GetSerialNumber(void)
{
	DWORD dwSerial = 0;
	GetVolumeInformationA(NULL, NULL, NULL, &dwSerial, NULL, NULL, NULL, NULL);
	std::stringstream ss;
	ss << dwSerial;
	std::string num_str = ss.str();

	return num_str;
}
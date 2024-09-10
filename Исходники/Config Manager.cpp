void ConfigManager::getFloat(const char* section, const char* key, float& value)
{
	char result[255];
	char buffer[255];

	sprintf(buffer, "%f", value);
	GetPrivateProfileStringA(section, key, buffer, result, 255, directory);
	value = (float)atof(result);
}
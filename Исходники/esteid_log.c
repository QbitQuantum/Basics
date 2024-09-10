const char *EstEID_getLogFilename() {
#ifdef _WIN32
	if (!filename[0]) {
		char *tempValue;
		size_t length;
		if(_dupenv_s(&tempValue, &length, "TEMP")) {
			tempValue = strdup("");
		}
		sprintf_s(filename, MAX_LOG_FILE_NAME_LEN, "%s\\esteid.log", tempValue);
		free(tempValue);
	}
	return filename;
#else
	return "/tmp/esteid.log";
#endif
}
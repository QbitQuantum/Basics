void GenerateTempFileName ( char alter * tempFileNameOut, char const * extension ) {
#ifdef _MSC_VER
	char temp_dir[_MAX_DIR];
	DWORD dir_len = 0;
	
	dir_len = GetTempPathA(_MAX_DIR, temp_dir);
	assert(dir_len != 0);	
	assert(dir_len <= _MAX_DIR);
	UINT res = 0;
	res = GetTempFileNameA(temp_dir, "HOOPS", 0, tempFileNameOut);
	assert(res != 0);
	// if extension specified, replace .tmp with user-provided value
	if (extension) {
		char *old_extension = strrchr(tempFileNameOut, '.');
		if (extension[0] == '.')
			old_extension[0] = 0;
		else
			old_extension[1] = 0;
		strcat(tempFileNameOut, extension);
	}
#else
	strcpy(tempFileNameOut, "/tmp/tmpXXXXXX");
	int ext_len = 0;
	
	if (extension) {
		if (extension[0] != '.') {
			strcat(tempFileNameOut, ".");
			ext_len += 1;
		}
		strcat(tempFileNameOut, extension);
		ext_len += strlen(extension);
	}
	else {
		strcat(tempFileNameOut, ".tmp");
		ext_len += 4;
	}
	
	int fileDescriptor = mkstemps(tempFileNameOut, ext_len);
	if (fileDescriptor == -1) {
		printf("mkstemps call failed.\nerrno: %d\t%s\n", errno, strerror(errno));
		tempFileNameOut[0] = 0;
	}
	else
		close(fileDescriptor);
#endif
}
int test_read(HANDLE hf, LARGE_INTEGER offset) {
    char buffer[256];
    DWORD dwRead;
    int ret = 0;

    if (!LockFile(hf, offset.u.LowPart, offset.u.HighPart, 
		   4096, 0)) {
	fprintf(stderr, "Unable to lock offset 0x%08x:%08x gle = 0x%08x\n", 
		 offset.u.HighPart, offset.u.LowPart, GetLastError());
	return -1;
    }

    if (!SetFilePointerEx(hf, offset, NULL, FILE_BEGIN)) {
	fprintf(stderr, "Unable to set file pointer to offset 0x%08x:%08x gle = 0x%08x\n", 
		 offset.u.HighPart, offset.u.LowPart, GetLastError());
	ret = -1;
	goto unlock;
    }

    if (!ReadFile(hf, buffer, strlen(teststr)+1, &dwRead, NULL)) {
	fprintf(stderr, "Unable to read test string at offset 0x%08x:%08x gle = 0x%08x\n", 
		 offset.u.HighPart, offset.u.LowPart, GetLastError());
	ret = -1;
	goto unlock;
    } else {
	printf("read '%s' (%d bytes) at offset 0x%08x:%08x\n", buffer, dwRead, offset.u.HighPart, offset.u.LowPart);
    }

    if (strcmp(buffer, teststr)) {
	fprintf(stderr, "Test string comparison failure at offset 0x%08x:%08x\n", 
		 offset.u.HighPart, offset.u.LowPart);
	ret = -1;
	goto unlock;
    }

  unlock:
    if (!UnlockFile(hf, offset.u.LowPart, offset.u.HighPart,
		   4096, 0)) {
	fprintf(stderr, "Unable to unlock offset 0x%08x:%08x gle = 0x%08x\n", 
		 offset.u.HighPart, offset.u.LowPart, GetLastError());
	ret = -1;
    }

    return ret;
}
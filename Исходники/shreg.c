static void test_SHQueryValueEx(void)
{
	HKEY hKey;
	DWORD dwSize;
	DWORD dwType;
	char buf[MAX_PATH];
	DWORD dwRet;
	const char * sTestedFunction = "";
	DWORD nUsedBuffer1,nUsedBuffer2;

        sTestedFunction = "RegOpenKeyExA";
        dwRet = RegOpenKeyExA(HKEY_CURRENT_USER, REG_TEST_KEY, 0,  KEY_QUERY_VALUE, &hKey);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);

	/****** SHQueryValueExA ******/

	sTestedFunction = "SHQueryValueExA";
	nUsedBuffer1 = max(strlen(sExpTestpath1)+1, strlen(sTestpath1)+1);
	nUsedBuffer2 = max(strlen(sExpTestpath2)+1, strlen(sTestpath2)+1);
	/*
	 * Case 1.1 All arguments are NULL
	 */
        dwRet = SHQueryValueExA( hKey, "Test1", NULL, NULL, NULL, NULL);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);

	/*
	 * Case 1.2 dwType is set
	 */
	dwType = -1;
        dwRet = SHQueryValueExA( hKey, "Test1", NULL, &dwType, NULL, NULL);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);
	ok( REG_SZ == dwType , "Expected REG_SZ, got (%u)\n", dwType);

	/*
	 * dwSize is set
         * dwExpanded < dwUnExpanded
	 */
	dwSize = 6;
        dwRet = SHQueryValueExA( hKey, "Test1", NULL, NULL, NULL, &dwSize);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);
	ok( dwSize == nUsedBuffer1, "Buffer sizes (%u) and (%u) are not equal\n", dwSize, nUsedBuffer1);

	/*
         * dwExpanded > dwUnExpanded
	 */
	dwSize = 6;
        dwRet = SHQueryValueExA( hKey, "Test3", NULL, NULL, NULL, &dwSize);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);
        ok( dwSize >= nUsedBuffer2 ||
            broken(dwSize == (strlen(sTestpath2) + 1)), /* < IE4.x */
            "Buffer size (%u) should be >= (%u)\n", dwSize, nUsedBuffer2);

	/*
	 * Case 1 string shrinks during expanding
	 */
	strcpy(buf, sEmptyBuffer);
	dwSize = 6;
	dwType = -1;
	dwRet = SHQueryValueExA( hKey, "Test1", NULL, &dwType, buf, &dwSize);
	ok( ERROR_MORE_DATA == dwRet, "Expected ERROR_MORE_DATA, got (%u)\n", dwRet);
	ok( 0 == strcmp(sEmptyBuffer, buf) , "Comparing (%s) with (%s) failed\n", buf, sEmptyBuffer);
	ok( dwSize == nUsedBuffer1, "Buffer sizes (%u) and (%u) are not equal\n", dwSize, nUsedBuffer1);
        ok( REG_SZ == dwType ||
            broken(REG_EXPAND_SZ == dwType), /* < IE6 */
            "Expected REG_SZ, got (%u)\n", dwType);

	/*
	 * string grows during expanding
         * dwSize is smaller than the size of the unexpanded string
	 */
	strcpy(buf, sEmptyBuffer);
	dwSize = 6;
	dwType = -1;
	dwRet = SHQueryValueExA( hKey, "Test3", NULL, &dwType, buf, &dwSize);
	ok( ERROR_MORE_DATA == dwRet, "Expected ERROR_MORE_DATA, got (%u)\n", dwRet);
	ok( 0 == strcmp(sEmptyBuffer, buf) , "Comparing (%s) with (%s) failed\n", buf, sEmptyBuffer);
        ok( dwSize >= nUsedBuffer2 ||
            broken(dwSize == (strlen(sTestpath2) + 1)), /* < IE6 */
            "Buffer size (%u) should be >= (%u)\n", dwSize, nUsedBuffer2);
        ok( REG_SZ == dwType ||
            broken(REG_EXPAND_SZ == dwType), /* < IE6 */
            "Expected REG_SZ, got (%u)\n", dwType);

        /*
         * string grows during expanding
         * dwSize is larger than the size of the unexpanded string, but
         * smaller than the part before the backslash. If the unexpanded
         * string fits into the buffer, it can get cut when expanded.
         */
        strcpy(buf, sEmptyBuffer);
        dwSize = strlen(sEnvvar2) - 2;
        dwType = -1;
        dwRet = SHQueryValueExA( hKey, "Test3", NULL, &dwType, buf, &dwSize);
        ok( ERROR_MORE_DATA == dwRet ||
            broken(ERROR_ENVVAR_NOT_FOUND == dwRet) || /* IE5.5 */
            broken(ERROR_SUCCESS == dwRet), /* < IE5.5*/
            "Expected ERROR_MORE_DATA, got (%u)\n", dwRet);

        todo_wine
        {
                ok( (0 == strcmp("", buf)) || (0 == strcmp(sTestpath2, buf)),
                    "Expected empty or unexpanded string (win98), got (%s)\n", buf); 
        }

        ok( dwSize >= nUsedBuffer2 ||
            broken(dwSize == (strlen("") + 1)), /* < IE 5.5 */
            "Buffer size (%u) should be >= (%u)\n", dwSize, nUsedBuffer2);
        ok( REG_SZ == dwType , "Expected REG_SZ, got (%u)\n", dwType);

	/*
         * string grows during expanding
         * dwSize is larger than the size of the part before the backslash,
         * but smaller than the expanded string. If the unexpanded string fits
         * into the buffer, it can get cut when expanded.
	 */
	strcpy(buf, sEmptyBuffer);
	dwSize = nExpLen2 - 4;
	dwType = -1;
        dwRet = SHQueryValueExA( hKey, "Test3", NULL, &dwType, buf, &dwSize);
        ok( ERROR_MORE_DATA == dwRet ||
            broken(ERROR_ENVVAR_NOT_FOUND == dwRet) || /* IE5.5 */
            broken(ERROR_SUCCESS == dwRet), /* < IE5.5 */
            "Expected ERROR_MORE_DATA, got (%u)\n", dwRet);

        todo_wine
        {
            ok( (0 == strcmp("", buf)) || (0 == strcmp(sEnvvar2, buf)) ||
                broken(0 == strcmp(sTestpath2, buf)), /* IE 5.5 */
                "Expected empty or first part of the string \"%s\", got \"%s\"\n", sEnvvar2, buf);
        }

        ok( dwSize >= nUsedBuffer2 ||
            broken(dwSize == (strlen(sEnvvar2) + 1)) || /* IE4.01 SP1 (W98) and IE5 (W98SE) */
            broken(dwSize == (strlen("") + 1)), /* IE4.01 (NT4) and IE5.x (W2K) */
            "Buffer size (%u) should be >= (%u)\n", dwSize, nUsedBuffer2);
	ok( REG_SZ == dwType , "Expected REG_SZ, got (%u)\n", dwType);

	/*
	 * The buffer is NULL but the size is set
	 */
	strcpy(buf, sEmptyBuffer);
	dwSize = 6;
	dwType = -1;
	dwRet = SHQueryValueExA( hKey, "Test3", NULL, &dwType, NULL, &dwSize);
	ok( ERROR_SUCCESS == dwRet, "%s failed, ret=%u\n", sTestedFunction, dwRet);
        ok( dwSize >= nUsedBuffer2 ||
            broken(dwSize == (strlen(sTestpath2) + 1)), /* IE4.01 SP1 (Win98) */
            "Buffer size (%u) should be >= (%u)\n", dwSize, nUsedBuffer2);
	ok( REG_SZ == dwType , "Expected REG_SZ, got (%u)\n", dwType);

	RegCloseKey(hKey);
}
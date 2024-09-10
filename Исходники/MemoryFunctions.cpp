bool My_LocalReAlloc(HLOCAL ret, DWORD error)
{
	HLOCAL dwRet = 0;

	////
	dwRet = LocalReAlloc(GENERIC_HANDLE, INT_VAL, INT_VAL);

	if (dwRet != ret)
		goto FAILED;

	if (!checkErrorCode(error))
		goto FAILED;

	uninterceptedPrint("LocalReAlloc PASSED!\n");

return TRUE;

FAILED:
	uninterceptedPrint("LocalReAlloc FAILED!\n");
	return FALSE;
}
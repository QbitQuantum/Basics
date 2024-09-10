DWORD APIENTRY
NPAddConnection(
    __in LPNETRESOURCE NetResource,
	__in LPWSTR Password,
    __in LPWSTR UserName)
{
	DbgPrintW(L"NPAddConnection\n");
	return  NPAddConnection3(NULL, NetResource, Password, UserName, 0);
}
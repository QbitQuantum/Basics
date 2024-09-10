//Test Method2
extern "C" DLL_EXPORT LPWSTR Marshal_InOut(/*[In,Out]*/LPWSTR s)
{

    //Check the Input
	size_t len = wcslen(s);

    if((len != lenstrManaged)||(wmemcmp(s,(WCHAR*)strManaged,len)!=0))
    {
        printf("Error in Function Marshal_InOut(Native Client)\n");
        return ReturnErrString();
    }

    //In-Place Change
    wcsncpy_s(s,len+1,strNative,lenstrNative);

    //Return
    return ReturnString();
}
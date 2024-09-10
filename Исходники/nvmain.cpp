String guidToString(const GUID &guid)
{
    LPOLESTR resStr;
    String res;

    if (StringFromCLSID(guid, &resStr) == S_OK)
    {
        res = resStr;
        CoTaskMemFree(resStr);
    }

    return res;
}
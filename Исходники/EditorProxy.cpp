Handle<Value> EditorGetSelection(const Arguments& args)
{
    CComPtr<VirtualPoint> virtualPoint;
    CComBSTR buf;    

    g_pSelection->get_Text(&buf);

    int retValLen = buf.Length();
    if (0 == retValLen)
        return String::New("");

    PSTR asciiBuf = (PSTR)HeapAlloc(GetProcessHeap(), 0, retValLen + 1);

    WideCharToMultiByte(CP_ACP, 0, buf, retValLen + 1, asciiBuf, retValLen + 1, NULL, NULL);
    asciiBuf[retValLen] = '\0';

    int destIndex = 0;
    for (int index = 0; index <= retValLen; index++)
    {
        if (asciiBuf[index] != '\r')
        {
            asciiBuf[destIndex] = asciiBuf[index];
            destIndex++;
        }
    }
    asciiBuf[destIndex] = '\0';

    Handle<String> retVal = String::New(asciiBuf, destIndex);

    HeapFree(GetProcessHeap(), 0, asciiBuf);

    return retVal;
}
char* WINAPI StringFromResource(char* pBuffer, int iResourceID)
{
    if (LoadStringA(g_hInst, iResourceID, pBuffer, STR_MAX_LENGTH) == 0) {
        return "";
    }
    return pBuffer;
}
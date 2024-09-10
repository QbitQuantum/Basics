DWORD GetFormattedErrorMessage(__out PWSTR * pwszErrorMessage, DWORD dwMessageId, va_list* arguments)
{
    DWORD dwLength = 0;
    LPWSTR wszSystemErrorMessage = NULL;

    do
    {
        if (NULL == pwszErrorMessage)
        {
            break;
        }
        *pwszErrorMessage = NULL;

        if (NULL == g_hResourceInstance)
        {
#ifdef CORECLR
            g_hResourceInstance = LoadLibraryEx(g_MAIN_BINARY_NAME, 0, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
#else
            g_hResourceInstance = LoadMUILibraryW(g_MAIN_BINARY_NAME, MUI_LANGUAGE_NAME, 0);
#endif
        }

        dwLength = FormatMessageW(
            FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            g_hResourceInstance,
            dwMessageId,
            0,
            (LPWSTR)&wszSystemErrorMessage,
            0,
            arguments);

        if (dwLength == 0)
        {
            break;
        }

        *pwszErrorMessage = new WCHAR[dwLength + 1];
        if (*pwszErrorMessage == NULL)
        {
            dwLength = 0;
            break;
        }

        if (FAILED(StringCchCopyW(*pwszErrorMessage, dwLength + 1, wszSystemErrorMessage)))
        {
            dwLength = 0;
            delete [] (*pwszErrorMessage);
            *pwszErrorMessage = NULL;
        }

    }while(false);

    if (NULL != wszSystemErrorMessage)
    {
        LocalFree(wszSystemErrorMessage);
    }

    return dwLength;
}
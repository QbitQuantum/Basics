LPWSTR FixupHtmlFilePath(LPWSTR path)
{
    WCHAR fullPath[MAX_PATH + 1] = { 0 };
    LPWSTR fullUrl = NULL;
    
    do
    {
        if (path)
        {
            GetWorkingPath(fullPath, MAX_PATH, path);
            if (PathFileExistsW(fullPath))
                break;

            GetProgramPath(fullPath, MAX_PATH, path);
            if (PathFileExistsW(fullPath))
                break;   
        }

        GetWorkingPath(fullPath, MAX_PATH, L"main.html");
        if (PathFileExistsW(fullPath))
            break;

        GetWorkingPath(fullPath, MAX_PATH, L"wkexe.html");
        if (PathFileExistsW(fullPath))
            break;    

        GetProgramPath(fullPath, MAX_PATH, L"index.html");
        if (PathFileExistsW(fullPath))
            break;    

        GetProgramPath(fullPath, MAX_PATH, L"main.html");
        if (PathFileExistsW(fullPath))
            break;

        GetProgramPath(fullPath, MAX_PATH, L"wkexe.html");
        if (PathFileExistsW(fullPath))
            break;

        return path;
    }
    while (0);

    fullUrl = (WCHAR*)malloc(sizeof(WCHAR) * (MAX_PATH + 1 + 10));
    _snwprintf(fullUrl, MAX_PATH + 1 + 10, L"file:///%s", fullPath);
    return fullUrl;
}
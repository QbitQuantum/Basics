OS_EXPORT int FileUtilities::makeDirAll(const std::wstring& aDirPath)
{
    JELOG2(EJavaFile);
    bool ableToOpen = true;
    std::wstring path;
    wchar_t *last, *tok, *delim =L"/" ;
    wchar_t *stringToTokenize = new wchar_t[aDirPath.length()+ 1];
    wcscpy(stringToTokenize, aDirPath.c_str());

    for (tok = wcstok(stringToTokenize,delim,&last); tok!=NULL;
            tok = wcstok(NULL, delim, &last))
    {
        path += std::wstring(tok);
        path += L"/";
        char *dirName = JavaCommonUtils::wstringToUtf8(path);
        if (ableToOpen)
        {
            DIR* wDirHandle = opendir(dirName);
            if (!wDirHandle)
            {
                ableToOpen = false;
                if (mkdir(dirName,0666)<0)
                {
                    WLOG1(EJavaFile,"FileUtilities::makeDirAll: Directory Creation Failed : %s",dirName);
                    delete[] dirName;
                    delete[] stringToTokenize;
                    return -1;
                }
            }
            closedir(wDirHandle); 
        }
        else
        {
            if (mkdir(dirName,0666)<0)
            {
                ELOG1(EJavaFile, "FileUtilities::makeDirAll: Directory Creation Failed : %s",dirName);
                delete[] dirName;
                delete[] stringToTokenize;
                return -1;
            }
        }
        delete[] dirName;
    }
    delete[] stringToTokenize;
    return 0;
}
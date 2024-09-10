bool  XConfig::Open(CTSTR lpFile)
{
    if(RootElement)
    {
        if(strFileName.CompareI(lpFile))
            return true;

        Close();
    }

    //-------------------------------------
    XFile file;

    if(!file.Open(lpFile, XFILE_READ, XFILE_OPENALWAYS))
        return false;

    RootElement = new XElement(this, NULL, TEXT("Root"));
    strFileName = lpFile;

    DWORD dwFileSize = (DWORD)file.GetFileSize();

    LPSTR lpFileDataUTF8 = (LPSTR)Allocate(dwFileSize+1);
    zero(lpFileDataUTF8, dwFileSize+1);
    file.Read(lpFileDataUTF8, dwFileSize);

    TSTR lpFileData = utf8_createTstr(lpFileDataUTF8);
    Free(lpFileDataUTF8);

    //-------------------------------------
    // remove comments

    TSTR lpComment, lpEndComment;

    while(lpComment = sstr(lpFileData, TEXT("/*")))
    {
        lpEndComment = sstr(lpFileData, TEXT("*/"));

        assert(lpEndComment);
        assert(lpComment < lpEndComment);

        if(!lpEndComment || (lpComment > lpEndComment))
        {
            file.Close();

            Close(false);
            Free(lpFileData);

            CrashError(TEXT("Error parsing X file '%s'"), strFileName.Array());
        }

        mcpy(lpComment, lpEndComment+3, slen(lpEndComment+3)+1);
    }

    //-------------------------------------

    TSTR lpTemp = lpFileData;

    if(!ReadFileData(RootElement, 0, lpTemp))
    {
        for(DWORD i=0; i<RootElement->SubItems.Num(); i++)
            delete RootElement->SubItems[i];

        CrashError(TEXT("Error parsing X file '%s'"), strFileName.Array());

        Free(lpFileData);
        Close(false);
        file.Close();
    }

    Free(lpFileData);

    file.Close();

    return true;
}
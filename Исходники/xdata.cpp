void 
addXdata() 
{
    AcDbObject* pObj = selectObject(AcDb::kForRead);
    if (!pObj) {
        acutPrintf(_T("Error selecting object\n"));
        return;
    }

    
    // Get the application name and string to be added to
    // xdata.
    //
    TCHAR appName[132], resString[200];
    appName[0] = resString[0] = _T('\0');

    acedGetString(NULL, _T("Enter application name: "),
        appName);
    acedGetString(NULL, _T("Enter string to be added: "),
        resString);

    
    struct  resbuf  *pRb, *pTemp;
    
    pRb = pObj->xData(appName);

    if (pRb != NULL) {

        // If xdata is present, then walk to the
        // end of the list.
        //
        for (pTemp = pRb; pTemp->rbnext != NULL;
                pTemp = pTemp->rbnext)
                { ; }
    } else {
        // If xdata is not present, register the application
        // and add appName to the first resbuf in the list.
        // Notice that there is no -3 group as there is in
        // AutoLISP. This is ONLY the xdata so
        // the -3 xdata-start marker isn't needed.
        // 
        acdbRegApp(appName);

        pRb = acutNewRb(AcDb::kDxfRegAppName);
        pTemp = pRb;
        const size_t nSize = _tcslen(appName) + 1;
        pTemp->resval.rstring
            = (TCHAR*) malloc(nSize * sizeof(TCHAR));
        errno_t err = _tcscpy_s(pTemp->resval.rstring, nSize, appName);
        assert(err == 0);
    }

    // Add user-specified string to the xdata.
    //
    pTemp->rbnext = acutNewRb(AcDb::kDxfXdAsciiString);
    pTemp = pTemp->rbnext;
    const size_t nSize = _tcslen(resString) + 1;
    pTemp->resval.rstring
        = (TCHAR*) malloc(nSize * sizeof(TCHAR));
    errno_t err = _tcscpy_s(pTemp->resval.rstring, nSize, resString);
    assert(err == 0);

    // The following code shows the use of upgradeOpen()
    // to change the entity from read to write.
    //
    pObj->upgradeOpen();
    pObj->setXData(pRb);
    
    pObj->close();
    acutRelRb(pRb);
}
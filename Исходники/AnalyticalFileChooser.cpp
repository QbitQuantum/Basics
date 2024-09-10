static BOOL checkTextModify(CMFCEditBrowseCtrl &ctrl, LPTSTR text)
{
    static const int bsize = AnalyticalFileChooser::bufSize;
    static TCHAR tmpBuf[bsize];
    static int textLen;
    static BOOL change;

    textLen = ctrl.GetWindowTextLengthW();
    ctrl.GetWindowTextW(tmpBuf, bsize);
    StrTrim(tmpBuf,  _T(" \t"));
    change =  0 == memcmp(tmpBuf, text, textLen * sizeof(TCHAR)) ? FALSE : TRUE;

    /*if (change)
    	lstrcpynW(text, tmpBuf, bsize);*/
    return change;
}
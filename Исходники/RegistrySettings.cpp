void CRegistrySettings::GetLastSelectionRectangle(CRect &rcLastSelection) {
    unsigned long lLength = MAX_PATH;
    _TCHAR szLastSelectionRectangle[MAX_PATH];
    bool bRet = LRegistry::ReadStringRegistryEntry(HKEY_CURRENT_USER, 
        _T("Software\\imc AG\\LECTURNITY\\Assistant\\SgSettings\\"), 
        _T("LastSelectionRectangleCustom"), szLastSelectionRectangle, &lLength);

    CString csLastSelectionRectangle = szLastSelectionRectangle;
    rcLastSelection.SetRectEmpty();
    if (bRet && !csLastSelectionRectangle.IsEmpty()) {
        int iPos = csLastSelectionRectangle.Find(_T(";"));
        CString csValue;
        bool bError = false;
        if (iPos > 0) {
            csValue = csLastSelectionRectangle.Left(iPos);
            rcLastSelection.left = _ttoi(csValue);
        }
        else
            bError = true;

        if (!bError) {
            int iNewLength = csLastSelectionRectangle.GetLength() - (iPos+1);
            csLastSelectionRectangle = csLastSelectionRectangle.Right(iNewLength);
            iPos = csLastSelectionRectangle.Find(_T(";"));
            if (iPos > 0) {
                csValue = csLastSelectionRectangle.Left(iPos);
                rcLastSelection.top = _ttoi(csValue);
            }
            else
                bError = true;
        }

        if (!bError) {
            int iNewLength = csLastSelectionRectangle.GetLength() - (iPos+1);
            csLastSelectionRectangle = csLastSelectionRectangle.Right(iNewLength);
            iPos = csLastSelectionRectangle.Find(_T(";"));
            if (iPos > 0) {
                csValue = csLastSelectionRectangle.Left(iPos);
                rcLastSelection.right = _ttoi(csValue);
            }
            else
                bError = true;
        }

        if (!bError) {
            int iNewLength = csLastSelectionRectangle.GetLength() - (iPos+1);
            csLastSelectionRectangle = csLastSelectionRectangle.Right(iNewLength);
            csValue = csLastSelectionRectangle;
            rcLastSelection.bottom = _ttoi(csValue);
        }
    }
}
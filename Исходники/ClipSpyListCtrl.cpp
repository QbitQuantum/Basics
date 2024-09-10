void CClipSpyListCtrl::ReadClipboard()
{
CComPtr<IDataObject> pDO;

    if ( FAILED( OleGetClipboard ( &pDO ) ))
        return;

    ReadDataAndFillList ( pDO );
}
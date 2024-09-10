//+-------------------------------------------------------------------------
//
//  Member:     FormSetClipboard(IDataObject *pdo)
//
//  Synopsis:   helper function to set the clipboard contents
//
//--------------------------------------------------------------------------
HRESULT FormSetClipboard(IDataObject* pdo)
{
    HRESULT hr;
    hr = OleSetClipboard(pdo);

    if(!hr && !GetPrimaryObjectCount())
    {
        hr = OleFlushClipboard();
    }
    else
    {
        TLS(pDataClip) = pdo;
    }

    RRETURN(hr);
}
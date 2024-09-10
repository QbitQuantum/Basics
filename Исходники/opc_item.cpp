/*##{method}####################################################################

--------------------------------------------------------------------------------

  Description: Ausgabe eines Fehlers

   Parameters:

Return Values:

--------------------------------------------------------------------------------
  History:
#######################################################################{end}##*/
long COPCItem :: OutPutError(HRESULT hError)
{
    HRESULT hRes;
    WCHAR *pszError;
    hRes = mOPCServer->GetErrorString(hError, GetUserDefaultLCID(), &pszError);
    if (FAILED(hRes))
    {
        CString strError;
        strError.Format("Error: 0x%08X", hError);
        return 1;
    }
	printf("Error: %ls\n", pszError);
    CoTaskMemFree(pszError);
    return 0;
}
//-----------------------------------------------------------------------------
// Name: SetElementsEventsCallBack
// Object: set simple document events callback
// Parameters :
//     in  : 
//     out : 
//     return : 
//-----------------------------------------------------------------------------
BOOL CElementEvents::SetElementEventsCallBack(pfElementEventsCallBack ElementEventsCallBack,LPVOID UserParam)
{
    if (IsBadCodePtr((FARPROC)ElementEventsCallBack) && (ElementEventsCallBack!=0))
        return FALSE;

    this->ElementEventsCallBack=ElementEventsCallBack;
    this->ElementEventsCallBackUserParam=UserParam;

    return TRUE;
}
//-----------------------------------------------------------------------------
// Name: SetElementsEventsCallBackEx
// Object: set extended document events callback
// Parameters :
//     in  : 
//     out : 
//     return : 
//-----------------------------------------------------------------------------
BOOL CHtmlViewer::SetElementsEventsCallBackEx(pfElementEventsCallBackEx ElementEventsCallBackEx,LPVOID UserParam)
{
    if (IsBadCodePtr((FARPROC)ElementEventsCallBackEx) && (ElementEventsCallBackEx!=0))
        return FALSE;

    this->ElementEventsCallBackEx=ElementEventsCallBackEx;
    this->ElementEventsCallBackExUserParam=UserParam;

    if (this->pDocumentElementEvents)
        this->pDocumentElementEvents->SetElementEventsCallBackEx(this->ElementEventsCallBackEx,this->ElementEventsCallBackExUserParam);

    return TRUE;
}
/**
 * throws a _com_error exception with a created error information
 * object supporting the interface IErrorInfo. The error information
 * object can be used to determine the source of the error and the
 * cause of the error. If the HRESULT of the error passed is E_OUT-
 * OFMEMORY indicating an out of memory exception only a _com_error
 * exception will be generated without an error information object.
 * Further if the passed CLSID reference is CLSID_NULL only a _com_error
 * exception without a error information object will be generated.
 * The error description (IErrorInfo::SetDescription etc.) will be
 * generated through a call to ::FormatMessage with the HRESULT.
 * @param   clsid - CLSID indicating the source of the error.
 * @param   riid - Interface context of the error source.
 * @param   hr - HRESULT error code of the error
 * @param   ... additional parameters passed to FormatMessage to
 *  generate the error description.<br>
 * @return  -
 * @exception   _com_error (with error info object).
 * @see SDK Documentation on ::FormatMessage, interface IErrorInfo.
*/
void ComThrow(const CLSID& clsid, REFIID riid,HRESULT hr,...) throw()
{
    IErrorInfo* pInfo;

    LPTSTR pszOut;
    //special handling for E_OUTOFMEMORY
    if(hr == E_OUTOFMEMORY) {
        _com_raise_error(hr); //no error info object
    }

    {
        CString strOut;
        va_list arg_ptr;

        va_start(arg_ptr,hr);
        pszOut = strOut.GetBuffer(_MAX_PATH);
        FormatMsgArg(pszOut,hr,arg_ptr);
        strOut.ReleaseBuffer();
        va_end(arg_ptr);

        ComErrorInfo(clsid,riid,&pInfo,strOut);
    }
    _com_raise_error(hr,pInfo);
}
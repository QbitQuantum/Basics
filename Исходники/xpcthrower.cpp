// static
void
XPCThrower::ThrowCOMError(JSContext* cx, unsigned long COMErrorCode,
                          nsresult rv, const EXCEPINFO * exception)
{
    nsCAutoString msg;
    IErrorInfo * pError;
    const char * format;
    if(!nsXPCException::NameAndFormatForNSResult(rv, nsnull, &format))
        format = "";
    msg = format;
#ifndef WINCE
    if(exception)
    {
        msg += static_cast<const char *>
                          (_bstr_t(exception->bstrSource, false));
        msg += " : ";
        msg.AppendInt(static_cast<PRUint32>(COMErrorCode));
        msg += " - ";
        msg += static_cast<const char *>
                          (_bstr_t(exception->bstrDescription, false));
    }
    else
    {
        // Get the current COM error object
        unsigned long result = GetErrorInfo(0, &pError);
        if(SUCCEEDED(result) && pError)
        {
            // Build an error message from the COM error object
            BSTR bstrSource = NULL;
            if(SUCCEEDED(pError->GetSource(&bstrSource)) && bstrSource)
            {
                _bstr_t src(bstrSource, false);
                msg += static_cast<const char *>(src);
                msg += " : ";
            }
            msg.AppendInt(static_cast<PRUint32>(COMErrorCode), 16);
            BSTR bstrDesc = NULL;
            if(SUCCEEDED(pError->GetDescription(&bstrDesc)) && bstrDesc)
            {
                msg += " - ";
                _bstr_t desc(bstrDesc, false);
                msg += static_cast<const char *>(desc);
            }
        }
        else
        {
            // No error object, so just report the result
            msg += "COM Error Result = ";
            msg.AppendInt(static_cast<PRUint32>(COMErrorCode), 16);
        }
    }

#else
    // No error object, so just report the result
    msg += "COM Error Result = ";
    msg.AppendInt(static_cast<PRUint32>(COMErrorCode), 16);
#endif

    XPCThrower::BuildAndThrowException(cx, rv, msg.get());
}
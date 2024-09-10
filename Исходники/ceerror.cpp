HRESULT
ceHExceptionCode(
    IN EXCEPTION_POINTERS const *pep)
{
    HRESULT hr;
    if (0 != pep->ExceptionRecord)
    {
        hr = pep->ExceptionRecord->ExceptionCode;
    }
    else
    {
        hr = E_FAIL;
    }

#if (0 == i386)
    if ((HRESULT) STATUS_DATATYPE_MISALIGNMENT == hr)
    {
	hr = CERTSRV_E_ALIGNMENT_FAULT;
    }
#endif
    return(ceHError(hr));
}
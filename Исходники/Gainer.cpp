HRESULT STDMETHODCALLTYPE CGainer::WriteAllDigitalOutputs( 
            /* [in] */ SAFEARRAY **NewValue)
{
    if (!m_iothread) return Error(IDS_E_NOTOPENED);
    if (!NewValue || !*NewValue) return E_POINTER;
    SAFEARRAY* p = *NewValue;
    SafeArrayLock(p);
    LPBYTE pdata = reinterpret_cast<LPBYTE>(p->pvData);
    char* dst = reinterpret_cast<char*>(_alloca(p->rgsabound[0].cElements + 8));
    char* msg = dst;
    *dst++ = 'D';
    for (size_t i = p->rgsabound[0].lLbound; i < p->rgsabound[0].cElements; i++)
    {
        dst += sprintf(dst, "%d", *(pdata + i - p->rgsabound[0].lLbound));
    }
    *dst++ = '*';
    *dst = '\0';
    SafeArrayUnlock(p);
    notify_message(m_iothread_id, WM_COM_IO, msg);
    return S_OK;
}
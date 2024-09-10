// Get a dispatch pointer from the current object associated
// with a ProgID
bool wxAutomationObject::GetInstance(const wxString& progId, int flags) const
{
    if (m_dispatchPtr)
        return false;

    CLSID clsId;
    HRESULT hr = wxCLSIDFromProgID(progId, clsId);
    if (FAILED(hr))
        return false;

    IUnknown *pUnk = NULL;
    hr = GetActiveObject(clsId, NULL, &pUnk);
    if (FAILED(hr))
    {
        if ( flags & wxAutomationInstance_CreateIfNeeded )
        {
            const_cast<wxAutomationObject *>(this)->
                m_dispatchPtr = DoCreateInstance(progId, clsId);
            if ( m_dispatchPtr )
                return true;
        }
        else
        {
            // Log an error except if we're supposed to fail silently when the
            // error is that no current instance exists.
            if ( hr != MK_E_UNAVAILABLE ||
                    !(flags & wxAutomationInstance_SilentIfNone) )
            {
                wxLogSysError(hr,
                              _("Cannot get an active instance of \"%s\""),
                              progId);
            }
        }

        return false;
    }

    hr = pUnk->QueryInterface(IID_IDispatch, (LPVOID*) &m_dispatchPtr);
    if (FAILED(hr))
    {
        wxLogSysError(hr,
                      _("Failed to get OLE automation interface for \"%s\""),
                      progId);
        return false;
    }

    return true;
}
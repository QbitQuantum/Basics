bool wxSafeArrayBase::Unlock()
{
    wxCHECK_MSG( m_array, false, wxS("Uninitialized safe array") );

    HRESULT hr = SafeArrayUnlock(m_array);
    if ( FAILED(hr) )
    {
        wxLogApiError(wxS("SafeArrayUnlock()"), hr);
        return false;
    }
    return true;
}
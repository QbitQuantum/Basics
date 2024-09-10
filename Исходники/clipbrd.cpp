void wxClipboard::Clear()
{
#if wxUSE_OLE_CLIPBOARD
    if (m_lastDataObject)
    {
        // don't touch data set by other applications
        HRESULT hr = OleIsCurrentClipboard(m_lastDataObject);
        if (S_OK == hr)
        {
            hr = OleSetClipboard(NULL);
            if ( FAILED(hr) )
            {
                wxLogApiError(wxT("OleSetClipboard(NULL)"), hr);
            }
        }
        m_lastDataObject = NULL;
    }
#endif // wxUSE_OLE_CLIPBOARD
}
STDMETHODIMP FbTooltip::put_Text(BSTR text)
{
    TRACK_FUNCTION();

    if (!text) return E_INVALIDARG;

    // realloc string
    SysReAllocString(&m_tip_buffer, text);
    m_ti.lpszText = m_tip_buffer;
    SendMessage(m_wndtooltip, TTM_SETTOOLINFO, 0, (LPARAM)&m_ti);
    return S_OK;
}
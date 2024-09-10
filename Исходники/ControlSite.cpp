// Unsubscribe event sink from the control
HRESULT CControlSite::Unadvise(const IID &iid, DWORD dwCookie)
{
    if (m_spObject == NULL)
    {
        return E_UNEXPECTED;
    }

    return AtlUnadvise(m_spObject, iid, dwCookie);
}
STDMETHODIMP DHCrst::SetSpinCount(DWORD dwSpinCount)
{
    _ASSERTE(m_pCrst && "Expected a non-null critical section here");

    SetCriticalSectionSpinCount(m_pCrst, dwSpinCount);
    // TODO: retval transformation

    return S_OK;
}
STDMETHODIMP CManagedDebugSessionService::OnShutdown()
{
    if (m_dwAdvice)
    {
        RETURN_IF_FAILED(AtlUnadvise(m_pDebugSessionService, IID_IDebugSessionServiceEvents, m_dwAdvice));
        m_dwAdvice = 0;
    }
    return S_OK;
}
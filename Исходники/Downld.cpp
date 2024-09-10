void CImpCEDL::DestroyEvntSink(void)
{
    if(m_pEvents) {
        HRESULT hr = AtlUnadvise(GetUnknown(),IID_IDLEvents, m_dwEvents);
        
        m_pEvents->Release();
        m_pEvents = NULL;            
    }

}
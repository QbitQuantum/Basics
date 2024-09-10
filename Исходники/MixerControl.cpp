STDMETHODIMP CMixerControl::GetText(long id, BSTR *pVal)
{
    if(!pVal) return E_POINTER;
    if(!(m_mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)) return MIX_E_WRONGTYPE;
    if((id < 0) || (id >= (long)m_mc.cMultipleItems)) return E_INVALIDARG;

    *pVal = T2BSTR(m_pStrings[id].szName);

	return S_OK;
}
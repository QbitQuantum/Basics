HRESULT
CEnumConnectionPoints::GetInterface(REFIID riid, IUnknown** ppUnknown)
{
  LOGCALL (("CEnumConnectionPoints::GetInterface(%s)\n", STRINGFROMGUID (riid)));

  IUnknown* pUnknown = NULL;
  if (riid == IID_IEnumConnectionPoints)
    pUnknown = static_cast<IEnumConnectionPoints*>(this);
  else if (riid == IID_IMarshal)
    {
      CriticalSection critical_section(this);
      if (m_pUnkFTM == NULL)
	CoCreateFreeThreadedMarshaler(GetControllingUnknown(), &m_pUnkFTM);
      if (m_pUnkFTM != NULL)
	return m_pUnkFTM->QueryInterface(riid, (void**) ppUnknown);
    }
  if (pUnknown == NULL)
    return E_NOINTERFACE;

  *ppUnknown = pUnknown;
  return S_OK;
}
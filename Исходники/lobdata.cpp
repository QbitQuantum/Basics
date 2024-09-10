HRESULT
CGetDataSequentialStream::GetInterface(REFIID riid, IUnknown** ppUnknown)
{
  LOGCALL (("CGetDataSequentialStream::GetInterface(%s)\n", STRINGFROMGUID (riid)));

  IUnknown* pUnknown = NULL;
  if (riid == IID_ISequentialStream)
    pUnknown = static_cast<ISequentialStream*>(this);
  else if (riid == IID_ISupportErrorInfo)
    pUnknown = static_cast<ISupportErrorInfo*>(this);
  else if (riid == IID_IMarshal)
    {
      CriticalSection critical_section(m_pStreamSync);
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
STDMETHODIMP CJavaObject::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
                                        UINT cNames, LCID lcid, DISPID* rgdispid)
{
  USES_CONVERSION;
  // Stack-allocated
  return GetDispID(OLE2BSTR(*rgszNames), 0, rgdispid);
}
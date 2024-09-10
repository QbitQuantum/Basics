// MzObj's Invoke()
static ULONG STDMETHODCALLTYPE Invoke(IMzObj *com_obj, DISPID dispid, REFIID riid, LCID lcid, WORD wFlags,
                                      DISPPARAMS *params, VARIANT *result, EXCEPINFO *pexcepinfo, 
                                      UINT *puArgErr)
{
  // We implement only a "default" interface
  if (!IsEqualIID(riid, &IID_NULL))
    return(DISP_E_UNKNOWNINTERFACE);

  // We need our type lib's TYPEINFO (to pass to DispInvoke)
  if (!MyTypeInfo)
    {
      register HRESULT	hr;

      if ((hr = loadMyTypeInfo())) return(hr);
    }

  // Let OLE32.DLL's DispInvoke() do all the real work of calling the appropriate
  // function in our object, and massaging the passed args into the correct format
  return(DispInvoke(com_obj, MyTypeInfo, dispid, wFlags, params, result, pexcepinfo, puArgErr));
}
STDMETHODIMP TCUtilImpl::ObjectReference(IUnknown* pUnk,
  BSTR* pbstrObjectReference)
{
  // Initialize the [out] parameter
  CLEAROUT(pbstrObjectReference, (BSTR)NULL);

  // Create the object reference moniker
  IMonikerPtr spMoniker;
  RETURN_FAILED(CreateObjrefMoniker(pUnk, &spMoniker));

  // Create a binding context
  IBindCtxPtr spbc;
  RETURN_FAILED(CreateBindCtx(0, &spbc));

  // Get the displayable name of the moniker
  TCCoTaskPtr<LPOLESTR> spszDisplayName;
  RETURN_FAILED(spMoniker->GetDisplayName(spbc, NULL, &spszDisplayName));

  // Create a BSTR from the display name
  *pbstrObjectReference = SysAllocString(spszDisplayName);

  // Indicate success or failure
  return *pbstrObjectReference ? S_OK : E_OUTOFMEMORY;
}
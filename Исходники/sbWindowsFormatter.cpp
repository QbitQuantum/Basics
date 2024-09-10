STDMETHODIMP
sbWindowsFormatter::QueryInterface(REFIID aIID,
                                   void** aInterface)
{
  // Validate arguments.
  if (IsBadWritePtr(aInterface, sizeof(void*)))
    return E_POINTER;

  // Initialize interface to null.
  *aInterface = NULL;

  // Return requested interface.
  if (InlineIsEqualGUID(aIID, IID_IUnknown))
    *aInterface = static_cast<IUnknown*>(this);
  else if (InlineIsEqualGUID(aIID, IID_sbIWindowsFormatter))
    *aInterface = static_cast<sbIWindowsFormatter*>(this);
  else
    return E_NOINTERFACE;

  // Add a reference to the interface.
  (static_cast<IUnknown*>(*aInterface))->AddRef();

  return S_OK;
}
bool VideoCaptureDeviceImpl::initName() {
  if (!m_pMoniker) {
    return false;
  }
  IBindCtx* pBindContext = 0;
  HRESULT result = CreateBindCtx(0, &pBindContext);
  if (FAILED(result)) {
    return false;
  }
  IBindCtxSharedPtr bindContextPtr(comInterfaceSharedPtr(pBindContext));
  if (!bindContextPtr) {
    return false;
  }

  IPropertyBag* pPropertyBag = 0;
  result = m_pMoniker->BindToStorage(
      bindContextPtr.get(),
      0,
      IID_IPropertyBag,
      reinterpret_cast<void**>(&pPropertyBag));
  if (FAILED(result)) {
    return false;
  }
  IPropertyBagSharedPtr propertyBagPtr(comInterfaceSharedPtr(pPropertyBag));
  if (!propertyBagPtr) {
    return false;
  }

  VARIANT variant;
  VariantSharedPtr variantPtr(variantSharedPtr(&variant));
  result = propertyBagPtr->Read(s_kFriendlyName.c_str(), variantPtr.get(), 0);
  if (FAILED(result)) {
    return false;
  }

  const BSTR basicString = variantPtr->bstrVal;
  if (!basicString) {
    return false;
  }
  std::string friendlyName(utf8StringFromBasicString(basicString));
  m_name = friendlyName;
  return true;
}
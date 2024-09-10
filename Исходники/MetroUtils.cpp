HRESULT MetroUtils::CreateUri(HSTRING aUriStr, ComPtr<IUriRuntimeClass>& aUriOut)
{
  HRESULT hr;
  ComPtr<IUriRuntimeClassFactory> uriFactory;
  hr = GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriFactory);
  AssertRetHRESULT(hr, hr);
  ComPtr<IUriRuntimeClass> uri;
  return uriFactory->CreateUri(aUriStr, &aUriOut);
}
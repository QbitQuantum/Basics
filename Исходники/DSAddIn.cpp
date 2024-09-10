// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
  pIApp_.Release();
  CoRevokeClassObject( classRegistrationId_);

	return S_OK;
}
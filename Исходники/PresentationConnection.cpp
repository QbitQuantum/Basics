void
PresentationConnection::Send(const ArrayBuffer& aData,
                             ErrorResult& aRv)
{
  if (NS_WARN_IF(mState != PresentationConnectionState::Connected)) {
    aRv.Throw(NS_ERROR_DOM_INVALID_STATE_ERR);
    return;
  }

  nsCOMPtr<nsIPresentationService> service =
    do_GetService(PRESENTATION_SERVICE_CONTRACTID);
  if(NS_WARN_IF(!service)) {
    AsyncCloseConnectionWithErrorMsg(
      NS_LITERAL_STRING("Unable to send message due to an internal error."));
    return;
  }

  aData.ComputeLengthAndData();

  static_assert(sizeof(*aData.Data()) == 1, "byte-sized data required");

  uint32_t length = aData.Length();
  char* data = reinterpret_cast<char*>(aData.Data());
  nsDependentCSubstring msgString(data, length);

  nsresult rv = service->SendSessionBinaryMsg(mId, mRole, msgString);
  if(NS_WARN_IF(NS_FAILED(rv))) {
    AsyncCloseConnectionWithErrorMsg(
      NS_LITERAL_STRING("Unable to send binary message for ArrayBuffer message."));
  }
}
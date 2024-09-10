HRESULT PipeStream::GetClientSessionId(ULONG* session_id) {
  if (session_id == nullptr)
    return E_INVALIDARG;
  if (!IsValid())
    return E_HANDLE;

  if (!GetNamedPipeClientSessionId(handle_, session_id))
    return HRESULT_FROM_LAST_ERROR();

  return S_OK;
}
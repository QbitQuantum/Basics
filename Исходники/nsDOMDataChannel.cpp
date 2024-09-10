void
nsDOMDataChannel::Send(const ArrayBuffer& aData, ErrorResult& aRv)
{
  MOZ_ASSERT(NS_IsMainThread(), "Not running on main thread");

  aData.ComputeLengthAndData();

  static_assert(sizeof(*aData.Data()) == 1, "byte-sized data required");

  uint32_t len = aData.Length();
  char* data = reinterpret_cast<char*>(aData.Data());

  nsDependentCSubstring msgString(data, len);
  Send(nullptr, msgString, len, true, aRv);
}
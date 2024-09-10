// static
already_AddRefed<nsIInputStream>
FileHandleBase::GetInputStream(const ArrayBuffer& aValue,
                               uint64_t* aInputLength, ErrorResult& aRv)
{
  aValue.ComputeLengthAndData();
  const char* data = reinterpret_cast<const char*>(aValue.Data());
  uint32_t length = aValue.Length();

  nsCOMPtr<nsIInputStream> stream;
  aRv = NS_NewByteInputStream(getter_AddRefs(stream), data, length,
                              NS_ASSIGNMENT_COPY);
  if (aRv.Failed()) {
    return nullptr;
  }

  *aInputLength = length;
  return stream.forget();
}
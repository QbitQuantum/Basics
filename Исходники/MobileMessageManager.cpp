already_AddRefed<DOMRequest>
MobileMessageManager::Delete(const Sequence<OwningLongOrSmsMessageOrMmsMessage>& aParams,
                             ErrorResult& aRv)
{
  const uint32_t size = aParams.Length();
  FallibleTArray<int32_t> idArray;
  if (!idArray.SetLength(size, fallible)) {
    aRv.Throw(NS_ERROR_OUT_OF_MEMORY);
    return nullptr;
  }

  DebugOnly<nsresult> rv;
  for (uint32_t i = 0; i < size; i++) {
    const OwningLongOrSmsMessageOrMmsMessage& element = aParams[i];
    int32_t &id = idArray[i];

    if (element.IsLong()) {
      id = element.GetAsLong();
    } else if (element.IsMmsMessage()) {
      id = element.GetAsMmsMessage()->Id();
    } else /*if (element.IsSmsMessage())*/ {
      id = element.GetAsSmsMessage()->Id();
    }
  }

  return Delete(idArray.Elements(), size, aRv);
}
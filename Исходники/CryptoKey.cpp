bool
CryptoKey::AllUsagesRecognized(const Sequence<nsString>& aUsages)
{
  for (uint32_t i = 0; i < aUsages.Length(); ++i) {
    if (!IsRecognizedUsage(aUsages[i])) {
      return false;
    }
  }
  return true;
}
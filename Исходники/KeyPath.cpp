// static
nsresult KeyPath::Parse(const Sequence<nsString>& aStrings, KeyPath* aKeyPath) {
  KeyPath keyPath(0);
  keyPath.SetType(ARRAY);

  for (uint32_t i = 0; i < aStrings.Length(); ++i) {
    if (!keyPath.AppendStringWithValidation(aStrings[i])) {
      return NS_ERROR_FAILURE;
    }
  }

  *aKeyPath = keyPath;
  return NS_OK;
}
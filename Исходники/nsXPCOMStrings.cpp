NS_CStringSetDataRange(nsACString& aStr,
                       uint32_t aCutOffset, uint32_t aCutLength,
                       const char* aData, uint32_t aDataLength)
{
  if (aCutOffset == UINT32_MAX) {
    // append case
    if (aData) {
      aStr.Append(aData, aDataLength);
    }
    return NS_OK; // XXX report errors
  }

  if (aCutLength == UINT32_MAX) {
    aCutLength = aStr.Length() - aCutOffset;
  }

  if (aData) {
    if (aDataLength == UINT32_MAX) {
      aStr.Replace(aCutOffset, aCutLength, nsDependentCString(aData));
    } else {
      aStr.Replace(aCutOffset, aCutLength, Substring(aData, aDataLength));
    }
  } else {
    aStr.Cut(aCutOffset, aCutLength);
  }

  return NS_OK; // XXX report errors
}
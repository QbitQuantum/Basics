nsCString
ToHexString(const nsTArray<uint8_t>& aBytes)
{
  return ToHexString(aBytes.Elements(), aBytes.Length());
}
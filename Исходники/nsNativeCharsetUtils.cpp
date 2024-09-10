nsresult
NS_CopyNativeToUnicode(const nsACString& aInput, nsAString& aOutput)
{
  uint32_t inputLen = aInput.Length();

  nsACString::const_iterator iter;
  aInput.BeginReading(iter);

  const char* buf = iter.get();

  // determine length of result
  uint32_t resultLen = 0;
  int n = ::MultiByteToWideChar(CP_ACP, 0, buf, inputLen, nullptr, 0);
  if (n > 0) {
    resultLen += n;
  }

  // allocate sufficient space
  if (!aOutput.SetLength(resultLen, fallible)) {
    return NS_ERROR_OUT_OF_MEMORY;
  }
  if (resultLen > 0) {
    nsAString::iterator out_iter;
    aOutput.BeginWriting(out_iter);

    char16_t* result = out_iter.get();

    ::MultiByteToWideChar(CP_ACP, 0, buf, inputLen, wwc(result), resultLen);
  }
  return NS_OK;
}
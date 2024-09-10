bool nsMediaFragmentURIParser::ParseNPTSS(nsDependentSubstring& aString, uint32_t& aSecond)
{
  if (aString.Length() < 2) {
    return false;
  }

  if (IsDigit(aString[0]) && IsDigit(aString[1])) {
    nsDependentSubstring n(aString, 0, 2);
    nsresult ec;
    int32_t u = PromiseFlatString(n).ToInteger(&ec);
    if (NS_FAILED(ec)) {
      return false;
    }

    aString.Rebind(aString, 2);
    if (u >= 60)
      return false;

    aSecond = u;
    return true;
  }

  return false;
}
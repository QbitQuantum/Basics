bool
StringEndsWith(const nsACString& aSource, const nsACString& aSubstring)
{
  nsACString::size_type src_len = aSource.Length(),
                        sub_len = aSubstring.Length();
  if (sub_len > src_len) {
    return false;
  }
  return Substring(aSource, src_len - sub_len, sub_len).Equals(aSubstring);
}
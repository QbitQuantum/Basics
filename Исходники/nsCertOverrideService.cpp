void
nsCertOverride::convertStringToBits(const nsACString& str,
                            /*out*/ OverrideBits& ob)
{
  ob = OverrideBits::None;

  for (uint32_t i = 0; i < str.Length(); i++) {
    switch (str.CharAt(i)) {
      case 'm':
      case 'M':
        ob |= OverrideBits::Mismatch;
        break;

      case 'u':
      case 'U':
        ob |= OverrideBits::Untrusted;
        break;

      case 't':
      case 'T':
        ob |= OverrideBits::Time;
        break;

      default:
        break;
    }
  }
}
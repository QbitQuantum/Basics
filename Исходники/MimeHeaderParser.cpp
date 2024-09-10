void ExtractName(const nsCOMArray<msgIAddressObject> &aHeader,
                 nsAString &name) {
  AutoTArray<nsString, 1> names;
  AutoTArray<nsString, 1> emails;
  ExtractAllAddresses(aHeader, names, emails);
  if (names.Length() > 0) {
    if (names[0].IsEmpty())
      name = emails[0];
    else
      name = names[0];
  } else {
    name.Truncate();
  }
}
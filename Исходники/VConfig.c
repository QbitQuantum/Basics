/**
  Extract the decimal index from the network interface name.

  @param[in]  Name           Name of the network interface.

  @retval INVALID_NIC_INDEX  Failed to extract the network interface index.
  @return others             The network interface index.

**/
UINTN
NicNameToIndex (
  IN CHAR16                   *Name
  )
{
  CHAR16  *Str;

  Str = Name + 3;
  if ((StrnCmp (Name, L"eth", 3) != 0) || (*Str == 0)) {
    return INVALID_NIC_INDEX;
  }

  while (*Str != 0) {
    if ((*Str < L'0') || (*Str > L'9')) {
      return INVALID_NIC_INDEX;
    }

    Str++;
  }

  return (UINT16) StrDecimalToUintn (Name + 3);
}
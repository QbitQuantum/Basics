void
Dacl::AddAllowedAce(const Sid& aSid, ACCESS_MASK aAccessMask)
{
  return AddAce(aSid, GRANT_ACCESS, aAccessMask);
}
//
/// Merges the functional groups of another menu descriptor into this menu
/// descriptor.
///
/// Popups are DeepCopied and are then owned by this menu
/// Group counts are merged too.
//
bool
TMenuDescr::Merge(const TMenuDescr& srcMenuDescr)
{
  int thisOffset = 0;
  int srcOffset = 0;

  for (int i = 0; i < NumGroups; i++) {
    if (srcMenuDescr.GroupCount[i] != 0) {
      // Delete same menu group in the dest. menudescr.
      for (int j = GroupCount[i] - 1; j >= 0; j--) {
        DeleteMenu(thisOffset+j, MF_BYPOSITION);
      }
      GroupCount[i] = 0;

      if (srcMenuDescr.GroupCount[i] > 0) {
        DeepCopy(*this, thisOffset, srcMenuDescr, srcOffset, srcMenuDescr.GroupCount[i]);
        srcOffset += srcMenuDescr.GroupCount[i];
        GroupCount[i] += srcMenuDescr.GroupCount[i];
      }
    }

    if (GroupCount[i] > 0)
      thisOffset += GroupCount[i];
  }
  return true;
}
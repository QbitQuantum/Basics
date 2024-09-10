NS_IMETHODIMP nsPrefBranch::GetChildList(const char *aStartingAt, uint32_t *aCount, char ***aChildArray)
{
  char            **outArray;
  int32_t         numPrefs;
  int32_t         dwIndex;
  AutoTArray<nsCString, 32> prefArray;

  NS_ENSURE_ARG(aStartingAt);
  NS_ENSURE_ARG_POINTER(aCount);
  NS_ENSURE_ARG_POINTER(aChildArray);

  *aChildArray = nullptr;
  *aCount = 0;

  // this will contain a list of all the pref name strings
  // allocate on the stack for speed

  const char* parent = getPrefName(aStartingAt);
  size_t parentLen = strlen(parent);
  for (auto iter = gHashTable->Iter(); !iter.Done(); iter.Next()) {
    auto entry = static_cast<PrefHashEntry*>(iter.Get());
    if (strncmp(entry->key, parent, parentLen) == 0) {
      prefArray.AppendElement(entry->key);
    }
  }

  // now that we've built up the list, run the callback on
  // all the matching elements
  numPrefs = prefArray.Length();

  if (numPrefs) {
    outArray = (char **)moz_xmalloc(numPrefs * sizeof(char *));
    if (!outArray)
      return NS_ERROR_OUT_OF_MEMORY;

    for (dwIndex = 0; dwIndex < numPrefs; ++dwIndex) {
      // we need to lop off mPrefRoot in case the user is planning to pass this
      // back to us because if they do we are going to add mPrefRoot again.
      const nsCString& element = prefArray[dwIndex];
      outArray[dwIndex] = (char *)nsMemory::Clone(
        element.get() + mPrefRootLength, element.Length() - mPrefRootLength + 1);

      if (!outArray[dwIndex]) {
        // we ran out of memory... this is annoying
        NS_FREE_XPCOM_ALLOCATED_POINTER_ARRAY(dwIndex, outArray);
        return NS_ERROR_OUT_OF_MEMORY;
      }
    }
    *aChildArray = outArray;
  }
  *aCount = numPrefs;

  return NS_OK;
}
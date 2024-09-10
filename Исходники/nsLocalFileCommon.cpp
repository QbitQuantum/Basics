NS_IMETHODIMP
nsLocalFile::CreateUnique(uint32_t aType, uint32_t aAttributes)
{
  nsresult rv;
  bool longName;

#ifdef XP_WIN
  nsAutoString pathName, leafName, rootName, suffix;
  rv = GetPath(pathName);
#else
  nsAutoCString pathName, leafName, rootName, suffix;
  rv = GetNativePath(pathName);
#endif
  if (NS_FAILED(rv)) {
    return rv;
  }

  longName = (pathName.Length() + kMaxSequenceNumberLength >
              kMaxFilenameLength);
  if (!longName) {
    rv = Create(aType, aAttributes);
    if (rv != NS_ERROR_FILE_ALREADY_EXISTS) {
      return rv;
    }
  }

#ifdef XP_WIN
  rv = GetLeafName(leafName);
  if (NS_FAILED(rv)) {
    return rv;
  }

  const int32_t lastDot = leafName.RFindChar(char16_t('.'));
#else
  rv = GetNativeLeafName(leafName);
  if (NS_FAILED(rv)) {
    return rv;
  }

  const int32_t lastDot = leafName.RFindChar('.');
#endif

  if (lastDot == kNotFound) {
    rootName = leafName;
  } else {
    suffix = Substring(leafName, lastDot);      // include '.'
    rootName = Substring(leafName, 0, lastDot); // strip suffix and dot
  }

  if (longName) {
    int32_t maxRootLength = (kMaxFilenameLength -
                             (pathName.Length() - leafName.Length()) -
                             suffix.Length() - kMaxSequenceNumberLength);

    // We cannot create an item inside a directory whose name is too long.
    // Also, ensure that at least one character remains after we truncate
    // the root name, as we don't want to end up with an empty leaf name.
    if (maxRootLength < 2) {
      return NS_ERROR_FILE_UNRECOGNIZED_PATH;
    }

#ifdef XP_WIN
    // ensure that we don't cut the name in mid-UTF16-character
    rootName.SetLength(NS_IS_LOW_SURROGATE(rootName[maxRootLength]) ?
                       maxRootLength - 1 : maxRootLength);
    SetLeafName(rootName + suffix);
#else
    if (NS_IsNativeUTF8()) {
      // ensure that we don't cut the name in mid-UTF8-character
      // (assume the name is valid UTF8 to begin with)
      while (UTF8traits::isInSeq(rootName[maxRootLength])) {
        --maxRootLength;
      }

      // Another check to avoid ending up with an empty leaf name.
      if (maxRootLength == 0 && suffix.IsEmpty()) {
        return NS_ERROR_FILE_UNRECOGNIZED_PATH;
      }
    }

    rootName.SetLength(maxRootLength);
    SetNativeLeafName(rootName + suffix);
#endif
    nsresult rvCreate = Create(aType, aAttributes);
    if (rvCreate != NS_ERROR_FILE_ALREADY_EXISTS) {
      return rvCreate;
    }
  }

  for (int indx = 1; indx < 10000; ++indx) {
    // start with "Picture-1.jpg" after "Picture.jpg" exists
#ifdef XP_WIN
    SetLeafName(rootName +
                NS_ConvertASCIItoUTF16(nsPrintfCString("-%d", indx)) +
                suffix);
#else
    SetNativeLeafName(rootName + nsPrintfCString("-%d", indx) + suffix);
#endif
    rv = Create(aType, aAttributes);
    if (NS_SUCCEEDED(rv) || rv != NS_ERROR_FILE_ALREADY_EXISTS) {
      return rv;
    }
  }

  // The disk is full, sort of
  return NS_ERROR_FILE_TOO_BIG;
}
/* Find and parse the SystemVersion.plist file. */
static void parseSystemVersionPList(void *Unused) {
  (void)Unused;
  /* Load CoreFoundation dynamically */
  const void *NullAllocator = dlsym(RTLD_DEFAULT, "kCFAllocatorNull");
  if (!NullAllocator)
    return;
  const CFAllocatorRef AllocatorNull = *(const CFAllocatorRef *)NullAllocator;
  CFDataCreateWithBytesNoCopyFuncTy CFDataCreateWithBytesNoCopyFunc =
      (CFDataCreateWithBytesNoCopyFuncTy)dlsym(RTLD_DEFAULT,
                                               "CFDataCreateWithBytesNoCopy");
  if (!CFDataCreateWithBytesNoCopyFunc)
    return;
  CFPropertyListCreateWithDataFuncTy CFPropertyListCreateWithDataFunc =
      (CFPropertyListCreateWithDataFuncTy)dlsym(
          RTLD_DEFAULT, "CFPropertyListCreateWithData");
/* CFPropertyListCreateWithData was introduced only in macOS 10.6+, so it
 * will be NULL on earlier OS versions. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  CFPropertyListCreateFromXMLDataFuncTy CFPropertyListCreateFromXMLDataFunc =
      (CFPropertyListCreateFromXMLDataFuncTy)dlsym(
          RTLD_DEFAULT, "CFPropertyListCreateFromXMLData");
#pragma clang diagnostic pop
  /* CFPropertyListCreateFromXMLDataFunc is deprecated in macOS 10.10, so it
   * might be NULL in future OS versions. */
  if (!CFPropertyListCreateWithDataFunc && !CFPropertyListCreateFromXMLDataFunc)
    return;
  CFStringCreateWithCStringNoCopyFuncTy CFStringCreateWithCStringNoCopyFunc =
      (CFStringCreateWithCStringNoCopyFuncTy)dlsym(
          RTLD_DEFAULT, "CFStringCreateWithCStringNoCopy");
  if (!CFStringCreateWithCStringNoCopyFunc)
    return;
  CFDictionaryGetValueFuncTy CFDictionaryGetValueFunc =
      (CFDictionaryGetValueFuncTy)dlsym(RTLD_DEFAULT, "CFDictionaryGetValue");
  if (!CFDictionaryGetValueFunc)
    return;
  CFGetTypeIDFuncTy CFGetTypeIDFunc =
      (CFGetTypeIDFuncTy)dlsym(RTLD_DEFAULT, "CFGetTypeID");
  if (!CFGetTypeIDFunc)
    return;
  CFStringGetTypeIDFuncTy CFStringGetTypeIDFunc =
      (CFStringGetTypeIDFuncTy)dlsym(RTLD_DEFAULT, "CFStringGetTypeID");
  if (!CFStringGetTypeIDFunc)
    return;
  CFStringGetCStringFuncTy CFStringGetCStringFunc =
      (CFStringGetCStringFuncTy)dlsym(RTLD_DEFAULT, "CFStringGetCString");
  if (!CFStringGetCStringFunc)
    return;
  CFReleaseFuncTy CFReleaseFunc =
      (CFReleaseFuncTy)dlsym(RTLD_DEFAULT, "CFRelease");
  if (!CFReleaseFunc)
    return;

  char *PListPath = "/System/Library/CoreServices/SystemVersion.plist";

#if TARGET_OS_SIMULATOR
  char *PListPathPrefix = getenv("IPHONE_SIMULATOR_ROOT");
  if (!PListPathPrefix)
    return;
  char FullPath[strlen(PListPathPrefix) + strlen(PListPath) + 1];
  strcpy(FullPath, PListPathPrefix);
  strcat(FullPath, PListPath);
  PListPath = FullPath;
#endif
  FILE *PropertyList = fopen(PListPath, "r");
  if (!PropertyList)
    return;

  /* Dynamically allocated stuff. */
  CFDictionaryRef PListRef = NULL;
  CFDataRef FileContentsRef = NULL;
  UInt8 *PListBuf = NULL;

  fseek(PropertyList, 0, SEEK_END);
  long PListFileSize = ftell(PropertyList);
  if (PListFileSize < 0)
    goto Fail;
  rewind(PropertyList);

  PListBuf = malloc((size_t)PListFileSize);
  if (!PListBuf)
    goto Fail;

  size_t NumRead = fread(PListBuf, 1, (size_t)PListFileSize, PropertyList);
  if (NumRead != (size_t)PListFileSize)
    goto Fail;

  /* Get the file buffer into CF's format. We pass in a null allocator here *
   * because we free PListBuf ourselves */
  FileContentsRef = (*CFDataCreateWithBytesNoCopyFunc)(
      NULL, PListBuf, (CFIndex)NumRead, AllocatorNull);
  if (!FileContentsRef)
    goto Fail;

  if (CFPropertyListCreateWithDataFunc)
    PListRef = (*CFPropertyListCreateWithDataFunc)(
        NULL, FileContentsRef, CF_PROPERTY_LIST_IMMUTABLE, NULL, NULL);
  else
    PListRef = (*CFPropertyListCreateFromXMLDataFunc)(
        NULL, FileContentsRef, CF_PROPERTY_LIST_IMMUTABLE, NULL);
  if (!PListRef)
    goto Fail;

  CFStringRef ProductVersion = (*CFStringCreateWithCStringNoCopyFunc)(
      NULL, "ProductVersion", CF_STRING_ENCODING_ASCII, AllocatorNull);
  if (!ProductVersion)
    goto Fail;
  CFTypeRef OpaqueValue = (*CFDictionaryGetValueFunc)(PListRef, ProductVersion);
  (*CFReleaseFunc)(ProductVersion);
  if (!OpaqueValue ||
      (*CFGetTypeIDFunc)(OpaqueValue) != (*CFStringGetTypeIDFunc)())
    goto Fail;

  char VersionStr[32];
  if (!(*CFStringGetCStringFunc)((CFStringRef)OpaqueValue, VersionStr,
                                 sizeof(VersionStr), CF_STRING_ENCODING_UTF8))
    goto Fail;
  sscanf(VersionStr, "%d.%d.%d", &GlobalMajor, &GlobalMinor, &GlobalSubminor);

Fail:
  if (PListRef)
    (*CFReleaseFunc)(PListRef);
  if (FileContentsRef)
    (*CFReleaseFunc)(FileContentsRef);
  free(PListBuf);
  fclose(PropertyList);
}
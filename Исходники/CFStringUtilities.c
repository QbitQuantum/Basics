Boolean
CFStringFindWithOptionsAndLocale (CFStringRef str,
                                  CFStringRef stringToFind,
                                  CFRange rangeToSearch,
                                  CFStringCompareFlags searchOptions,
                                  CFLocaleRef locale, CFRange *result)
{
  UniChar *pattern;
  UniChar *text;
  CFIndex patternLength;
  CFIndex textLength;
  CFIndex start;
  CFIndex end;
  CFAllocatorRef alloc;
  UCollator *ucol;
  UStringSearch *usrch;
  UErrorCode err = U_ZERO_ERROR;
  
  if (rangeToSearch.length == 0)
    return false;
  
  alloc = CFAllocatorGetDefault ();
  textLength = CFStringGetLength (stringToFind);
  if (textLength == 0)
    return false;
  
  patternLength = rangeToSearch.length;
  pattern = CFAllocatorAllocate (alloc, patternLength * sizeof(UniChar), 0);
  CFStringGetCharacters (str, rangeToSearch, pattern);
  
  text = CFAllocatorAllocate (alloc, textLength * sizeof(UniChar), 0);
  CFStringGetCharacters (stringToFind, CFRangeMake(0, textLength), text);
  
  ucol = CFStringICUCollatorOpen (searchOptions, locale);
  usrch = usearch_openFromCollator (text, textLength, pattern, patternLength,
                                    ucol, NULL, &err);
  if (U_FAILURE(err))
    return false;
  
  /* FIXME: need to handle kCFCompareAnchored */
  if (searchOptions & kCFCompareBackwards)
    {
      start = usearch_last (usrch, &err);
    }
  else
    {
      start = usearch_first (usrch, &err);
    }
  if (start == USEARCH_DONE)
    {
      CFAllocatorDeallocate (alloc, pattern);
      CFAllocatorDeallocate (alloc, text);
      return false;
    }
  end = usearch_getMatchedLength (usrch);
  usearch_close (usrch);
  CFStringICUCollatorClose (ucol);
  
  if (result)
    *result = CFRangeMake (start + rangeToSearch.location, end);
  
  CFAllocatorDeallocate (alloc, pattern);
  CFAllocatorDeallocate (alloc, text);
  return true;
}
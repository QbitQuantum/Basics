void GLUTAPIENTRY
glutGameModeString(const char *string)
{
  Criterion *criteria;
  int ncriteria[4], requestedMask, queries = 1;
#if _WIN32
  int bpp, width, height, hertz, n;
#endif

  initGameModeSupport();
#if _WIN32
  XHDC = GetDC(GetDesktopWindow());
  bpp = GetDeviceCaps(XHDC, BITSPIXEL);
  /* Note that Windows 95 and 98 systems always return zero
     for VREFRESH so be prepared to ignore values of hertz
     that are too low. */
  hertz = GetDeviceCaps(XHDC, VREFRESH);
  width = GetSystemMetrics(SM_CXSCREEN);
  height = GetSystemMetrics(SM_CYSCREEN);
#endif
  criteria = parseGameModeString(string, &ncriteria[0], &requestedMask);

#if _WIN32
  /* Build an extra set of default queries.  If no pixel depth is
     explicitly specified, prefer a display mode that doesn't change
     the display mode.  Likewise for the width and height.  Likewise for
     the display frequency. */
  n = ncriteria[0];
  if (!(requestedMask & (1 << DM_PIXEL_DEPTH))) {
    criteria[n].capability = DM_PIXEL_DEPTH;
    criteria[n].comparison = EQ;
    criteria[n].value = bpp;
    n += 1;
    ncriteria[queries] = n;
    queries++;
  }
  if (!(requestedMask & ((1<<DM_WIDTH) | (1<<DM_HEIGHT)) )) {
    criteria[n].capability = DM_WIDTH;
    criteria[n].comparison = EQ;
    criteria[n].value = width;
    criteria[n].capability = DM_HEIGHT;
    criteria[n].comparison = EQ;
    criteria[n].value = height;
    n += 2;
    ncriteria[queries] = n;
    queries++;
  }
  /* Assume a display frequency of less than 50 is to be ignored. */
  if (hertz >= 50) {
    if (!(requestedMask & (1 << DM_HERTZ))) {
      criteria[n].capability = DM_HERTZ;
      criteria[n].comparison = EQ;
      criteria[n].value = hertz;
      n += 1;
      ncriteria[queries] = n;
      queries++;
    }
  }
#endif

  /* Perform multiple queries until one succeeds or no more queries. */
  do {
    queries--;
    currentDm = findMatch(dmodes, ndmodes, criteria, ncriteria[queries]);
  } while((currentDm == NULL) && (queries > 0));

  free(criteria);
}
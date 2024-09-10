void ZProfile::closeRoot ()
{
  ZFUNCTRACE_DEVELOP ("ZProfile::closeRoot()");
#ifdef ZC_WIN
  if (iRootHandle)
      {
        closePath ();
        closeHandle ((HKEY) iRootHandle);
        iRootHandle = 0;
      }                         // if
#endif
#ifdef ZC_OS2
  if (iRootHandle != 0 &&
      iRootHandle != HINI_SYSTEMPROFILE && iRootHandle != HINI_USERPROFILE)
      {
        if (!PrfCloseProfile (iRootHandle))
          throwSysErr (PrfCloseProfileName);
        iRootHandle = 0;
      }                         // if
#endif
}                               // closeRoot
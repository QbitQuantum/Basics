/**
  function to determine if FullPath is under current filesystem.

  @param[in]    FullPath    The target location to determine.
  @param[in]    Cwd         Current directory.

  @retval       TRUE        The FullPath is in the current filesystem.
  @retval       FALSE       The FullPaht isn't in the current filesystem.
**/
BOOLEAN
IsCurrentFileSystem (
  IN CONST CHAR16   *FullPath,
  IN CONST CHAR16   *Cwd
  )
{
  CHAR16 *Splitter1;
  CHAR16 *Splitter2;

  Splitter1 = NULL;
  Splitter2 = NULL;

  ASSERT(FullPath != NULL);

  Splitter1 = StrStr (FullPath, L":");
  if (Splitter1 == NULL) {
    return TRUE;
  }

  Splitter2 = StrStr (Cwd, L":");

  if (((UINTN) Splitter1 - (UINTN) FullPath) != ((UINTN) Splitter2 - (UINTN) Cwd)) {
    return FALSE;
  } else {
    if (StrniCmp (FullPath, Cwd, ((UINTN) Splitter1 - (UINTN) FullPath) / sizeof (CHAR16)) == NULL) {
      return TRUE;
    } else {
      return FALSE;
    }
  }
}
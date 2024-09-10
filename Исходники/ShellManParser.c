/**
  parses through Buffer (which is MAN file formatted) and returns the
  detailed help for any sub section specified in the comma seperated list of
  sections provided.  If the end of the file or a .TH section is found then
  return.

  Upon a sucessful return the caller is responsible to free the memory in *HelpText

  @param[in] Buffer             Buffer to read from
  @param[in] Sections           name of command's sub sections to find
  @param[in] HelpText           pointer to pointer to string where text goes.
  @param[in] HelpSize           pointer to size of allocated HelpText (may be updated)

  @retval EFI_OUT_OF_RESOURCES  a memory allocation failed.
  @retval EFI_SUCCESS           the section was found and its description sotred in
                                an alloceted buffer.
**/
EFI_STATUS
EFIAPI
ManBufferFindSections(
  IN CONST CHAR16 *Buffer,
  IN CONST CHAR16 *Sections,
  IN CHAR16       **HelpText,
  IN UINTN        *HelpSize
  )
{
  EFI_STATUS          Status;
  CONST CHAR16        *CurrentLocation;
  BOOLEAN             CurrentlyReading;
  CHAR16              *SectionName;
  UINTN               SectionLen;
  BOOLEAN             Found;
  CHAR16              *TempString;
  CHAR16              *TempString2;

  if ( Buffer     == NULL
    || HelpText   == NULL
    || HelpSize   == NULL
   ){
    return (EFI_INVALID_PARAMETER);
  }

  Status            = EFI_SUCCESS;
  CurrentlyReading  = FALSE;
  Found             = FALSE;

  for (CurrentLocation = Buffer,TempString = NULL
    ;  CurrentLocation != NULL && *CurrentLocation != CHAR_NULL
    ;  CurrentLocation=StrStr(CurrentLocation, L"\r\n"),TempString = NULL
   ){
    while(CurrentLocation[0] == L'\r' || CurrentLocation[0] == L'\n') {
      CurrentLocation++;
    }
    if (CurrentLocation[0] == L'#') {
      //
      // Skip comment lines
      //
      continue;
    }
    if (StrnCmp(CurrentLocation, L".TH", 3) == 0) {
      //
      // we hit the end of this commands section so stop.
      //
      break;
    }
    if (StrnCmp(CurrentLocation, L".SH ", 4) == 0) {
      if (Sections == NULL) {
        CurrentlyReading = TRUE;
        continue;
      } else if (CurrentlyReading) {
        CurrentlyReading = FALSE;
      }
      CurrentLocation += 4;
      //
      // is this a section we want to read in?
      //
      if (StrLen(CurrentLocation)!=0) {
        TempString2 = StrStr(CurrentLocation, L" ");
        TempString2 = MIN(TempString2, StrStr(CurrentLocation, L"\r"));
        TempString2 = MIN(TempString2, StrStr(CurrentLocation, L"\n"));
        ASSERT(TempString == NULL);
        TempString = StrnCatGrow(&TempString, NULL, CurrentLocation, TempString2==NULL?0:TempString2 - CurrentLocation);
        if (TempString == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          break;
        }
        SectionName = TempString;
        SectionLen = StrLen(SectionName);
        SectionName = StrStr(Sections, SectionName);
        if (SectionName == NULL) {
          continue;
        }
        if (*(SectionName + SectionLen) == CHAR_NULL || *(SectionName + SectionLen) == L',') {
          CurrentlyReading = TRUE;
        }
      }
    } else if (CurrentlyReading) {
      Found = TRUE;
      if (StrLen(CurrentLocation)!=0) {
        TempString2 = StrStr(CurrentLocation, L"\r");
        TempString2 = MIN(TempString2, StrStr(CurrentLocation, L"\n"));
        ASSERT(TempString == NULL);
        TempString = StrnCatGrow(&TempString, NULL, CurrentLocation, TempString2==NULL?0:TempString2 - CurrentLocation);
        if (TempString == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          break;
        }
        //
        // copy and save the current line.
        //
        ASSERT((*HelpText == NULL && *HelpSize == 0) || (*HelpText != NULL));
        StrnCatGrow (HelpText, HelpSize, TempString, 0);
        if (HelpText == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          break;
        }
        StrnCatGrow (HelpText, HelpSize, L"\r\n", 0);
        if (HelpText == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          break;
        }
      }
    }
    SHELL_FREE_NON_NULL(TempString);
  }
  if (!Found && !EFI_ERROR(Status)) {
    return (EFI_NOT_FOUND);
  }
  return (Status);
}
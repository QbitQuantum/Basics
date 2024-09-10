/**
  Variable property get with wildcard name.

  @param[in] VariableName       Pointer to variable name.
  @param[in] VendorGuid         Pointer to variable vendor GUID.
  @param[in] WildcardMatch      Try wildcard match or not.

  @return Pointer to variable property.

**/
VAR_CHECK_VARIABLE_PROPERTY *
VariablePropertyGetWithWildcardName (
  IN CHAR16                         *VariableName,
  IN EFI_GUID                       *VendorGuid,
  IN BOOLEAN                        WildcardMatch
  )
{
  UINTN     Index;
  UINTN     NameLength;

  NameLength = StrLen (VariableName) - 4;
  for (Index = 0; Index < sizeof (mVarCheckVariableWithWildcardName)/sizeof (mVarCheckVariableWithWildcardName[0]); Index++) {
    if (CompareGuid (mVarCheckVariableWithWildcardName[Index].Guid, VendorGuid)){
      if (WildcardMatch) {
        if ((StrLen (VariableName) == StrLen (mVarCheckVariableWithWildcardName[Index].Name)) &&
            (StrnCmp (VariableName, mVarCheckVariableWithWildcardName[Index].Name, NameLength) == 0) &&
            VarCheckInternalIsHexaDecimalDigitCharacter (VariableName[NameLength]) &&
            VarCheckInternalIsHexaDecimalDigitCharacter (VariableName[NameLength + 1]) &&
            VarCheckInternalIsHexaDecimalDigitCharacter (VariableName[NameLength + 2]) &&
            VarCheckInternalIsHexaDecimalDigitCharacter (VariableName[NameLength + 3])) {
          return &mVarCheckVariableWithWildcardName[Index].VariableProperty;
        }
      }
      if (StrCmp (mVarCheckVariableWithWildcardName[Index].Name, VariableName) == 0) {
        return  &mVarCheckVariableWithWildcardName[Index].VariableProperty;
      }
    }
  }

  return NULL;
}
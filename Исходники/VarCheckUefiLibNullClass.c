/**
  Get UEFI defined var check function.

  @param[in]  VariableName      Pointer to variable name.
  @param[in]  VendorGuid        Pointer to variable vendor GUID.
  @param[out] VariableProperty  Pointer to variable property.

  @return Internal var check function, NULL if no specific check function.

**/
INTERNAL_VAR_CHECK_FUNCTION
GetUefiDefinedVarCheckFunction (
  IN CHAR16                         *VariableName,
  IN EFI_GUID                       *VendorGuid,
  OUT VAR_CHECK_VARIABLE_PROPERTY   **VariableProperty
  )
{
  UINTN     Index;
  UINTN     NameLength;

  if (CompareGuid (VendorGuid, &gEfiGlobalVariableGuid)) {
    //
    // Try list 1, exactly match.
    //
    for (Index = 0; Index < sizeof (mGlobalVariableList)/sizeof (mGlobalVariableList[0]); Index++) {
      if (StrCmp (mGlobalVariableList[Index].Name, VariableName) == 0) {
        *VariableProperty = &(mGlobalVariableList[Index].VariableProperty);
        return mGlobalVariableList[Index].CheckFunction;
      }
    }

    //
    // Try list 2.
    //
    NameLength = StrLen (VariableName) - 4;
    for (Index = 0; Index < sizeof (mGlobalVariableList2)/sizeof (mGlobalVariableList2[0]); Index++) {
      if ((StrLen (VariableName) == StrLen (mGlobalVariableList2[Index].Name)) &&
          (StrnCmp (VariableName, mGlobalVariableList2[Index].Name, NameLength) == 0) &&
          VarCheckUefiIsHexaDecimalDigitCharacter (VariableName[NameLength]) &&
          VarCheckUefiIsHexaDecimalDigitCharacter (VariableName[NameLength + 1]) &&
          VarCheckUefiIsHexaDecimalDigitCharacter (VariableName[NameLength + 2]) &&
          VarCheckUefiIsHexaDecimalDigitCharacter (VariableName[NameLength + 3])) {
        *VariableProperty = &(mGlobalVariableList2[Index].VariableProperty);
        return mGlobalVariableList2[Index].CheckFunction;
      }
    }
  }

  return NULL;
}
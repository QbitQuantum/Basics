EFI_STATUS
IfrFind (
  IN FORM_BROWSER_FORMSET  *FormSet,
  IN UINT8                 Format,
  OUT  EFI_HII_VALUE       *Result
  )
/*++

Routine Description:
  Evaluate opcode EFI_IFR_FIND.

Arguments:
  FormSet     - Formset which contains this opcode.
  Format      - Case sensitive or insensitive.
  Result      - Evaluation result for this opcode.

Returns:
  EFI_SUCCESS - Opcode evaluation success.
  Other       - Opcode evaluation failed.

--*/
{
  EFI_STATUS     Status;
  EFI_HII_VALUE  Value;
  CHAR16         *String[2];
  UINTN          Base;
  CHAR16         *StringPtr;
  UINTN          Index;

  if (Format > EFI_IFR_FF_CASE_INSENSITIVE) {
    return EFI_UNSUPPORTED;
  }

  Status = PopExpression (&Value);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (Value.Type > EFI_IFR_TYPE_NUM_SIZE_64) {
    return EFI_UNSUPPORTED;
  }
  Base = (UINTN) Value.Value.u64;

  //
  // String[0] - sub-string
  // String[1] - The string to search
  //
  String[0] = NULL;
  String[1] = NULL;
  for (Index = 0; Index < 2; Index++) {
    Status = PopExpression (&Value);
    if (EFI_ERROR (Status)) {
      goto Done;
    }

    if (Value.Type != EFI_IFR_TYPE_STRING) {
      Status = EFI_UNSUPPORTED;
      goto Done;
    }

    String[Index] = GetToken (Value.Value.string, FormSet->HiiHandle);
    if (String== NULL) {
      Status = EFI_NOT_FOUND;
      goto Done;
    }

    if (Format == EFI_IFR_FF_CASE_INSENSITIVE) {
      //
      // Case insensitive, convert both string to upper case
      //
      IfrStrToUpper (String[Index]);
    }
  }

  Result->Type = EFI_IFR_TYPE_NUM_SIZE_64;
  if (Base >= EfiStrLen (String[1])) {
    Result->Value.u64 = 0xFFFFFFFFFFFFFFFF;
  } else {
    StringPtr = EfiStrStr (String[1] + Base, String[0]);
    Result->Value.u64 = (StringPtr == NULL) ? 0xFFFFFFFFFFFFFFFF : (StringPtr - String[1]);
  }

Done:
  EfiLibSafeFreePool (String[0]);
  EfiLibSafeFreePool (String[1]);

  return Status;
}
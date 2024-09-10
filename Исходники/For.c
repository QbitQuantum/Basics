/**
  Determine if a valid string is a valid number for the 'for' command.

  @param[in] Number The pointer to the string representation of the number to test.

  @retval TRUE    The number is valid.
  @retval FALSE   The number is not valid.
**/
BOOLEAN
EFIAPI
ShellIsValidForNumber (
  IN CONST CHAR16 *Number
  )
{
  if (Number == NULL || *Number == CHAR_NULL) {
    return (FALSE);
  }

  if (*Number == L'-') {
    Number++;
  }

  if (StrLen(Number) == 0) {
    return (FALSE);
  }

  if (StrLen(Number) >= 7) {
    if ((StrStr(Number, L" ") == NULL) || (((StrStr(Number, L" ") != NULL) && (StrStr(Number, L" ") - Number) >= 7))) {
      return (FALSE);
    }
  }

  if (!ShellIsDecimalDigitCharacter(*Number)) {
    return (FALSE);
  }

  return (TRUE);
}
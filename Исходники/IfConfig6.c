/**
  Split a string with specified separator and save the substring to a list.

  @param[in]    String       The pointer of the input string.
  @param[in]    Separator    The specified separator.

  @return The pointer of headnode of ARG_LIST.

**/
ARG_LIST *
SplitStrToList (
  IN CONST CHAR16    *String,
  IN CHAR16          Separator
  )
{
  CHAR16      *Str;
  CHAR16      *ArgStr;
  ARG_LIST    *ArgList;
  ARG_LIST    *ArgNode;

  if (*String == L'\0') {
    return NULL;
  }

  //
  // Copy the CONST string to a local copy.
  //
  Str     = (CHAR16 *) AllocateZeroPool (StrSize (String));
  ASSERT (Str != NULL);
  Str     = StrnCpy (Str, String, StrLen (String));
  ArgStr  = Str;

  //
  // init a node for the list head.
  //
  ArgNode = (ARG_LIST *) AllocateZeroPool (sizeof (ARG_LIST));
  ASSERT (ArgNode != NULL);
  ArgList = ArgNode;

  //
  // Split the local copy and save in the list node.
  //
  while (*Str != L'\0') {
    if (*Str == Separator) {
      *Str          = L'\0';
      ArgNode->Arg  = ArgStr;
      ArgStr        = Str + 1;
      ArgNode->Next = (ARG_LIST *) AllocateZeroPool (sizeof (ARG_LIST));
      ASSERT (ArgNode->Next != NULL);
      ArgNode = ArgNode->Next;
    }

    Str++;
  }

  ArgNode->Arg  = ArgStr;
  ArgNode->Next = NULL;

  return ArgList;
}
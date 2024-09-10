NLM_EXTERN Nlm_CharPtr LIBCALL TruncateStringCopy(char FAR *theString, Nlm_Int4 Length)
/* Returns a new string consisting of at most the first length-1 
   characters of theString. */
{
  Nlm_CharPtr NewString = (Nlm_CharPtr)MemNew((size_t)Length);

  StrNCpy(NewString, theString, (size_t)(Length - 1));
  NewString[Length-1] = NULLB;
  return NewString;
}
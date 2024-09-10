/*Extracts the UChar* to a char* and calls through createConverter */
UConverter*  ucnv_openU (const UChar * name,
			 UErrorCode * err)
{
  char asciiName[MAX_CONVERTER_NAME_LENGTH];

  if (U_FAILURE (*err))
    return NULL;
  if (name == NULL)
    return ucnv_open (NULL, err);
  if (u_strlen (name) > MAX_CONVERTER_NAME_LENGTH)
    {
      *err = U_ILLEGAL_ARGUMENT_ERROR;
      return NULL;
    }
  return ucnv_open (u_austrcpy (asciiName, name), err);
}
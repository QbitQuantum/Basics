/* ---------------------------------------------------------------------- */
int
copy_token_tab (char *token_ptr, char **ptr, int *length)
/* ---------------------------------------------------------------------- */
{
/*
 *   Copies from **ptr to *token_ptr until first tab is encountered.
 *
 *   Arguments:
 *      *token_ptr  output, place to store token
 *
 *     **ptr        input, character string to read token from
 *                  output, next position after token
 *
 *       length     output, length of token
 *
 *   Returns:
 *      UPPER,
 *      LOWER,
 *      DIGIT,
 *      EMPTY,
 *      EOL,
 *      UNKNOWN.
 */
  int i, j, return_value;
  char c;
/*
 *   Strip leading spaces
 */
  while ((c = **ptr) == ' ')
    (*ptr)++;
/*
 *   Check what we have
 */
  if (isupper ((int) c))
  {
    return_value = UPPER;
  }
  else if (islower ((int) c))
  {
    return_value = LOWER;
  }
  else if (isdigit ((int) c) || c == '.' || c == '-')
  {
    return_value = DIGIT;
  }
  else if (c == '\0')
  {
    return_value = EOL;
    return (return_value);
  }
  else if (c == '\t')
  {
    return_value = EMPTY;
  }
  else
  {
    return_value = UNKNOWN;
  }
/*
 *   Begin copying to token
 */
  i = 0;
#ifdef SKIP
  while ((c = **ptr) != '\t' && c != '\0')
  {
    token_ptr[i] = c;
    (*ptr)++;
    i++;
  }
#endif
  for (;;)
  {
    c = **ptr;
    if (c == '\t')
    {
      (*ptr)++;
      break;
    }
    else if (c == '\0')
    {
      break;
    }
    else
    {
      token_ptr[i] = c;
      (*ptr)++;
      i++;
    }
  }
  token_ptr[i] = '\0';
  *length = i;
/*
 *   Strip trailing spaces
 */
  for (j = i - 1; j >= 0; j--)
  {
    if (j != ' ')
      break;
  }
  if (j != i - 1)
  {
    token_ptr[j + 1] = '\0';
    *length = j + 1;
  }
  return (return_value);
}
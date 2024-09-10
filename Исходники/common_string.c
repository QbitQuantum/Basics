static
void
stringSubst2 (
char * const                bsrcptr,
char * const                bdstptr,
const char * const          pattstr,
const char * const          replstr,
const int                   pattsiz,
const int                   replsiz)
{
  char *              pattptr;
  int                 pattidx;

  pattptr = strstr (bsrcptr, pattstr);            /* Search for the pattern in the remaining source string   */
  pattidx = (pattptr == NULL) ? (strlen (bsrcptr) + 1): (pattptr - bsrcptr); /* Get length of unchanged part */

  if (replsiz < pattsiz)                          /* If replacement is smaller, pre-move unchanged part */
    memMov (bdstptr, bsrcptr, pattidx * sizeof (char));

  if (pattptr != NULL)                            /* If remaining part of string has to be processed */
    stringSubst2 (pattptr + pattsiz, bdstptr + pattidx + replsiz, pattstr, replstr, pattsiz, replsiz);

  if (replsiz > pattsiz)                          /* If replacement is longer, post-move unchanged part */
    memMov (bdstptr, bsrcptr, pattidx * sizeof (char));

  if (pattptr != NULL)                            /* If there is something to replace         */
    memCpy (bdstptr + pattidx, replstr, replsiz * sizeof (char)); /* Write replacement string */

  return;
}
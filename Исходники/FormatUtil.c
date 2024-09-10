/******************************************************************************
 * Function:    int _DtHelpFmtFindBreak (char *ptr, int mb_len, int *num_chars)
 *
 * Parameters:
 *              ptr             Specifies the string to check.
 *              mb_len          Specifies if the sequence should be single
 *                              byte or multi-byte.
 *              num_chars       Returns the character count.
 *
 * Returns      number of bytes in the sequence.
 *
 * errno Values:
 *
 * Purpose:     Find a length of 'ptr' comprised of multi or single byte
 *              characters.
 *
 *****************************************************************************/
int
_DtHelpFmtFindBreak (
    char *ptr,
    int   mb_len,
    int  *num_chars)
{
    int   len = 0;
    int   numChars = 0;
    int   mySize;
    short done = 0;

    while (0 == done && '\0' != *ptr)
      {
        mySize = mblen(ptr, MB_CUR_MAX);
        done   = 1;
        if (0 < mySize &&
		((1 != mb_len && 1 != mySize) || (1 == mb_len && 1 == mySize)))
          {
            numChars++;
            ptr  += mySize;
            len  += mySize;
            done  = 0;
          }
      }

    *num_chars = numChars;
    return len;
}
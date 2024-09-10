void clearerr(FILE *str)
{
  // Just return if the stream is NULL
  if (!str) return;

  _LOCK_FILE(str);
  
  str->_Mode &= ~M_EOF;       /* reset EOF indicator   */
  str->_Mode &= ~M_ERROR;     /* reset error indicator */

  _UNLOCK_FILE(str);
}
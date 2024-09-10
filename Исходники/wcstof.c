#include <stdlib.h>
#include <string.h>
#include <mbstring.h>

#include "mb_wc_common.h"

float wcstof (const wchar_t * __restrict__ wcs, wchar_t ** __restrict__ wcse)
{
  char * cs;
  char * cse;
  unsigned int i;
  float ret;
  const unsigned int cp = __mingw_get_codepage();

  /* Allocate enough room for (possibly) mb chars */
  cs = (char *) malloc ((wcslen(wcs)+1) * MB_CUR_MAX);

  if (cp == 0) /* C locale */
    {
      for (i = 0; (wcs[i] != 0) && wcs[i] <= 255; i++)
	cs[i] = (char) wcs[i];
      cs[i]  = '\0';
    }
  else
    {
      int nbytes = -1;
      int mb_len = 0;
      /* loop through till we hit null or invalid character */
      for (i = 0; (wcs[i] != 0) && (nbytes != 0); i++)
	{
	  nbytes = WideCharToMultiByte(cp, WC_COMPOSITECHECK | WC_SEPCHARS,
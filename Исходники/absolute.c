boolean
kpse_absolute_p P1C(string, filename)
{
#ifdef VMS
#include <string.h>
  return strcspn (filename, "]>:") != strlen (filename);
#else /* not VMS */
  boolean absolute = IS_DIR_SEP (*filename)
#ifdef DOS
                      || ISALPHA (*filename) && filename[1] == ':'
#endif /* DOS */
		      ;
  boolean explicit_relative
    = (*filename == '.'
       && (IS_DIR_SEP (filename[1])
           || (filename[1] == '.' && IS_DIR_SEP (filename[2]))));

  return absolute || explicit_relative;
#endif /* not VMS */
}
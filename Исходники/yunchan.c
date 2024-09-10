FILE *create_tempfile (void)
{
  FILE *ret = NIL;
  char *s = _tempnam (getenv ("TEMP"),"msg");
  if (s) {			/* if got temporary name... */
				/* open file, and stash name on _tmpfname */
    if (ret = fopen (s,"w+b")) ret->_tmpfname = s;
    else fs_give ((void **) &s);/* flush temporary string */
  }
  return ret;
}
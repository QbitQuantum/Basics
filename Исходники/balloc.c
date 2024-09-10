/* external function definitions */
void *
balloc(int size)
{
  static char fnc[] = "balloc";
  void *p;

  if (size <= 0) {
    return (void *) (0);
  }
  if ((p = (void *) malloc((unsigned) size)) == (void *) (0)) {
    if (errno == ENOMEM) {
      /* GASP!!!! */
      gasp(size);
      _exit(1);
    }
    Abort("%t %s(): abort: malloc(%u): %m\n", fnc, (unsigned) size);
  }
  return p;
}
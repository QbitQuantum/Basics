static char *
whatreg (unsigned int *preg, char *src)
{
  unsigned int new_reg;

  /* src[0] is already known to be a digit.  */
  if (ISDIGIT (src[1]))
    {
      new_reg = (src[0] - '0') * 10 + src[1] - '0';
      src += 2;
    }
  else
    {
      new_reg = (src[0] - '0');
      src += 1;
    }

  if (src[0] != 0 && src[0] != ',' && src[0] != '(' && src[0] != ')')
    return NULL;

  *preg = new_reg;
  return src;
}
char		*lowerCase(char *s)
{
  char		*tmp;

  tmp = s;
  while (s && *s)
    {
      if (isUpper(*s))
	*s += 32;
      s++;
    }
  return (tmp);
}
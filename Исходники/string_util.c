char   *
        format(char *buf, char *from, int width, int right_justify)
{
  int     len = strlen(from), i;

  if (len > width)
    len = width;

  buf[width] = '\0';

  if (right_justify)
    {
      STRNCPY(&(buf[width - len]), from, len);

      for (i = 0; i < (width - len); i++)
  buf[i] = ' ';
    }
  else
    {
      STRNCPY(buf, from, len);

      for (i = len; i < width; i++)
  buf[i] = ' ';
    }

  return (buf);
}
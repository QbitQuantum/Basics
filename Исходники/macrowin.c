int
        formatline(char *line)
{
  register int end;
  char   *temp;
  int     num = 0;

  if (!line)
    return 0;
  if (strlen(line) <= MAXMACRO)
    {
      STRNCPY(maclines[num], line, sizeof(maclines[0]));
      lineno++;
      return 1;
    }

  temp = line;
  while (1)
    {
      end = MAXMACRO - 1;
      if (end > strlen(temp))
  {
    lineno++;
    STRNCPY(maclines[num++], temp, sizeof(maclines[0]));
    return (num);
  }
      else
  for (; temp[end] != '%'; end--);

      lineno++;
      STRNCPY(maclines[num++], temp, end);

      temp = temp + end;
    }
}
static void rtmsg_dump(const uint8_t *buf, size_t len)
{
  char str[80];
  size_t i, off = 0;
  int k = 0;

  for(i=0; i<len; i++)
    {
      if(k == 20)
	{
	  printerror(0, NULL, __func__, "%s", str);
	  k = 0;
	  off = 0;
	}

      if(k != 0 && (k % 4) == 0)
	string_concat(str, sizeof(str), &off, " ");
      string_concat(str, sizeof(str), &off, "%02x", buf[i]);
      k++;
    }

  if(k != 0)
    printerror(0, NULL, __func__, "%s", str);
  return;
}
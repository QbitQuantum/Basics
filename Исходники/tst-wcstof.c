int
zmain (int argc, char** argv)
{
  int result = 0;
  char buf[100];
  wchar_t tmp[3];
  tmp[0] = '8';
  tmp[1] = '1';
  tmp[2] = 0;

  snprintf (buf, 100, "%S = %f", tmp, wcstof (tmp, NULL));
  printf ("\"%s\" -> %s\n", buf,
	  strcmp (buf, "81 = 81.000000") == 0 ? "okay" : "buggy");
  result |= strcmp (buf, "81 = 81.000000") != 0;

  return result;
}
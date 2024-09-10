void test_array (const char *s)
{
  extern char a[8];

  q[0] = strcmp (a, s);
  q[1] = strncmp (a, s, 7);
  q[2] = strlen (a);
  q[3] = strnlen (a, 7);
  q[4] = strcspn (a, s);
  q[5] = strspn (a, s);
  q[6] = strxfrm (a, s, 7);
}
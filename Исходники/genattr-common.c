static void
gen_attr (rtx attr)
{
  const char *p, *tag;

  p = XSTR (attr, 1);
  if (*p != '\0')
    {
      printf ("enum attr_%s {", XSTR (attr, 0));

      while ((tag = scan_comma_elt (&p)) != 0)
	{
	  write_upcase (XSTR (attr, 0));
	  putchar ('_');
	  while (tag != p)
	    putchar (TOUPPER (*tag++));
	  if (*p == ',')
	    fputs (", ", stdout);
	}
      fputs ("};\n", stdout);
    }
}
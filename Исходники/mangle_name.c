static void
append_unicode_mangled_name (const char *name, int len)
{
  const unsigned char *ptr;
  const unsigned char *limit = (const unsigned char *)name + len;
  int uuU = 0;
  for (ptr = (const unsigned char *) name;  ptr < limit;  )
    {
      int ch = UTF8_GET(ptr, limit);

      if ((ISALNUM (ch) && ch != 'U') || ch == '$')
        {
	  obstack_1grow (mangle_obstack, ch);
          uuU = 0;
        }
      /* Everything else needs encoding */
      else
	{
	  /* Buffer large enough for UINT_MAX plus the prefix.  */
	  char buf [13];
	  if (ch == '_' || ch == 'U')
	    {
	      /* Prepare to recognize __U */
	      if (ch == '_' && (uuU < 3))
		{
		  uuU++;
		  obstack_1grow (mangle_obstack, ch);
		}
	      /* We recognize __U that we wish to encode
                 __U_. Finish the encoding. */
	      else if (ch == 'U' && (uuU == 2))
		{
		  uuU = 0;
		  obstack_grow (mangle_obstack, "U_", 2);
		}
	      /* Otherwise, just reset uuU and emit the character we
                 have. */
	      else
		{
		  uuU = 0;
		  obstack_1grow (mangle_obstack, ch);
		}
	      continue;
	    }
	  sprintf (buf, "__U%x_", ch);
	  obstack_grow (mangle_obstack, buf, strlen (buf));
	  uuU = 0;
	}
    }
}
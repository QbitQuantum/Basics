/* catread - read a catalogue file */
static _CAT_CATALOG_T *
catread (const char *name)
{
  FILE *f;
  STRING_T *s = DScreate (), *t = DScreate ();
  _CAT_CATALOG_T *cat = 0;
  size_t z;
  _CAT_MESSAGE_T catmsg = { 0, 0, 0 };
  int c;

  /* Open the catfile */
  f = fopen (name, "r");
  if (f == 0)
    return 0;			/* could not open file */
  setvbuf (f, 0, _IOFBF, 16384);
  while (DSlength (s = append_from_file (f, s)) > 0)
    {
      DSresize (s, DSlength (s) - 1, 0);
      /* We have a full line */
      if (DSlength (s) > 0)
	{
	  z = DSfind_first_not_of (s, " \t\f\v\r", 0, NPOS);
	  DSremove (s, 0, z);
	  z = DSfind_last_not_of (s, " \t\f\v\r", NPOS, NPOS);
	  DSresize (s, z + 1, 0);
	}
      if (DSlength (s) > 0 && DSget_at (s, DSlength (s) - 1) == '\\')
	{
	  /* continuation */
	  DSresize (s, DSlength (s) - 1, 0);
	}
      else
	{
	  if (DSlength (s) > 0 && isdigit (DSget_at (s, 0)))
	    {
	      /* if it starts with a digit, assume it's a catalog line */
	      for (z = 0, catmsg.set_id = 0;
		   isdigit (c = DSget_at (s, z));
		   catmsg.set_id = catmsg.set_id * 10 + (c - '0'), z++);
	      z++;
	      for (catmsg.msg_id = 0;
		   isdigit (c = DSget_at (s, z));
		   catmsg.msg_id = catmsg.msg_id * 10 + (c - '0'), z++);
	      z++;
	      DSremove (s, 0, z);
	      transform_string (t, s);
	      if (catmsg.msg == 0)
		catmsg.msg = DScreate ();
	      DSassign (catmsg.msg, t, 0, NPOS);
	      if (cat == 0)
		{
		  cat = malloc (sizeof (_CAT_CATALOG_T));
		  if (cat == 0)
		    Nomemory ();
		  cat->is_opened = 0;
		  cat->msgs = _CATMSG_create ();
		}
	      _CATMSG_append (cat->msgs, &catmsg, 1, 0);
	    }
	  DSresize (s, 0, 0);
	}
    }
  fclose (f);
  qsort (_CATMSG_base (cat->msgs), _CATMSG_length (cat->msgs),
	 sizeof (_CAT_MESSAGE_T), catmsg_cmp);
  return cat;
}
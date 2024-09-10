/* Parse a message specification from (argc;argv). Returned msgset is
   not sorted nor optimised */
int
_mh_msgset_parse (mu_mailbox_t mbox, mh_msgset_t *msgset, int argc, char **argv)
{
  size_t msgcnt;
  size_t *msglist;
  size_t i, msgno;
  
  if (argc == 0)
    return 1;
  
  msgcnt = argc;
  msglist = calloc (msgcnt, sizeof(*msglist));
  for (i = 0, msgno = 0; i < argc; i++)
    {
      char *p = NULL, *q;
      size_t start, end;
      size_t msg_first, n;
      long num;
      char *arg = msgset_preproc (mbox, argv[i]);

      if (!mu_isdigit (arg[0]))
	{
	  int j;
	  mh_msgset_t m;
	  
	  if (expand_user_seq (mbox, &m, arg))
	    {
	      mu_error (_("message set %s does not exist"), arg);
	      exit (1);
	    }
	  _expand (&msgcnt, &msglist, m.count);
	  for (j = 0; j < m.count; j++)
	    msglist[msgno++] = m.list[j];
	  mh_msgset_free (&m);
	}
      else
	{
	  start = strtoul (arg, &p, 0);
	  switch (*p)
	    {
	    case 0:
	      n = mh_get_message (mbox, start, NULL);
	      if (!n)
		{
		  mu_error (_("message %lu does not exist"),
			    (unsigned long) start);
		  exit (1);
		}
	      msglist[msgno++] = n;
	      break;
	      
	    case '-':
	      end = strtoul (p+1, &p, 0);
	      if (*p)
		msgset_abort (argv[i]);
	      if (end < start)
		{
		  size_t t = start;
		  start = end;
		  end = t;
		}
	      _expand (&msgcnt, &msglist, end - start);
	      msg_first  = msgno;
	      for (; start <= end; start++)
		{
		  n = mh_get_message (mbox, start, NULL);
		  if (n)
		    msglist[msgno++] = n;
		}
	      if (msgno == msg_first)
		{
		  mu_error (_("no messages in range %s"), argv[i]);
		  exit (1);
		}
	      break;
	      
	    case ':':
	      num = strtoul (p+1, &q, 0);
	      if (*q)
		msgset_abort (argv[i]);
	      if (p[1] != '+' && p[1] != '-')
		{
		  if (strncmp (argv[i], "last:", 5) == 0
		      || strncmp (argv[i], "prev:", 5) == 0)
		    num = -num;
		}
	      end = start + num;
	      if (end < start)
		{
		  size_t t = start;
		  start = end + 1;
		  end = t;
		}
	      else
		end--;
	      _expand (&msgcnt, &msglist, end - start);
	      msg_first  = msgno;
	      for (; start <= end; start++)
		{
		  n = mh_get_message (mbox, start, NULL);
		  if (n)
		    msglist[msgno++] = n;
		}
	      if (msgno == msg_first)
		{
		  mu_error (_("no messages in range %s"), argv[i]);
		  exit (1);
		}
	      break;
	      
	    default:
	      msgset_abort (argv[i]);
	    }
	}
      free (arg);
    }

  msgset->count = msgno;
  msgset->list = msglist;
  return 0;
}
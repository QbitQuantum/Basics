void
smtp (int fd)
{
  int state, c;
  char *buf = NULL;
  size_t size = 0;
  mu_mailbox_t mbox;
  mu_message_t msg;
  char *tempfile;
  char *rcpt_addr;
  
  in = fdopen (fd, "r");
  out = fdopen (fd, "w");
  SETVBUF (in, NULL, _IOLBF, 0);
  SETVBUF (out, NULL, _IOLBF, 0);

  smtp_reply (220, "Ready");
  for (state = STATE_INIT; state != STATE_QUIT; )
    {
      int argc;
      char **argv;
      int kw, len;
      
      if (getline (&buf, &size, in) == -1)
	exit (1);
      len = strlen (buf);
      while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r'))
	len --;
      buf[len] = 0;
      
      if (mu_argcv_get (buf, "", NULL, &argc, &argv))
	exit (1);

      kw = smtp_kw (argv[0]);
      if (kw == KW_QUIT)
	{
	  smtp_reply (221, "Done");
	  state = STATE_QUIT;
	  mu_argcv_free (argc, argv);
	  continue;
	}
      
      switch (state)
	{
	case STATE_INIT:
	  switch (kw)
	    {
	    case KW_EHLO:
	    case KW_HELO:
	      if (argc == 2)
		{
		  smtp_reply (250, "pleased to meet you");
		  state = STATE_EHLO;
		}
	      else
		smtp_reply (501, "%s requires domain address", argv[0]);
	      break;

	    default:
	      smtp_reply (503, "Polite people say HELO first");
	      break;
	    }
	  break;
	  
	case STATE_EHLO:
	  switch (kw)
	    {
	    case KW_MAIL:
	      if (argc == 2)
		from_person = check_prefix (argv[1], "from:");
	      else if (argc == 3 && mu_c_strcasecmp (argv[1], "from:") == 0)
		from_person = argv[2];
	      else
		from_person = NULL;

	      if (from_person)
		{
		  from_person = strdup (from_person);
		  smtp_reply (250, "Sender OK");
		  state = STATE_MAIL;
		}
	      else
		smtp_reply (501, "Syntax error");
	      break;

	    default:
	      smtp_reply (503, "Need MAIL command");
	    }
	  break;
	  
	case STATE_MAIL:
	  switch (kw)
	    {
	    case KW_RCPT:
	      if (argc == 2)
		rcpt_addr = check_prefix (argv[1], "to:");
	      else if (argc == 3 && mu_c_strcasecmp (argv[1], "to:") == 0)
		rcpt_addr = argv[2];
	      else
		rcpt_addr = NULL;
	      
	      if (rcpt_addr)
		{
		  if (add_recipient (rcpt_addr))
		    smtp_reply (451, "Recipient not accepted");
		  else
		    {
		      smtp_reply (250, "Recipient OK");
		      state = STATE_RCPT;
		    }
		}
	      else
		smtp_reply (501, "Syntax error");
	      break;
	      
	    default:
	      smtp_reply (503, "Need RCPT command");
	    }
	  break;
	  
	case STATE_RCPT:
	  switch (kw)
	    {
	    case KW_RCPT:
	      if (argc == 2)
		rcpt_addr = check_prefix (argv[1], "to:");
	      else if (argc == 3 && mu_c_strcasecmp (argv[1], "to:") == 0)
		rcpt_addr = argv[2];
	      else
		rcpt_addr = NULL;
	      
	      if (rcpt_addr)
		{
		  if (add_recipient (rcpt_addr))
		    smtp_reply (451, "Recipient not accepted");
		  else
		    {
		      smtp_reply (250, "Recipient OK");
		      state = STATE_RCPT;
		    }
		}
	      else
		smtp_reply (501, "Syntax error");
	      break;

	    case KW_DATA:
	      smtp_reply (354,
			  "Enter mail, end with \".\" on a line by itself");
	      make_tmp (in, from_person, &tempfile);
	      if ((c = mu_mailbox_create_default (&mbox, tempfile)) != 0)
		{
		  mu_error ("%s: can't create mailbox %s: %s",
			    progname,
			    tempfile, mu_strerror (c));
		  unlink (tempfile);
		  exit (1);
		}

	      if ((c = mu_mailbox_open (mbox, MU_STREAM_RDWR)) != 0)
		{
		  mu_error ("%s: can't open mailbox %s: %s",
			    progname, 
			    tempfile, mu_strerror (c));
		  unlink (tempfile);
		  exit (1);
		}

	      mu_mailbox_get_message (mbox, 1, &msg);
	      if (message_finalize (msg, 0) == 0)
		mta_send (msg);
	      else
		smtp_reply (501, "can't send message"); /*FIXME: code?*/
	      unlink (tempfile);

	      mu_address_destroy (&recipients);
	      from_person = NULL;
	      
	      smtp_reply (250, "Message accepted for delivery");
	      state = STATE_EHLO;
	      break;

	    default:
	      smtp_reply (503, "Invalid command");
	      break;
	    }
	  break;

	}
      mu_argcv_free (argc, argv);
    }
    
  close (fd);
}
static void
set_input(struct runinfo *rip)
{
  if (rip->from == i_stdin)
    {
      rip->more_sources = 0;
      rip->source = stdin;
      curr_fname = rip->fname = xstrdup("<stdin>");
    }
  else if (rip->from == i_names)
    {
      rip->source = NULL;
      while (rip->more_sources)
	{
	  static char fname_buf[_MAX_PATH + 1];
	  char *fp = fgets(fname_buf,_MAX_PATH,stdin);
	  if (fp)
	    {
	      fp = fname_buf + strlen(fname_buf);
	      if ('\n' == fp[-1])
		fp[-1] = '\0';
	      if (NULL == (rip->source = fopen(fname_buf,"r")) && verbose)
		fprintf(stderr,"runexpat: open failed on %s\n",fname_buf);
	      else if (verbose)
		fprintf(stderr,"runexpat: inputting %s\n",fname_buf);
	      rip->more_sources = feof(stdin);
	      curr_fname = rip->fname = xstrdup(fname_buf);
	    }
	  else
	    {
	      rip->source = NULL;
	      rip->more_sources = 0;
	    }
	  if (rip->source)
	    break;
	}
    }
  else if (rip->from == i_list)
    {
      if (rip->todo == NULL)
	{
	  rip->todo = rip->list;
	  if (NULL == rip->todo || NULL == *rip->todo)
	    {
	      rip->source = NULL;
	      rip->more_sources = 0;
	      rip->todo = NULL;
	      return;
	    }
	}
      rip->more_sources = 1;
      while (rip->more_sources)
	{
	  if (NULL == (rip->source = fopen(*rip->todo,"r")) && verbose)
	    fprintf(stderr,"runexpat: open failed on %s\n",*rip->todo);
	  else
	    {
	      if (verbose)
		fprintf(stderr,"runexpat: inputting %s\n",*rip->todo);
	      curr_fname = *rip->todo;
	      rip->fname = xstrdup(curr_fname);
	      progress("xmlinput: %s\n",curr_fname);
	    }
	  rip->more_sources = (NULL != *++rip->todo);
	  if (!rip->more_sources)
	    rip->todo = NULL;
	  if (rip->source)
	    break;
	}
    }
}
/* return non-negative on success; -1 on error; 
   non-negative is the length of string parsed by f2_parse.
 */
int
f2_parse(const Uchar *file, size_t line, Uchar *lp, struct f2 *f2p, Uchar **psu_sense, struct sig_context *scp)
{
  Uchar *tmp = NULL, *err_lp = NULL,
    *disambig = NULL, *ampamp = NULL, 
    *orig_lp = lp, field = '\0', *psu_tmp = NULL;
  int ret = 0;
  const char *saved_phase = phase;
  int square, saved_with_textid = with_textid;

  if (!lp)
    return 1;
  /* err_lp = npool_copy(lp, scp->pool); */
  err_lp = (Uchar*)strdup((char*)lp);

  phase = "f2";
  with_textid = 0;

  /* skip the old shadow lem codes */
  if (*lp == '`')
    {
      vwarning2((char*)file,line,"%s: please remove deprecated shadow lem sequence '`' or '`?'",err_lp);      
      lp += 1 + (lp[1] == '?');
    }

  if ((ampamp = (unsigned char*)strstr((char*)lp, "&&")))
    {
      f2_parse_cof(file, line, lp, f2p, psu_sense, ampamp, scp);
      goto ret;
    }

  /* if the sig starts with @ parse the admin fields @PROJ%LANG:FORM=
   * first.
   *
   * N.B.: % and : are not recognized by field_end() as this causes
   * problems parsing morphology.
   */
  if ('@' == *lp)
    {
      f2p->project = lp+1;
      lp = (Uchar*)strchr((char*)lp,'%');
      if (lp)
	{
	  *lp++ = '\0';
	  f2p->lang = lp;
	  f2p->core = langcore_of((const char*)lp);
	  lp = (Uchar*)strchr((char*)lp,':');
	  if (lp)
	    {
	      *lp++ = '\0';
	      f2p->form = lp;
	      lp = (Uchar*)strchr((char*)lp,'=');
	      *lp++ = '\0';
	    }
	}
    }

  if ('[' == *lp)
    {
      /* FIXME: this needs to be more rigorous and check for CF-legal char in initial position */
      vwarning2((char*)file,line,"%s: lemmatization cannot begin with '['",err_lp);
      goto ret;
    }

  if (!strchr((const char *)lp,'['))
    {
      /* f2p->cf = "X"; */
      f2p->gw = (unsigned char *)"X";
      if (*lp == 'n')
	{
	  f2p->pos = "n";
	  ++lp;
	}
      else if (*lp == 'u')
	{
	  f2p->pos = "u";
	  ++lp;
	}
      goto pos_parse;
    }

  /* parse the CF[GW/SENSE]POS'EPOS which are constant: */
  f2p->cf = lp;
  if (*lp == '"')
    {
      ++lp;
      f2p->cf = lp; /* don't include quotes in the CF; 
		       WATCHME: what happens in post-cache
		       retrieval parse?
		     */
      BIT_SET(f2p->flags,F2_FLAGS_CF_QUOTED);
      /*  fp->explicit |= NEW_CF; */ 
      /* have to do something here, i.e., suppress charset translation */
    }

  while (*lp && (*lp != '[' || lp[-1] == '\\'))
    ++lp;

  if (BIT_ISSET(f2p->flags,F2_FLAGS_CF_QUOTED))
    {
      if (lp[-1] == '"')
	lp[-1] = '\0';
      else
	{
	  vwarning2((char*)file,line,"%s: '\"' missing on quoted CF",err_lp);
	  ret = -1;
	}
    }

  if (lp)
    *lp = '\0';
  else
    goto ret;

  if (lp[-1] == ')' && lp[-2] != '\\')
    {
      char *oparen = strchr((char*)f2p->cf,'(');
      if (oparen && oparen[-1] != '\\')
	{
	  *oparen++ = '\0';
	  f2p->restrictor = (unsigned char*)oparen;
	  lp[-1] = '\0';
	}
      else
	{
	  vwarning2((char*)file,line,"%s: '(' missing on restrictor",err_lp);
	  ret = -1;
	  goto ret;
	}
    }
  else if ((tmp = (unsigned char*)strchr((char*)f2p->cf,'(')) && tmp[-1] != '\\')
    {
      vwarning2((char*)file,line,"%s: ')' missing on restrictor",err_lp);
      ret = -1;
      goto ret;
    }

  f2p->gw = ++lp;
  if ((psu_tmp = (Uchar *)strstr(cc(lp),"+=")))
    {
      *psu_tmp = '\0';
      psu_tmp += 2;
      if (psu_sense)
	*psu_sense = psu_tmp;
      psu_tmp = (Uchar *)strchr((const char *)psu_tmp,']');
    }

  /* make SENSE optional here to support inline lem parsing */
  square = 0;
  while (*lp && (*lp != '/' || lp[1] != '/'))
    {
      if (*lp == '[' && lp[-1] != '\\')
	++square;
      else if (*lp == ']' && lp[-1] != '\\')
	{
	  if (square)
	    --square;
	  else
	    break;
	}
      ++lp;
    }

  /* If we didn't find ] but had a psu_sense with +=,
     reset lp to the closing square bracket after the
     psu_sense */
  if (!*lp && psu_tmp)
    lp = psu_tmp;

  if (*lp)
    {
      if ('/' == *lp)
	{
	  *lp++ = '\0';
	  ++lp;
	  f2p->sense = lp;
	  square = 0;
	  while (*lp)
	    {
	      if (*lp == '[' && lp[-1] != '\\')
		++square;
	      else if (*lp == ']' && lp[-1] != '\\')
		{
		  if (square)
		    --square;
		  else
		    break;
		}
	      ++lp;
	    }
	}
      if (*lp) /* lp is at closing square bracket of CF[GW] */
	{
	  *lp++ = '\0';
	  
	  /* This is either a POS or something
	     that starts with a field char */

	pos_parse:
	  if (isupper(*lp))
	    {
	      Uchar *end = NULL;
	      Uchar *epos = NULL;
	      for (end = lp; *end && !isspace(*end); ++end)
		;
	      epos = (Uchar*)strchr((const char *)lp,'\'');
	      f2p->pos = lp;
	      if (epos && epos < end)
		lp = epos;
	      else
		lp = field_end(lp);
	      if (*f2p->pos == 'V' && '/' == *lp && (lp[1] == 't' || lp[1] == 'i'))
		{
		  ++lp;
		  epos = (Uchar*)strchr((const char *)lp,'\'');
		  if (epos && epos < end)
		    lp = epos;
		  else
		    lp = field_end(lp);
		}
	      field = *lp;
	      if (field == '\'')
		{
		  *lp++ = '\0';
		  f2p->epos = lp;
		  lp = field_end(lp);
		  if (*f2p->epos == 'V' && '/' == *lp && (lp[1] == 't' || lp[1] == 'i'))
		    {
		      ++lp;
		      lp = field_end(lp);
		    }
		  field = *lp;
		  *lp++ = '\0';
		}
	      else
		*lp++ = '\0';
	    }
	  else if (*lp == '\'')
	    {
	      *lp++ = '\0';
	      f2p->epos = lp;
	      lp = field_end(lp);
	      field = *lp;
	      *lp++ = '\0';
	    }
	  else if (*lp)
	    {
	      field = *lp;
	      *lp++ = '\0';
	    }

	  /* Now we are at a variable set of instance
	     fields; parse as though they can be in any
	     order, though in principle the order should
	     always be fixed. */
	  while (*lp)
	    {
	      switch (field)
		{
#if 0
		  /* this must follow POS and ' is no longer a field
		   * ender because of conflict with ' in M1
		   */
		case '\'':
		  f2p->epos = lp;
		  break;
#endif
		case '@':
		  f2p->project = lp;
		  break;
		case '%':
		  f2p->lang = lp;
		  break;
		case ':':
		  f2p->form = lp;
		  break;
		case '$':
		  if (!BIT_ISSET(f2p->flags, F2_FLAGS_LEM_BY_NORM))
		    f2p->norm = lp;
		  /* else ignore normalization because we got it from the "FORM" */
		  break;
		case '/':
		  f2p->base = lp;
		  break;
		case '+':
		  if (*lp == '-')
		    f2p->cont = lp;
		  else if (*lp == '.')
		    f2p->augment = lp;
		  else
		    vwarning2((char*)file,line,"%s: '+' in signature should be followed by '-' or '.'", err_lp);
		  ++lp;
		  break;
		case '#':
		  if (*lp == '#')
		    {
		      ++lp;
		      f2p->morph2 = lp;
		    }
		  else
		    f2p->morph = lp;
		  break;
		case '*':
		  f2p->stem = lp;
		  break;
		case '\\':
		  disambig = lp;
		  while (isalnum(*lp) || '\\' == *lp)
		    ++lp;
		  break;
		case '<':
		case ' ':
		case '\t':
		case 0:
		  goto break_switch_loop;
		default:
		  vwarning2((char*)file,line,"%s: parse error at '%c'", err_lp, field);
		  ++ret;
		  goto ret;
		}
	      lp = field_end(lp);
	      if (*lp)
		{
		  field = *lp;
		  *lp++ = '\0';
		}
	    }
	}
    }

 break_switch_loop:

  validate_pos((const char *)file, line, f2p->pos);
  validate_pos((const char *)file, line, f2p->epos);
  if (f2p->base)
    validate_base((const char *)file, line, f2p->base);

#if 0
  /* If lp is non-zero we didn't manage to parse the entire form: */
  if (*lp)
    {
      vwarning2((char*)file,line,"%s: bad tense designator: only allowed with verb POS",err_lp);
      ret = -1;
      goto ret;
    }
#endif

  /* field == '$' occurs when $ is the end of the lem, e.g., ana[to]PRP$ */
  /* FIXME: THIS IS A POOR TEST BECAUSE IT FAILS ON ]N$#M1 */
  if (field == '$')
    {
      if (!f2p->norm || !*f2p->norm)
	f2p->norm = f2p->cf;
    }
  
  if (BIT_ISSET(f2p->flags, F2_FLAGS_LEM_BY_NORM))
    {
      if (f2p->norm && f2p->cf && !strcmp((char*)f2p->cf,(char*)f2p->norm))
	{
	  BIT_SET(f2p->flags, F2_FLAGS_NORM_IS_CF);
	  f2p->cf = NULL;
	}
    }

  if (f2p->gw)
    {
      char *bs = strchr((char*)f2p->gw, '\\');
      if (bs)
	{
	  unsigned char *gwtmp = npool_copy(f2p->gw, f2_pool);
	  bs = (char *)(gwtmp + (bs - (char*)f2p->gw));
	  *bs++ = '\0';
	  f2p->gw = gwtmp;
	  if (*bs == 'i' || *bs == 't')
	    {
	      if ((!f2p->pos || *f2p->pos == 'V')
		  && (!f2p->epos || *f2p->epos == 'V'))
		{
		  if (*bs == 'i')
		    f2p->epos = npool_copy((unsigned char *)"V/i",f2_pool);
		  else
		    f2p->epos = npool_copy((unsigned char *)"V/t",f2_pool);
		}
	      else
		{
		  vwarning2((char*)file,line,"%s: bad designator: only allowed with verb POS",err_lp);
		  ret = -1;
		  goto ret;
		}
	    }
	  else
	    {
	      vwarning2((char*)file,line,"%s: bad designator: only 'i' or 't' allowed",err_lp);
	      ret = -1;
	      goto ret;
	    }
	}
    }
 
 ret:
  free(err_lp);
  /* '<' == *lp must be dealt with by caller */
  if (isspace(*lp))
    *lp++ = '\0';

  if (!f2p->gw || !*f2p->gw)
    {
      if (f2p->sense && *f2p->sense)
	f2p->gw = f2p->sense;
      else
	f2p->gw = (unsigned char *)"1";
    }

  clean_cf((char*)file, line, (unsigned char *)f2p->cf);

  clean_gw_sense((char*)file, line, (unsigned char *)f2p->gw);
  if (f2p->sense)
    clean_gw_sense((char*)file, line, (unsigned char *)f2p->sense);

  if (f2p->augment)
    {
      char buf[1024];
      sprintf(buf,"%s%s%s",f2p->form,AUGMENT_STR,f2p->augment);
      f2p->form = npool_copy((unsigned char *)buf,f2_pool);
    }

  if (disambig)
    {
      char buf[1024];
      if (*disambig == *(DISAMBIG_STR))
	sprintf(buf,"%s%s",f2p->form,disambig);
      else
	sprintf(buf,"%s%s%s",f2p->form,DISAMBIG_STR,disambig);
      f2p->form = npool_copy((unsigned char *)buf,f2_pool);
    }

  if (f2p->cf && strchr((char*)f2p->cf,' '))
    BIT_SET(f2p->flags, F2_FLAGS_IS_PSU);
  phase = saved_phase;
  with_textid = saved_with_textid;

  return (ret < 0) ? -1 : (lp - orig_lp);
}
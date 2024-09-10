static reg_errcode_t
tre_parse_bracket_items(tre_parse_ctx_t *ctx, int negate,
			tre_ctype_t neg_classes[], int *num_neg_classes,
			tre_ast_node_t ***items, int *num_items,
			int *items_size)
{
  const tre_char_t *re = ctx->re;
  reg_errcode_t status = REG_OK;
  tre_ctype_t classt = (tre_ctype_t)0;
  int i = *num_items;
  int max_i = *items_size;
  int skip;

  /* Build an array of the items in the bracket expression. */
  while (status == REG_OK)
    {
      skip = 0;
      if (re == ctx->re_end)
	{
	  status = REG_EBRACK;
	}
      else if (*re == CHAR_RBRACKET && re > ctx->re)
	{
	  DPRINT(("tre_parse_bracket:	done: '%.*" STRF "'\n", REST(re)));
	  re++;
	  break;
	}
      else
	{
	  tre_cint_t min = 0, max = 0;

	  classt = (tre_ctype_t)0;
	  if (re + 2 < ctx->re_end
	      && *(re + 1) == CHAR_MINUS && *(re + 2) != CHAR_RBRACKET)
	    {
	      DPRINT(("tre_parse_bracket:  range: '%.*" STRF "'\n", REST(re)));
	      min = *re;
	      max = *(re + 2);
	      re += 3;
	      /* XXX - Should use collation order instead of encoding values
		 in character ranges. */
	      if (min > max)
		status = REG_ERANGE;
	    }
	  else if (re + 1 < ctx->re_end
		   && *re == CHAR_LBRACKET && *(re + 1) == CHAR_PERIOD)
	    status = REG_ECOLLATE;
	  else if (re + 1 < ctx->re_end
		   && *re == CHAR_LBRACKET && *(re + 1) == CHAR_EQUAL)
	    status = REG_ECOLLATE;
	  else if (re + 1 < ctx->re_end
		   && *re == CHAR_LBRACKET && *(re + 1) == CHAR_COLON)
	    {
	      char tmp_str[64];
	      const tre_char_t *endptr = re + 2;
	      size_t len;
	      DPRINT(("tre_parse_bracket:  class: '%.*" STRF "'\n", REST(re)));
	      while (endptr < ctx->re_end && *endptr != CHAR_COLON)
		endptr++;
	      if (endptr != ctx->re_end)
		{
		  len = MIN(endptr - re - 2, 63);
#ifdef TRE_WCHAR
		  {
		    tre_char_t tmp_wcs[64];
		    wcsncpy(tmp_wcs, re + 2, len);
		    tmp_wcs[len] = L'\0';
#if defined HAVE_WCSRTOMBS
		    {
		      mbstate_t state;
		      const tre_char_t *src = tmp_wcs;
		      memset(&state, '\0', sizeof(state));
		      len = wcsrtombs(tmp_str, &src, sizeof(tmp_str), &state);
		    }
#elif defined HAVE_WCSTOMBS
		    len = wcstombs(tmp_str, tmp_wcs, 63);
#endif /* defined HAVE_WCSTOMBS */
		  }
#else /* !TRE_WCHAR */
		  strncpy(tmp_str, (const char*)re + 2, len);
#endif /* !TRE_WCHAR */
		  tmp_str[len] = '\0';
		  DPRINT(("  class name: %s\n", tmp_str));
		  classt = tre_ctype(tmp_str);
		  if (!classt)
		    status = REG_ECTYPE;
		  /* Optimize character classes for 8 bit character sets. */
		  if (status == REG_OK && ctx->cur_max == 1)
		    {
		      status = tre_expand_ctype(ctx->mem, classt, items,
						&i, &max_i, ctx->cflags);
		      classt = (tre_ctype_t)0;
		      skip = 1;
		    }
		  re = endptr + 2;
		}
	      else
		status = REG_ECTYPE;
	      min = 0;
	      max = TRE_CHAR_MAX;
	    }
	  else
	    {
	      DPRINT(("tre_parse_bracket:   char: '%.*" STRF "'\n", REST(re)));
	      if (*re == CHAR_MINUS && *(re + 1) != CHAR_RBRACKET
		  && ctx->re != re)
		/* Two ranges are not allowed to share and endpoint. */
		status = REG_ERANGE;
	      min = max = *re++;
	    }

	  if (status != REG_OK)
	    break;

	  if (classt && negate)
	    if (*num_neg_classes >= MAX_NEG_CLASSES)
	      status = REG_ESPACE;
	    else
	      neg_classes[(*num_neg_classes)++] = classt;
	  else if (!skip)
	    {
	      status = tre_new_item(ctx->mem, min, max, &i, &max_i, items);
	      if (status != REG_OK)
		break;
	      ((tre_literal_t*)((*items)[i-1])->obj)->u.classt = classt;
	    }

	  /* Add opposite-case counterpoints if REG_ICASE is present.
	     This is broken if there are more than two "same" characters. */
	  if (ctx->cflags & REG_ICASE && !classt && status == REG_OK && !skip)
	    {
	      tre_cint_t cmin, ccurr;

	      DPRINT(("adding opposite-case counterpoints\n"));
	      while (min <= max)
		{
		  if (tre_islower(min))
		    {
		      cmin = ccurr = tre_toupper(min++);
		      while (tre_islower(min) && tre_toupper(min) == ccurr + 1
			     && min <= max)
			ccurr = tre_toupper(min++);
		      status = tre_new_item(ctx->mem, cmin, ccurr,
					    &i, &max_i, items);
		    }
		  else if (tre_isupper(min))
		    {
		      cmin = ccurr = tre_tolower(min++);
		      while (tre_isupper(min) && tre_tolower(min) == ccurr + 1
			     && min <= max)
			ccurr = tre_tolower(min++);
		      status = tre_new_item(ctx->mem, cmin, ccurr,
					    &i, &max_i, items);
		    }
		  else min++;
		  if (status != REG_OK)
		    break;
		}
	      if (status != REG_OK)
		break;
	    }
	}
    }
  *num_items = i;
  *items_size = max_i;
  ctx->re = re;
  return status;
}
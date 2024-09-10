static int
internal_function
FCT (const CHAR *pattern, const CHAR *string, const CHAR *string_end,
     bool no_leading_period, int flags)
{
  register const CHAR *p = pattern, *n = string;
  register UCHAR c;
#ifdef _LIBC
# if WIDE_CHAR_VERSION
  const char *collseq = (const char *)
    _NL_CURRENT(LC_COLLATE, _NL_COLLATE_COLLSEQWC);
# else
  const UCHAR *collseq = (const UCHAR *)
    _NL_CURRENT(LC_COLLATE, _NL_COLLATE_COLLSEQMB);
# endif
#endif

  while ((c = *p++) != L_('\0'))
    {
      bool new_no_leading_period = false;
      c = FOLD (c);

      switch (c)
	{
	case L_('?'):
	  if (__builtin_expect (flags & FNM_EXTMATCH, 0) && *p == '(')
	    {
	      int res;

	      res = EXT (c, p, n, string_end, no_leading_period,
			 flags);
	      if (res != -1)
		return res;
	    }

	  if (n == string_end)
	    return FNM_NOMATCH;
	  else if (*n == L_('/') && (flags & FNM_FILE_NAME))
	    return FNM_NOMATCH;
	  else if (*n == L_('.') && no_leading_period)
	    return FNM_NOMATCH;
	  break;

	case L_('\\'):
	  if (!(flags & FNM_NOESCAPE))
	    {
	      c = *p++;
	      if (c == L_('\0'))
		/* Trailing \ loses.  */
		return FNM_NOMATCH;
	      c = FOLD (c);
	    }
	  if (n == string_end || FOLD ((UCHAR) *n) != c)
	    return FNM_NOMATCH;
	  break;

	case L_('*'):
	  if (__builtin_expect (flags & FNM_EXTMATCH, 0) && *p == '(')
	    {
	      int res;

	      res = EXT (c, p, n, string_end, no_leading_period,
			 flags);
	      if (res != -1)
		return res;
	    }

	  if (n != string_end && *n == L_('.') && no_leading_period)
	    return FNM_NOMATCH;

	  for (c = *p++; c == L_('?') || c == L_('*'); c = *p++)
	    {
	      if (*p == L_('(') && (flags & FNM_EXTMATCH) != 0)
		{
		  const CHAR *endp = END (p);
		  if (endp != p)
		    {
		      /* This is a pattern.  Skip over it.  */
		      p = endp;
		      continue;
		    }
		}

	      if (c == L_('?'))
		{
		  /* A ? needs to match one character.  */
		  if (n == string_end)
		    /* There isn't another character; no match.  */
		    return FNM_NOMATCH;
		  else if (*n == L_('/')
			   && __builtin_expect (flags & FNM_FILE_NAME, 0))
		    /* A slash does not match a wildcard under
		       FNM_FILE_NAME.  */
		    return FNM_NOMATCH;
		  else
		    /* One character of the string is consumed in matching
		       this ? wildcard, so *??? won't match if there are
		       less than three characters.  */
		    ++n;
		}
	    }

	  if (c == L_('\0'))
	    /* The wildcard(s) is/are the last element of the pattern.
	       If the name is a file name and contains another slash
	       this means it cannot match, unless the FNM_LEADING_DIR
	       flag is set.  */
	    {
	      int result = (flags & FNM_FILE_NAME) == 0 ? 0 : FNM_NOMATCH;

	      if (flags & FNM_FILE_NAME)
		{
		  if (flags & FNM_LEADING_DIR)
		    result = 0;
		  else
		    {
		      if (MEMCHR (n, L_('/'), string_end - n) == NULL)
			result = 0;
		    }
		}

	      return result;
	    }
	  else
	    {
	      const CHAR *endp;

	      endp = MEMCHR (n, (flags & FNM_FILE_NAME) ? L_('/') : L_('\0'),
			     string_end - n);
	      if (endp == NULL)
		endp = string_end;

	      if (c == L_('[')
		  || (__builtin_expect (flags & FNM_EXTMATCH, 0) != 0
		      && (c == L_('@') || c == L_('+') || c == L_('!'))
		      && *p == L_('(')))
		{
		  int flags2 = ((flags & FNM_FILE_NAME)
				? flags : (flags & ~FNM_PERIOD));
		  bool no_leading_period2 = no_leading_period;

		  for (--p; n < endp; ++n, no_leading_period2 = false)
		    if (FCT (p, n, string_end, no_leading_period2, flags2)
			== 0)
		      return 0;
		}
	      else if (c == L_('/') && (flags & FNM_FILE_NAME))
		{
		  while (n < string_end && *n != L_('/'))
		    ++n;
		  if (n < string_end && *n == L_('/')
		      && (FCT (p, n + 1, string_end, flags & FNM_PERIOD, flags)
			  == 0))
		    return 0;
		}
	      else
		{
		  int flags2 = ((flags & FNM_FILE_NAME)
				? flags : (flags & ~FNM_PERIOD));
		  int no_leading_period2 = no_leading_period;

		  if (c == L_('\\') && !(flags & FNM_NOESCAPE))
		    c = *p;
		  c = FOLD (c);
		  for (--p; n < endp; ++n, no_leading_period2 = false)
		    if (FOLD ((UCHAR) *n) == c
			&& (FCT (p, n, string_end, no_leading_period2, flags2)
			    == 0))
		      return 0;
		}
	    }

	  /* If we come here no match is possible with the wildcard.  */
	  return FNM_NOMATCH;

	case L_('['):
	  {
	    /* Nonzero if the sense of the character class is inverted.  */
	    register bool not;
	    CHAR cold;
	    UCHAR fn;

	    if (posixly_correct == 0)
	      posixly_correct = getenv ("POSIXLY_CORRECT") != NULL ? 1 : -1;

	    if (n == string_end)
	      return FNM_NOMATCH;

	    if (*n == L_('.') && no_leading_period)
	      return FNM_NOMATCH;

	    if (*n == L_('/') && (flags & FNM_FILE_NAME))
	      /* `/' cannot be matched.  */
	      return FNM_NOMATCH;

	    not = (*p == L_('!') || (posixly_correct < 0 && *p == L_('^')));
	    if (not)
	      ++p;

	    fn = FOLD ((UCHAR) *n);

	    c = *p++;
	    for (;;)
	      {
		if (!(flags & FNM_NOESCAPE) && c == L_('\\'))
		  {
		    if (*p == L_('\0'))
		      return FNM_NOMATCH;
		    c = FOLD ((UCHAR) *p);
		    ++p;

		    if (c == fn)
		      goto matched;
		  }
		else if (c == L_('[') && *p == L_(':'))
		  {
		    /* Leave room for the null.  */
		    CHAR str[CHAR_CLASS_MAX_LENGTH + 1];
		    size_t c1 = 0;
#if defined _LIBC || WIDE_CHAR_SUPPORT
		    wctype_t wt;
#endif
		    const CHAR *startp = p;

		    for (;;)
		      {
			if (c1 == CHAR_CLASS_MAX_LENGTH)
			  /* The name is too long and therefore the pattern
			     is ill-formed.  */
			  return FNM_NOMATCH;

			c = *++p;
			if (c == L_(':') && p[1] == L_(']'))
			  {
			    p += 2;
			    break;
			  }
			if (c < L_('a') || c >= L_('z'))
			  {
			    /* This cannot possibly be a character class name.
			       Match it as a normal range.  */
			    p = startp;
			    c = L_('[');
			    goto normal_bracket;
			  }
			str[c1++] = c;
		      }
		    str[c1] = L_('\0');

#if defined _LIBC || WIDE_CHAR_SUPPORT
		    wt = IS_CHAR_CLASS (str);
		    if (wt == 0)
		      /* Invalid character class name.  */
		      return FNM_NOMATCH;

# if defined _LIBC && ! WIDE_CHAR_VERSION
		    /* The following code is glibc specific but does
		       there a good job in speeding up the code since
		       we can avoid the btowc() call.  */
		    if (_ISCTYPE ((UCHAR) *n, wt))
		      goto matched;
# else
		    if (ISWCTYPE (BTOWC ((UCHAR) *n), wt))
		      goto matched;
# endif
#else
		    if ((STREQ (str, L_("alnum")) && ISALNUM ((UCHAR) *n))
			|| (STREQ (str, L_("alpha")) && ISALPHA ((UCHAR) *n))
			|| (STREQ (str, L_("blank")) && ISBLANK ((UCHAR) *n))
			|| (STREQ (str, L_("cntrl")) && ISCNTRL ((UCHAR) *n))
			|| (STREQ (str, L_("digit")) && ISDIGIT ((UCHAR) *n))
			|| (STREQ (str, L_("graph")) && ISGRAPH ((UCHAR) *n))
			|| (STREQ (str, L_("lower")) && ISLOWER ((UCHAR) *n))
			|| (STREQ (str, L_("print")) && ISPRINT ((UCHAR) *n))
			|| (STREQ (str, L_("punct")) && ISPUNCT ((UCHAR) *n))
			|| (STREQ (str, L_("space")) && ISSPACE ((UCHAR) *n))
			|| (STREQ (str, L_("upper")) && ISUPPER ((UCHAR) *n))
			|| (STREQ (str, L_("xdigit")) && ISXDIGIT ((UCHAR) *n)))
		      goto matched;
#endif
		    c = *p++;
		  }
#ifdef _LIBC
		else if (c == L_('[') && *p == L_('='))
		  {
		    UCHAR str[1];
		    uint32_t nrules =
		      _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
		    const CHAR *startp = p;

		    c = *++p;
		    if (c == L_('\0'))
		      {
			p = startp;
			c = L_('[');
			goto normal_bracket;
		      }
		    str[0] = c;

		    c = *++p;
		    if (c != L_('=') || p[1] != L_(']'))
		      {
			p = startp;
			c = L_('[');
			goto normal_bracket;
		      }
		    p += 2;

		    if (nrules == 0)
		      {
			if ((UCHAR) *n == str[0])
			  goto matched;
		      }
		    else
		      {
			const int32_t *table;
# if WIDE_CHAR_VERSION
			const int32_t *weights;
			const int32_t *extra;
# else
			const unsigned char *weights;
			const unsigned char *extra;
# endif
			const int32_t *indirect;
			int32_t idx;
			const UCHAR *cp = (const UCHAR *) str;

			/* This #include defines a local function!  */
# if WIDE_CHAR_VERSION
#  include <locale/weightwc.h>
# else
#  include <locale/weight.h>
# endif

# if WIDE_CHAR_VERSION
			table = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEWC);
			weights = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_WEIGHTWC);
			extra = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_EXTRAWC);
			indirect = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_INDIRECTWC);
# else
			table = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
			weights = (const unsigned char *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_WEIGHTMB);
			extra = (const unsigned char *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_EXTRAMB);
			indirect = (const int32_t *)
			  _NL_CURRENT (LC_COLLATE, _NL_COLLATE_INDIRECTMB);
# endif

			idx = findidx (&cp);
			if (idx != 0)
			  {
			    /* We found a table entry.  Now see whether the
			       character we are currently at has the same
			       equivalance class value.  */
			    int len = weights[idx];
			    int32_t idx2;
			    const UCHAR *np = (const UCHAR *) n;

			    idx2 = findidx (&np);
			    if (idx2 != 0 && len == weights[idx2])
			      {
				int cnt = 0;

				while (cnt < len
				       && (weights[idx + 1 + cnt]
					   == weights[idx2 + 1 + cnt]))
				  ++cnt;

				if (cnt == len)
				  goto matched;
			      }
			  }
		      }

		    c = *p++;
		  }
#endif
		else if (c == L_('\0'))
		  /* [ (unterminated) loses.  */
		  return FNM_NOMATCH;
		else
		  {
		    bool is_range = false;

#ifdef _LIBC
		    bool is_seqval = false;

		    if (c == L_('[') && *p == L_('.'))
		      {
			uint32_t nrules =
			  _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
			const CHAR *startp = p;
			size_t c1 = 0;

			while (1)
			  {
			    c = *++p;
			    if (c == L_('.') && p[1] == L_(']'))
			      {
				p += 2;
				break;
			      }
			    if (c == '\0')
			      return FNM_NOMATCH;
			    ++c1;
			  }

			/* We have to handling the symbols differently in
			   ranges since then the collation sequence is
			   important.  */
			is_range = *p == L_('-') && p[1] != L_('\0');

			if (nrules == 0)
			  {
			    /* There are no names defined in the collation
			       data.  Therefore we only accept the trivial
			       names consisting of the character itself.  */
			    if (c1 != 1)
			      return FNM_NOMATCH;

			    if (!is_range && *n == startp[1])
			      goto matched;

			    cold = startp[1];
			    c = *p++;
			  }
			else
			  {
			    int32_t table_size;
			    const int32_t *symb_table;
# ifdef WIDE_CHAR_VERSION
			    char str[c1];
			    size_t strcnt;
# else
#  define str (startp + 1)
# endif
			    const unsigned char *extra;
			    int32_t idx;
			    int32_t elem;
			    int32_t second;
			    int32_t hash;

# ifdef WIDE_CHAR_VERSION
			    /* We have to convert the name to a single-byte
			       string.  This is possible since the names
			       consist of ASCII characters and the internal
			       representation is UCS4.  */
			    for (strcnt = 0; strcnt < c1; ++strcnt)
			      str[strcnt] = startp[1 + strcnt];
# endif

			    table_size =
			      _NL_CURRENT_WORD (LC_COLLATE,
						_NL_COLLATE_SYMB_HASH_SIZEMB);
			    symb_table = (const int32_t *)
			      _NL_CURRENT (LC_COLLATE,
					   _NL_COLLATE_SYMB_TABLEMB);
			    extra = (const unsigned char *)
			      _NL_CURRENT (LC_COLLATE,
					   _NL_COLLATE_SYMB_EXTRAMB);

			    /* Locate the character in the hashing table.  */
			    hash = elem_hash (str, c1);

			    idx = 0;
			    elem = hash % table_size;
			    second = hash % (table_size - 2);
			    while (symb_table[2 * elem] != 0)
			      {
				/* First compare the hashing value.  */
				if (symb_table[2 * elem] == hash
				    && c1 == extra[symb_table[2 * elem + 1]]
				    && memcmp (str,
					       &extra[symb_table[2 * elem + 1]
						     + 1], c1) == 0)
				  {
				    /* Yep, this is the entry.  */
				    idx = symb_table[2 * elem + 1];
				    idx += 1 + extra[idx];
				    break;
				  }

				/* Next entry.  */
				elem += second;
			      }

			    if (symb_table[2 * elem] != 0)
			      {
				/* Compare the byte sequence but only if
				   this is not part of a range.  */
# ifdef WIDE_CHAR_VERSION
				int32_t *wextra;

				idx += 1 + extra[idx];
				/* Adjust for the alignment.  */
				idx = (idx + 3) & ~3;

				wextra = (int32_t *) &extra[idx + 4];
# endif

				if (! is_range)
				  {
# ifdef WIDE_CHAR_VERSION
				    for (c1 = 0;
					 (int32_t) c1 < wextra[idx];
					 ++c1)
				      if (n[c1] != wextra[1 + c1])
					break;

				    if ((int32_t) c1 == wextra[idx])
				      goto matched;
# else
				    for (c1 = 0; c1 < extra[idx]; ++c1)
				      if (n[c1] != extra[1 + c1])
					break;

				    if (c1 == extra[idx])
				      goto matched;
# endif
				  }

				/* Get the collation sequence value.  */
				is_seqval = true;
# ifdef WIDE_CHAR_VERSION
				cold = wextra[1 + wextra[idx]];
# else
				/* Adjust for the alignment.  */
				idx += 1 + extra[idx];
				idx = (idx + 3) & ~4;
				cold = *((int32_t *) &extra[idx]);
# endif

				c = *p++;
			      }
			    else if (c1 == 1)
			      {
				/* No valid character.  Match it as a
				   single byte.  */
				if (!is_range && *n == str[0])
				  goto matched;

				cold = str[0];
				c = *p++;
			      }
			    else
			      return FNM_NOMATCH;
			  }
		      }
		    else
# undef str
#endif
		      {
			c = FOLD (c);
		      normal_bracket:

			/* We have to handling the symbols differently in
			   ranges since then the collation sequence is
			   important.  */
			is_range = (*p == L_('-') && p[1] != L_('\0')
				    && p[1] != L_(']'));

			if (!is_range && c == fn)
			  goto matched;

			cold = c;
			c = *p++;
		      }

		    if (c == L_('-') && *p != L_(']'))
		      {
#if _LIBC
			/* We have to find the collation sequence
			   value for C.  Collation sequence is nothing
			   we can regularly access.  The sequence
			   value is defined by the order in which the
			   definitions of the collation values for the
			   various characters appear in the source
			   file.  A strange concept, nowhere
			   documented.  */
			uint32_t fcollseq;
			uint32_t lcollseq;
			UCHAR cend = *p++;

# ifdef WIDE_CHAR_VERSION
			/* Search in the `names' array for the characters.  */
			fcollseq = __collseq_table_lookup (collseq, fn);
			if (fcollseq == ~((uint32_t) 0))
			  /* XXX We don't know anything about the character
			     we are supposed to match.  This means we are
			     failing.  */
			  goto range_not_matched;

			if (is_seqval)
			  lcollseq = cold;
			else
			  lcollseq = __collseq_table_lookup (collseq, cold);
# else
			fcollseq = collseq[fn];
			lcollseq = is_seqval ? cold : collseq[(UCHAR) cold];
# endif

			is_seqval = false;
			if (cend == L_('[') && *p == L_('.'))
			  {
			    uint32_t nrules =
			      _NL_CURRENT_WORD (LC_COLLATE,
						_NL_COLLATE_NRULES);
			    const CHAR *startp = p;
			    size_t c1 = 0;

			    while (1)
			      {
				c = *++p;
				if (c == L_('.') && p[1] == L_(']'))
				  {
				    p += 2;
				    break;
				  }
				if (c == '\0')
				  return FNM_NOMATCH;
				++c1;
			      }

			    if (nrules == 0)
			      {
				/* There are no names defined in the
				   collation data.  Therefore we only
				   accept the trivial names consisting
				   of the character itself.  */
				if (c1 != 1)
				  return FNM_NOMATCH;

				cend = startp[1];
			      }
			    else
			      {
				int32_t table_size;
				const int32_t *symb_table;
# ifdef WIDE_CHAR_VERSION
				char str[c1];
				size_t strcnt;
# else
#  define str (startp + 1)
# endif
				const unsigned char *extra;
				int32_t idx;
				int32_t elem;
				int32_t second;
				int32_t hash;

# ifdef WIDE_CHAR_VERSION
				/* We have to convert the name to a single-byte
				   string.  This is possible since the names
				   consist of ASCII characters and the internal
				   representation is UCS4.  */
				for (strcnt = 0; strcnt < c1; ++strcnt)
				  str[strcnt] = startp[1 + strcnt];
# endif

				table_size =
				  _NL_CURRENT_WORD (LC_COLLATE,
						    _NL_COLLATE_SYMB_HASH_SIZEMB);
				symb_table = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_SYMB_TABLEMB);
				extra = (const unsigned char *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_SYMB_EXTRAMB);

				/* Locate the character in the hashing
                                   table.  */
				hash = elem_hash (str, c1);

				idx = 0;
				elem = hash % table_size;
				second = hash % (table_size - 2);
				while (symb_table[2 * elem] != 0)
				  {
				/* First compare the hashing value.  */
				    if (symb_table[2 * elem] == hash
					&& (c1
					    == extra[symb_table[2 * elem + 1]])
					&& memcmp (str,
						   &extra[symb_table[2 * elem + 1]
							 + 1], c1) == 0)
				      {
					/* Yep, this is the entry.  */
					idx = symb_table[2 * elem + 1];
					idx += 1 + extra[idx];
					break;
				      }

				    /* Next entry.  */
				    elem += second;
				  }

				if (symb_table[2 * elem] != 0)
				  {
				    /* Compare the byte sequence but only if
				       this is not part of a range.  */
# ifdef WIDE_CHAR_VERSION
				    int32_t *wextra;

				    idx += 1 + extra[idx];
				    /* Adjust for the alignment.  */
				    idx = (idx + 3) & ~4;

				    wextra = (int32_t *) &extra[idx + 4];
# endif
				    /* Get the collation sequence value.  */
				    is_seqval = true;
# ifdef WIDE_CHAR_VERSION
				    cend = wextra[1 + wextra[idx]];
# else
				    /* Adjust for the alignment.  */
				    idx += 1 + extra[idx];
				    idx = (idx + 3) & ~4;
				    cend = *((int32_t *) &extra[idx]);
# endif
				  }
				else if (symb_table[2 * elem] != 0 && c1 == 1)
				  {
				    cend = str[0];
				    c = *p++;
				  }
				else
				  return FNM_NOMATCH;
			      }
# undef str
			  }
			else
			  {
			    if (!(flags & FNM_NOESCAPE) && cend == L_('\\'))
			      cend = *p++;
			    if (cend == L_('\0'))
			      return FNM_NOMATCH;
			    cend = FOLD (cend);
			  }

			/* XXX It is not entirely clear to me how to handle
			   characters which are not mentioned in the
			   collation specification.  */
			if (
# ifdef WIDE_CHAR_VERSION
			    lcollseq == 0xffffffff ||
# endif
			    lcollseq <= fcollseq)
			  {
			    /* We have to look at the upper bound.  */
			    uint32_t hcollseq;

			    if (is_seqval)
			      hcollseq = cend;
			    else
			      {
# ifdef WIDE_CHAR_VERSION
				hcollseq =
				  __collseq_table_lookup (collseq, cend);
				if (hcollseq == ~((uint32_t) 0))
				  {
				    /* Hum, no information about the upper
				       bound.  The matching succeeds if the
				       lower bound is matched exactly.  */
				    if (lcollseq != fcollseq)
				      goto range_not_matched;

				    goto matched;
				  }
# else
				hcollseq = collseq[cend];
# endif
			      }

			    if (lcollseq <= hcollseq && fcollseq <= hcollseq)
			      goto matched;
			  }
# ifdef WIDE_CHAR_VERSION
		      range_not_matched:
# endif
#else
			/* We use a boring value comparison of the character
			   values.  This is better than comparing using
			   `strcoll' since the latter would have surprising
			   and sometimes fatal consequences.  */
			UCHAR cend = *p++;

			if (!(flags & FNM_NOESCAPE) && cend == L_('\\'))
			  cend = *p++;
			if (cend == L_('\0'))
			  return FNM_NOMATCH;

			/* It is a range.  */
			if (cold <= fn && fn <= cend)
			  goto matched;
#endif

			c = *p++;
		      }
		  }

		if (c == L_(']'))
		  break;
	      }

	    if (!not)
	      return FNM_NOMATCH;
	    break;

	  matched:
	    /* Skip the rest of the [...] that already matched.  */
	    do
	      {
	      ignore_next:
		c = *p++;

		if (c == L_('\0'))
		  /* [... (unterminated) loses.  */
		  return FNM_NOMATCH;

		if (!(flags & FNM_NOESCAPE) && c == L_('\\'))
		  {
		    if (*p == L_('\0'))
		      return FNM_NOMATCH;
		    /* XXX 1003.2d11 is unclear if this is right.  */
		    ++p;
		  }
		else if (c == L_('[') && *p == L_(':'))
		  {
		    int c1 = 0;
		    const CHAR *startp = p;

		    while (1)
		      {
			c = *++p;
			if (++c1 == CHAR_CLASS_MAX_LENGTH)
			  return FNM_NOMATCH;

			if (*p == L_(':') && p[1] == L_(']'))
			  break;

			if (c < L_('a') || c >= L_('z'))
			  {
			    p = startp;
			    goto ignore_next;
			  }
		      }
		    p += 2;
		    c = *p++;
		  }
		else if (c == L_('[') && *p == L_('='))
		  {
		    c = *++p;
		    if (c == L_('\0'))
		      return FNM_NOMATCH;
		    c = *++p;
		    if (c != L_('=') || p[1] != L_(']'))
		      return FNM_NOMATCH;
		    p += 2;
		    c = *p++;
		  }
		else if (c == L_('[') && *p == L_('.'))
		  {
		    ++p;
		    while (1)
		      {
			c = *++p;
			if (c == '\0')
			  return FNM_NOMATCH;

			if (*p == L_('.') && p[1] == L_(']'))
			  break;
		      }
		    p += 2;
		    c = *p++;
		  }
	      }
	    while (c != L_(']'));
	    if (not)
	      return FNM_NOMATCH;
	  }
	  break;

	case L_('+'):
	case L_('@'):
	case L_('!'):
	  if (__builtin_expect (flags & FNM_EXTMATCH, 0) && *p == '(')
	    {
	      int res;

	      res = EXT (c, p, n, string_end, no_leading_period, flags);
	      if (res != -1)
		return res;
	    }
	  goto normal_match;

	case L_('/'):
	  if (NO_LEADING_PERIOD (flags))
	    {
	      if (n == string_end || c != (UCHAR) *n)
		return FNM_NOMATCH;

	      new_no_leading_period = true;
	      break;
	    }
	  /* FALLTHROUGH */
	default:
	normal_match:
	  if (n == string_end || c != FOLD ((UCHAR) *n))
	    return FNM_NOMATCH;
	}

      no_leading_period = new_no_leading_period;
      ++n;
    }

  if (n == string_end)
    return 0;

  if ((flags & FNM_LEADING_DIR) && n != string_end && *n == L_('/'))
    /* The FNM_LEADING_DIR flag says that "foo*" matches "foobar/frobozz".  */
    return 0;

  return FNM_NOMATCH;
}
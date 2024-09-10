/* given the bounds of a particular subscript (assumed correct), we convert the subscript into
 * a form that mimics the GDS representation of that subscript
 */
boolean_t convert_key_to_db(mval *gvn, int start, int stop, gv_key *gvkey, unsigned char **key)
{
	mval 		tmpval, *mvptr, dollarcharmval;
	int 		isrc;
	char		strbuff[MAX_KEY_SZ + 1], *str, *str_top;
	char 		fnname[MAX_LEN_FOR_CHAR_FUNC], *c;
	boolean_t	is_zchar;
	int4		num;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	if (ISDIGIT_ASCII(gvn->str.addr[start]) ||
		'-' == gvn->str.addr[start] || '+' == gvn->str.addr[start] || '.' == gvn->str.addr[start])
	{	/* convert a number */
		tmpval.str.addr = &gvn->str.addr[start];
		tmpval.str.len 	= stop - start;
		tmpval.mvtype = MV_STR;
		mvptr = &tmpval;
		MV_FORCE_NUM(mvptr);
		if (MVTYPE_IS_NUM_APPROX(tmpval.mvtype))
			return FALSE;
		mval2subsc(&tmpval, gvkey, gv_cur_region->std_null_coll);
	} else
	{	/* It's a string. We need to accept strings, $CHAR args, and $ZCHAR args. */
		str = &strbuff[0];
		str_top = &strbuff[0] + MAX_KEY_SZ + 1;
		/* MV_NUM_APPROX needed by mval2subsc to skip val_iscan call */
		tmpval.mvtype = (MV_STR | MV_NUM_APPROX);
		for (isrc = start; isrc < stop; )
		{
			if ('_' == gvn->str.addr[isrc])
			{	/* We can skip this case, since we're already "appending"
				 * the strings on the lhs to the string on the rhs. */
				isrc++;
			} else if ('$' == gvn->str.addr[isrc])
			{	/* We determine if what comes after is a Char or a ZCHar,
				 * and copy over accordingly */
				c = &fnname[0];
				isrc++; /* skip the '$' */
				while ('(' != gvn->str.addr[isrc])
					*c++ = TOUPPER(gvn->str.addr[isrc++]);
				*c = '\0';
				assert(strlen(c) <= MAX_LEN_FOR_CHAR_FUNC - 1);
				if (!MEMCMP_LIT(fnname, "ZCHAR") || !MEMCMP_LIT(fnname, "ZCH"))
					is_zchar = TRUE;
				else if (!MEMCMP_LIT(fnname, "CHAR") || !MEMCMP_LIT(fnname, "C"))
					is_zchar = FALSE;
				else
					assert(FALSE);
				/* Parse the arguments */
				isrc++; /* skip the '(' */
				while (TRUE)
				{	/* Inside the argument list for $[Z]CHAR */
					/* STRTOUL will stop at the ',' or ')' */
					num = (int4)STRTOUL(&gvn->str.addr[isrc], NULL, 10);
#					ifdef UNICODE_SUPPORTED
					if (!is_zchar && is_gtm_chset_utf8)
						op_fnchar(2, &dollarcharmval, num);
					else
#					endif
						op_fnzchar(2, &dollarcharmval, num);
					assert(MV_IS_STRING(&dollarcharmval));
					if (dollarcharmval.str.len)
					{
						if (str + dollarcharmval.str.len > str_top)
							/* String overflows capacity. */
							return FALSE;
						memcpy(str, dollarcharmval.str.addr, dollarcharmval.str.len);
						str += dollarcharmval.str.len;
					}
					/* move on to the next argument */
					while (',' != gvn->str.addr[isrc] && ')' != gvn->str.addr[isrc])
						isrc++;
					if (',' == gvn->str.addr[isrc])
						isrc++;
					else
					{
						assert(')' == gvn->str.addr[isrc]);
						isrc++; /* skip ')' */
						break;
					}
				}
			} else if ('"' == gvn->str.addr[isrc])
			{	/* Assume valid string. */
				isrc++;
				while (isrc < stop && !('"' == gvn->str.addr[isrc] && '"' != gvn->str.addr[isrc+1]))
				{
					if (str == str_top)
						/* String overflows capacity. */
						return FALSE;
					if ('"' == gvn->str.addr[isrc] && '"' == gvn->str.addr[isrc+1])
					{
						*str++ = '"';
						isrc += 2;
					} else
						*str++ = gvn->str.addr[isrc++];
				}
				isrc++; /* skip over '"' */
			} else
				assert(FALSE);
		}
		tmpval.str.addr = strbuff;
		tmpval.str.len 	= str - strbuff;
		DEBUG_ONLY(TREF(skip_mv_num_approx_assert) = TRUE;)
		mval2subsc(&tmpval, gvkey, gv_cur_region->std_null_coll);
		DEBUG_ONLY(TREF(skip_mv_num_approx_assert) = FALSE;)
	}
void	get_frame_place_mcode(int level, stack_mode_t mode, int cur_zlevel, mval *result)
{
	int		count;
	stack_frame	*fp;
	unsigned char	pos_str[MAX_ENTRYREF_LEN];
	mval		label;
	mval		routine;
	int		ips;
	int		offset;
	int		s1, s2;
	boolean_t	indirect_frame;
	ihdtyp		*irtnhdr;
	cache_entry	*indce;
	INTPTR_T	*vp;
  	unsigned char	*fpmpc;

	assert(DOLLAR_STACK_PLACE == mode || DOLLAR_STACK_MCODE == mode);
	assert(0 <= level);
	assert(level < cur_zlevel);
	count = cur_zlevel;
	for (fp = frame_pointer;  ; fp = fp->old_frame_pointer)
	{
		if (NULL == fp->old_frame_pointer)
		{
			if (fp->type & SFT_TRIGR)
				/* Have a trigger baseframe, pick up stack continuation frame_pointer stored by base_frame() */
				fp = *(stack_frame **)(fp + 1);
			else
			{	/* Something wrong, just return null or assert if debug mode */
				assert(FALSE);
				result->str.len = 0;
				return;
			}
		}
		assert(NULL != fp);
		if (!(fp->type & SFT_COUNT))
			continue;
		count--;
		if (count == level)
			break;
	}
	fpmpc = fp->mpc;
	if (ADDR_IN_CODE(fpmpc, fp->rvector))
	{
		result->str.addr = (char *)&pos_str[0];
		result->str.len = INTCAST(symb_line(fpmpc, &pos_str[0], 0, fp->rvector) - &pos_str[0]);
		indirect_frame = FALSE;
	} else
	{
		indirect_frame = TRUE;
		pos_str[0] = '@';
		result->str.addr = (char *)&pos_str[0];
		result->str.len = 1;
	}
	if (DOLLAR_STACK_PLACE == mode)
	{
		if (result->str.len)
		{
			s2pool(&result->str);
			assert(((unsigned char *)result->str.addr + result->str.len) == stringpool.free);
		}
	}
	if (DOLLAR_STACK_MCODE == mode)
	{
		if (!indirect_frame)
		{
			if (IS_GTM_IMAGE || (0 < level))
			{
				label.mvtype = MV_STR;
				routine.mvtype = MV_STR;
				result->mvtype = MV_STR;
				label.str.len = result->str.len;
				label.str.addr = (char *)&pos_str[0];
				routine.str.len = 0;
				for (ips = 0, s1 = s2 = -1; ips < result->str.len; ips++)
				{
					if ('+' == pos_str[ips])
					{
						assert((-1 == s1) && (-1 == s2));
						s1 = ips;
					}
					if ('^' == pos_str[ips])
					{
						s2 = ips;
						break;
					}
				}
				if (s2 >= 0)
				{
					routine.str.addr = (char *)&pos_str[s2 + 1];
					routine.str.len = result->str.len - s2 - 1;
					label.str.len = s2;
				}
				offset = 0;
				if (s1 >= 0)
				{
					label.str.len = s1;
					if (s2 < 0)
						s2 = result->str.len;
					for (ips = s1 + 1; ips < s2; ips++)
						offset = offset * 10 + pos_str[ips] - '0';
				}
				op_fntext(&label, offset, &routine, result);
			} else
			{	/* Utility base frame does not have source code */
				result->str.addr = UTIL_BASE_FRAME_CODE;
				result->str.len = STRLEN(UTIL_BASE_FRAME_CODE);
			}
		} else
		{	/* code picked up from cache_cleanup(). any changes here might need to be reflected there */
			vp = (INTPTR_T *)fp->ctxt;
			assert(NULL != vp);
			vp--;
			if ((GTM_OMAGIC << 16) + OBJ_LABEL != *vp)	/* Validate backward linkage */
				GTMASSERT;
			vp--;
			irtnhdr = (ihdtyp *)((char *)vp + *vp);
			indce = irtnhdr->indce;
			assert(NULL != indce);
			assert(0 < indce->refcnt);	/* currently used in the M stack better have a non-zero refcnt */
			result->str = indce->src.str;
			s2pool(&result->str);
			assert(((unsigned char *)result->str.addr + result->str.len) == stringpool.free);
		}
	}
	return;
}
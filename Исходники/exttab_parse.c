callin_entry_list*	citab_parse (void)
{
	int			parameter_count, i, fclose_res;
	uint4			inp_mask, out_mask, mask;
	mstr			labref, callnam;
	enum xc_types		ret_tok, parameter_types[MAXIMUM_PARAMETERS], pr;
	char			str_buffer[MAX_TABLINE_LEN], *tbp, *end;
	FILE			*ext_table_file_handle;
	callin_entry_list	*entry_ptr, *save_entry_ptr = 0;

	error_def(ERR_CITABENV);
	error_def(ERR_CITABOPN);
	error_def(ERR_CIENTNAME);
	error_def(ERR_COLON);
	error_def(ERR_CIRTNTYP);
	error_def(ERR_CIRCALLNAME);
	error_def(ERR_CIDIRECTIVE);
	error_def(ERR_CIRPARMNAME);
	error_def(ERR_CIPARTYPE);
	error_def(ERR_CIUNTYPE);
	error_def(ERR_SYSCALL);
	error_def(ERR_CIMAXPARAM);

	ext_table_file_name = GETENV(CALLIN_ENV_NAME);
	if (!ext_table_file_name) /* environment variable not set */
		rts_error(VARLSTCNT(4) ERR_CITABENV, 2, LEN_AND_STR(CALLIN_ENV_NAME));

	ext_table_file_handle = Fopen(ext_table_file_name, "r");
	if (!ext_table_file_handle) /* call-in table not found */
		rts_error(VARLSTCNT(11) ERR_CITABOPN, 2, LEN_AND_STR(ext_table_file_name),
			  ERR_SYSCALL, 5, LEN_AND_LIT("fopen"), CALLFROM, errno);
	ext_source_line_num = 0;
	while (read_table(LIT_AND_LEN(str_buffer), ext_table_file_handle))
	{
		if (!*(tbp = scan_space(str_buffer)))
			continue;
		if (!(end = scan_ident(tbp)))
			ext_stx_error(ERR_CIRCALLNAME, ext_table_file_name);
		callnam.addr = tbp;
		callnam.len = INTCAST(end - tbp);
		tbp = scan_space(end);
		if (':' != *tbp++)
			ext_stx_error(ERR_COLON, ext_table_file_name);
		ret_tok = scan_keyword(&tbp); /* return type */
		switch (ret_tok) /* return type valid ? */
		{
			case xc_void:
			case xc_char_star:
			case xc_int_star:
			case xc_uint_star:
			case xc_long_star:
			case xc_ulong_star:
			case xc_float_star:
			case xc_double_star:
			case xc_string_star:
				break;
			default:
				ext_stx_error(ERR_CIRTNTYP, ext_table_file_name);
		}
		labref.addr = tbp;
		if ((end = scan_labelref(tbp)))
			labref.len = INTCAST(end - tbp);
		else
			ext_stx_error(ERR_CIENTNAME, ext_table_file_name);
		tbp = scan_space(end);
		inp_mask = out_mask = 0;
		for (parameter_count = 0; (*tbp && ')' != *tbp); parameter_count++)
		{
			if (MAXIMUM_PARAMETERS <= parameter_count)
				ext_stx_error(ERR_CIMAXPARAM, ext_table_file_name);
			/* must have comma if this is not the first parameter, otherwise '(' */
			if (((0 == parameter_count)?'(':',') != *tbp++)
				ext_stx_error(ERR_CIRPARMNAME, ext_table_file_name);
			tbp = scan_space(tbp);
			if ((0 == parameter_count) && (*tbp == ')')) /* special case () */
				break;
			/* looking for an I, a O or an IO */
			mask = (1 << parameter_count);
			inp_mask |= ('I' == *tbp) ? (tbp++, mask) : 0;
			out_mask |= ('O' == *tbp) ? (tbp++, mask) : 0;
			if ((!(inp_mask & mask) && !(out_mask & mask)) || (':' != *tbp++))
				ext_stx_error(ERR_CIDIRECTIVE, ext_table_file_name);
			switch ((pr = scan_keyword(&tbp))) /* valid param type? */
			{
				case xc_int:
				case xc_uint:
				case xc_long:
				case xc_ulong:
				case xc_float:
				case xc_double:
					if (out_mask & mask)
						ext_stx_error(ERR_CIPARTYPE, ext_table_file_name);
					/* fall-thru */
				case xc_char_star:
				case xc_int_star:
				case xc_uint_star:
				case xc_long_star:
				case xc_ulong_star:
				case xc_float_star:
				case xc_double_star:
				case xc_string_star:
					break;
				default:
					ext_stx_error(ERR_CIUNTYPE, ext_table_file_name);
			}
			parameter_types[parameter_count] = pr;
			tbp = scan_space(tbp);
		}
		if (!*tbp)
			ext_stx_error(ERR_CIRPARMNAME, ext_table_file_name);
		entry_ptr = get_memory(sizeof(callin_entry_list));
		entry_ptr->next_entry = save_entry_ptr;
		save_entry_ptr = entry_ptr;
		entry_ptr->return_type = ret_tok;
		entry_ptr->argcnt = parameter_count;
		entry_ptr->input_mask = inp_mask;
		entry_ptr->output_mask = out_mask;
		entry_ptr->parms = get_memory(parameter_count * sizeof(entry_ptr->parms[0]));
		for (i = 0 ;  i < parameter_count ;  i++)
			entry_ptr->parms[i] = parameter_types[i];
		put_mstr(&labref, &entry_ptr->label_ref);
		put_mstr(&callnam, &entry_ptr->call_name);
	}
	FCLOSE(ext_table_file_handle, fclose_res);
	return entry_ptr;
}
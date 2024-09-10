CC_STRING CMaExpander::TryExpand()
{
	CToken token;
	CC_STRING outs;
	static int debug_level;
	CC_STRING saved_inStr = inStr;

	debug_level++;


	while(1) {
		const char *const last_pos  = pos;

		IgnoreSpaces();
		if( ! get_token(tc, &pos, &token, for_include) )
			break;
		if( token.attr == CToken::TA_IDENT ) {
			CMacro *ma;
			CC_STRING tmp;
			ma = GetMacro(token.id);
			if( IS_MACRO(ma) && ! in_defined_context() ) {
				if( IS_FLM(ma) ) {
					skip_blanks(pos);
					if( *pos == '(' ) {
						tmp = Expand_FLM(ma);
					}
					else
						goto do_cat;
				} else {
					tmp = Expand_OLM(ma);
				}

				const ssize_t offset = last_pos - inStr.c_str();
				CC_STRING newStr;
				
				newStr.strcat(inStr.c_str(), last_pos);
				newStr += tmp;
				newStr += pos;
				
				inStr = newStr;
				pos   = inStr.c_str() + offset;
			} else
				goto do_cat;
		} else {
		do_cat:
			outs.strcat(last_pos, pos);
		}
		last_ids[0] = last_ids[1];
		last_ids[1] = token.id;
	}

//	printf("Leave [%u] %s\n", debug_level, outs.c_str());
	--debug_level;
//	fprintf(stderr, "*** %u: %s => %s\n", debug_level, saved_inStr.c_str(), outs.c_str());

	return outs;
}
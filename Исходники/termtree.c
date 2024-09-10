int tokenize_term(const char* str, int level, struct termtree_t *tree) {

	struct level_specific_opfuncs {
		const char operators[2];
		mathfuncptr funcs[2];
	};

	static const struct level_specific_opfuncs level_ops[3] = 
	{ {{'+', '-'}, {f_add, f_sub}}, {{'*', '/'}, {f_mul, f_div}}, {{'^', '%'}, {f_pow, f_mod}} };

	if (!strlen(str)) return 0;
	*tree = termtree_create(level);

	struct level_specific_opfuncs of = level_ops[level];

	int term_beg_pos = 0;
	int i = 0;
	size_t term_str_len = strlen(str);

	#define OPERATOR(c) ((c) == of.operators[0] || (c) == of.operators[1])

	char last_char = str[term_str_len-1];
	if (OPERATOR(last_char)) {
		parse_error(ERR_BAD_OPERATOR, str, term_str_len-1);
		return -1;
	}

	for (; i < term_str_len; ++i) {
		char c = str[i];

		while (!(OPERATOR(c)) && i < term_str_len) {
			if (c == '(') {
				int par_end = find_matching_parenthesis(str, i);
				if (par_end < 0) { parse_error(ERR_BAD_PARENTHESIS, str, i); return -1; }
				else i = par_end;	// skip to par_end
			}
			++i;
			c = str[i];
		}
		
		int term_end_pos = i;
		int subterm_length = term_end_pos - term_beg_pos;

		if (subterm_length <= 0 && level > 0) {
			// an expression such as '5++--+-+--+-5' is considered to be syntactically valid,
			// while '5^*//****///5' isn't (hence the level>0 criterion)

			parse_error(ERR_BAD_OPERATOR, str, i);
			return -1;
		}

		// TODO: consider an early-out for L0 subterms with length 0.

		char *subterm = substring(str, term_beg_pos, subterm_length);

		mathfuncptr f = NULL;
		if (c == of.operators[0]) { f = of.funcs[0]; }
		else if (c == of.operators[1]) { f = of.funcs[1]; }

		int reparse = 0;

		if (term_has_strippable_parentheses(subterm)) {
			if (strlen(subterm) <= 2) { parse_error(ERR_BAD_PARENTHESIS, subterm, i); return -1; }
			char *subterm_stripped = strip_surrounding_parentheses(subterm);
			sa_free(subterm);
			subterm = subterm_stripped;
			reparse = 1;	// had parentheses -> needs full re-evaluation
		}

		termtree_add(tree, subterm, f, reparse);
		sa_free(subterm);

		term_beg_pos = i+1;
	
	}

	return tree->num_terms;

}
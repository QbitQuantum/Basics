static void
def_union(definition *defp)
{
	token tok;
	declaration dec;
	case_list *cases;
	case_list **tailp;

	defp->def_kind = DEF_UNION;
	scan(TOK_IDENT, &tok);
	defp->def_name = tok.str;
	scan(TOK_SWITCH, &tok);
	scan(TOK_LPAREN, &tok);
	get_declaration(&dec, DEF_UNION);
	defp->def.un.enum_decl = dec;
	tailp = &defp->def.un.cases;
	scan(TOK_RPAREN, &tok);
	scan(TOK_LBRACE, &tok);
	scan(TOK_CASE, &tok);
	while (tok.kind == TOK_CASE) {
		scan(TOK_IDENT, &tok);
		cases = ALLOC(case_list);
		cases->case_name = tok.str;
		scan(TOK_COLON, &tok);
		get_declaration(&dec, DEF_UNION);
		cases->case_decl = dec;
		*tailp = cases;
		tailp = &cases->next;
		scan(TOK_SEMICOLON, &tok);
		scan3(TOK_CASE, TOK_DEFAULT, TOK_RBRACE, &tok);
	}
	*tailp = NULL;
	if (tok.kind == TOK_DEFAULT) {
		scan(TOK_COLON, &tok);
		get_declaration(&dec, DEF_UNION);
		defp->def.un.default_decl = ALLOC(declaration);
		*defp->def.un.default_decl = dec;
		scan(TOK_SEMICOLON, &tok);
		scan(TOK_RBRACE, &tok);
	} else {
		defp->def.un.default_decl = NULL;
	}
}
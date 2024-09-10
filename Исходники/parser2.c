static AST vardecls(AST vdl, AST fdl) {
    Token *t = &tok;
    AST a=0;
    AST a1=0;
    bool isfuncdecl = false;

    while (true) {
	if (!isprimtype(t->sym) && !isclasstype() && !isstructtype()) break;
	a1 = vardecl();
	if (a1 && nodetype(a1) == nFUNCDECL) /* expect var, but it was func */
	{ isfuncdecl = true; break; }
	if (a1) vdl = append_list(vdl, a1);

	if (t->sym == ';') gettoken();
	else parse_error("expected ;");
    }

    if (isfuncdecl) {
	fdl = append_list(fdl, a1);    /* add first elem of fdl */
    }

    return vdl;
}
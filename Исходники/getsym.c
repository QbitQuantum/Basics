void hoc_execstr(const char* cp) {
	Symbol *sp;
	Symlist *symlist = (Symlist *)0;
	Inst *pcsav;
	char s[256];

	Sprintf(s, "{%s}\n", cp);
	sp = hoc_install("", PROCEDURE, 0., &symlist);
	sp->u.u_proc->defn.in = STOP;
	sp->u.u_proc->list = (Symlist *)0;
	sp->u.u_proc->nauto = 0;
	IGNORE(hoc_xopen_run(sp, s));
	pcsav = hoc_pc;
	hoc_execute(sp->u.u_proc->defn.in);
	hoc_pc = pcsav;
	hoc_free_list(&symlist);
}	
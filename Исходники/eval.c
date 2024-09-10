void
evaltree(union node *n, int flags)
{
	if (n == NULL) {
		TRACE(("evaltree(NULL) called\n"));
		exitstatus = 0;
		goto out;
	}
#ifdef WITH_HISTORY
	displayhist = 1;	/* show history substitutions done with fc */
#endif
	TRACE(("pid %d, evaltree(%p: %d, %d) called\n",
	    getpid(), n, n->type, flags));
	switch (n->type) {
	case NSEMI:
		evaltree(n->nbinary.ch1, flags & EV_TESTED);
		if (evalskip)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NAND:
		evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip || exitstatus != 0)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NOR:
		evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip || exitstatus == 0)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NREDIR:
		expredir(n->nredir.redirect);
		redirect(n->nredir.redirect, REDIR_PUSH);
		evaltree(n->nredir.n, flags);
		popredir();
		break;
	case NSUBSHELL:
		evalsubshell(n, flags);
		break;
	case NBACKGND:
		evalsubshell(n, flags);
		break;
	case NIF: {
		evaltree(n->nif.test, EV_TESTED);
		if (evalskip)
			goto out;
		if (exitstatus == 0)
			evaltree(n->nif.ifpart, flags);
		else if (n->nif.elsepart)
			evaltree(n->nif.elsepart, flags);
		else
			exitstatus = 0;
		break;
	}
	case NWHILE:
	case NUNTIL:
		evalloop(n, flags);
		break;
	case NFOR:
		evalfor(n, flags);
		break;
	case NCASE:
		evalcase(n, flags);
		break;
	case NDEFUN:
		defun(n->narg.text, n->narg.next);
		exitstatus = 0;
		break;
	case NNOT:
		evaltree(n->nnot.com, EV_TESTED);
		exitstatus = !exitstatus;
		break;
	case NPIPE:
		evalpipe(n);
		break;
	case NCMD:
		evalcommand(n, flags, (struct backcmd *)NULL);
		break;
	default:
		out1fmt("Node type = %d\n", n->type);
		flushout(&output);
		break;
	}
out:
	if (pendingsigs)
		dotrap();
	if ((flags & EV_EXIT) != 0)
		exitshell(exitstatus);
}
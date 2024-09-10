extern List *glom(Node *n) {
	List *v, *head, *tail;
	Node *words;
	if (n == NULL)
		return NULL;
	switch (n->type) {
	case nArgs:
	case nLappend:
		words = n->u[0].p;
		tail = NULL;
		while (words != NULL && (words->type == nArgs || words->type == nLappend)) {
			if (words->u[1].p != NULL && words->u[1].p->type != nWord)
				break;
			head = glom(words->u[1].p);
			if (head != NULL) {
				head->n = tail;
				tail = head;
			}
			words = words->u[0].p;
		}
		v = append(glom(words), tail); /* force left to right evaluation */
		return append(v, glom(n->u[1].p));
	case nBackq:
		return backq(n->u[0].p, n->u[1].p);
	case nConcat:
		head = glom(n->u[0].p); /* force left-to-right evaluation */
		return concat(head, glom(n->u[1].p));
	case nDup:
	case nRedir:
		qredir(n);
		return NULL;
	case nWord:
		return word(n->u[0].s, n->u[1].s);
	case nNmpipe:
		return mkcmdarg(n);
	default:
		/*
		   The next four operations depend on the left-child of glom
		   to be a variable name. Therefore the variable is looked up
		   here.
		*/
		if ((v = glom(n->u[0].p)) == NULL)
			rc_error("null variable name");
		if (v->n != NULL)
			rc_error("multi-word variable name");
		if (*v->w == '\0')
			rc_error("zero-length variable name");
		v = (*v->w == '*' && v->w[1] == '\0') ? varlookup(v->w)->n : varlookup(v->w);
		switch (n->type) {
		default:
			panic("unexpected node in glom");
			exit(1);
			/* NOTREACHED */
		case nCount:
			return count(v);
		case nFlat:
			return flatten(v);
		case nVar:
			return v;
		case nVarsub:
			return varsub(v, glom(n->u[1].p));
		}
	}
}
/* snarfheredoc -- read a heredoc until the eof marker */
extern Tree *snarfheredoc(const char *eof, Boolean quoted) {
	Tree *tree, **tailp;
	Buffer *buf;
	unsigned char *s;

	assert(quoted || strchr(eof, '$') == NULL);	/* can never be typed (whew!) */
	if (strchr(eof, '\n') != NULL) {
		yyerror("here document eof-marker contains a newline");
		return NULL;
	}
	disablehistory = TRUE;

	for (tree = NULL, tailp = &tree, buf = openbuffer(0);;) {
		int c;
		print_prompt2();
		for (s = (unsigned char *) eof; (c = GETC()) == *s; s++)
			;
		if (*s == '\0' && (c == '\n' || c == EOF)) {
			if (buf->current == 0 && tree != NULL)
				freebuffer(buf);
			else
				*tailp = treecons(mk(nQword, sealcountedbuffer(buf)), NULL);
			break;
		}
		if (s != (unsigned char *) eof)
			buf = bufncat(buf, eof, s - (unsigned char *) eof);
		for (;; c = GETC()) {
			if (c == EOF) {
				yyerror("incomplete here document");
				freebuffer(buf);
				disablehistory = FALSE;
				return NULL;
			}
			if (c == '$' && !quoted && (c = GETC()) != '$') {
				Tree *var;
				UNGETC(c);
				if (buf->current == 0)
					freebuffer(buf);
				else {
					*tailp = treecons(mk(nQword, sealcountedbuffer(buf)), NULL);
					tailp = &(*tailp)->CDR;
				}
				var = getherevar();
				if (var == NULL) {
					freebuffer(buf);
					disablehistory = FALSE;
					return NULL;
				}
				*tailp = treecons(var, NULL);
				tailp = &(*tailp)->CDR;
				buf = openbuffer(0);
				continue;
			}
			buf = bufputc(buf, c);
			if (c == '\n')
				break;
		}
	}

	disablehistory = FALSE;
	return tree->CDR == NULL ? tree->CAR : tree;
}
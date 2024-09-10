/* The actual "aliasing" of for backgrounds() is done here
   with the aid of insert_we().   */
static void
insert(struct wordent *pl, int file_args)
{
    struct wordent *now, *last;
    Char   *cmd, *bcmd, *cp1, *cp2;
    size_t cmd_len;
    Char   *upause = STRunderpause;
    size_t p_len = Strlen(upause);

    cmd_len = Strlen(pl->word);
    cmd = xcalloc(1, (cmd_len + 1) * sizeof(Char));
    (void) Strcpy(cmd, pl->word);
/* Do insertions at beginning, first replace command word */

    if (file_args) {
	now = pl;
	xfree(now->word);
	now->word = xcalloc(1, 5 * sizeof(Char));
	(void) Strcpy(now->word, STRecho);

	now = xcalloc(1, sizeof(struct wordent));
	now->word = xcalloc(1, 6 * sizeof(Char));
	(void) Strcpy(now->word, STRbackqpwd);
	insert_we(now, pl);

	for (last = now; *last->word != '\n' && *last->word != ';';
	     last = last->next)
	    continue;

	now = xcalloc(1, sizeof(struct wordent));
	now->word = xcalloc(1, 2 * sizeof(Char));
	(void) Strcpy(now->word, STRgt);
	insert_we(now, last->prev);

	now = xcalloc(1, sizeof(struct wordent));
	now->word = xcalloc(1, 2 * sizeof(Char));
	(void) Strcpy(now->word, STRbang);
	insert_we(now, last->prev);

	now = xcalloc(1, sizeof(struct wordent));
	now->word = xcalloc(1, (cmd_len + p_len + 4) * sizeof(Char));
	cp1 = now->word;
	cp2 = cmd;
	*cp1++ = '~';
	*cp1++ = '/';
	*cp1++ = '.';
	while ((*cp1++ = *cp2++) != '\0')
	    continue;
	cp1--;
	cp2 = upause;
	while ((*cp1++ = *cp2++) != '\0')
	    continue;
	insert_we(now, last->prev);

	now = xcalloc(1, sizeof(struct wordent));
	now->word = xcalloc(1, 2 * sizeof(Char));
	(void) Strcpy(now->word, STRsemi);
	insert_we(now, last->prev);
	bcmd = xcalloc(1, (cmd_len + 2) * sizeof(Char));
	*bcmd = '%';
	Strcpy(bcmd + 1, cmd);
	now = xcalloc(1, sizeof(struct wordent));
	now->word = bcmd;
	insert_we(now, last->prev);
    }
    else {
	struct wordent *del;

	now = pl;
	xfree(now->word);
	now->word = xcalloc(1, (cmd_len + 2) * sizeof(Char));
	*now->word = '%';
	Strcpy(now->word + 1, cmd);
	for (now = now->next;
	     *now->word != '\n' && *now->word != ';' && now != pl;) {
	    now->prev->next = now->next;
	    now->next->prev = now->prev;
	    xfree(now->word);
	    del = now;
	    now = now->next;
	    xfree(del);
	}
    }
}
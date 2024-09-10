char *lg_readline(const char *mb_prompt)
{
	static int is_init = FALSE;
	static HistoryW *hist = NULL;
	static HistEventW ev;
	static EditLine *el = NULL;

	int numc;
	size_t byte_len;
	const wchar_t *wc_line;
	char *mb_line;
	char *nl;

	if (!is_init)
	{
		size_t sz;
#define HFILE ".lg_history"
		is_init = TRUE;

		sz = mbstowcs(NULL, mb_prompt, 0) + 4;
		wc_prompt = malloc (sz*sizeof(wchar_t));
		mbstowcs(wc_prompt, mb_prompt, sz);

		hist = history_winit();    /* Init built-in history */
		history_w(hist, &ev, H_SETSIZE, 20);  /* Remember 20 events */
		history_w(hist, &ev, H_LOAD, HFILE);
		el = el_init("link-parser", stdin, stdout, stderr);

		/* By default, it comes up in vi mode, with the editor not in
		 * insert mode; and even when in insert mode, it drops back to
		 * command mode at the drop of a hat. Totally confusing/lame. */
		el_wset(el, EL_EDITOR, L"emacs");
		el_wset(el, EL_HIST, history_w, hist);
		el_wset(el, EL_PROMPT_ESC, prompt, '\1'); /* Set the prompt function */
		el_source(el, NULL); /* Source the user's defaults file. */
	}

	wc_line = el_wgets(el, &numc);

	/* Received end-of-file */
	if (numc <= 0)
	{
		el_end(el);
		history_wend(hist);
		free(wc_prompt);
		wc_prompt = NULL;
		hist = NULL;
		el = NULL;
		is_init = FALSE;
		return NULL;
	}

	if (1 < numc)
	{
		history_w(hist, &ev, H_ENTER, wc_line);
		history_w(hist, &ev, H_SAVE, HFILE);
	}
	/* fwprintf(stderr, L"==> got %d %ls", numc, wc_line); */

	byte_len = wcstombs(NULL, wc_line, 0) + 4;
	mb_line = malloc(byte_len);
	wcstombs(mb_line, wc_line, byte_len);

	/* In order to be compatible with regular libedit, we have to
	 * strip away the trailing newline, if any. */
	nl = strchr(mb_line, '\n');
	if (nl) *nl = 0x0;
	
	return mb_line;
}
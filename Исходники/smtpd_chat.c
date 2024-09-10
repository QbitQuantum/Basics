static void smtp_chat_append(SMTPD_STATE *state, char *direction)
{
    char   *line;

    if (state->notify_mask == 0)
	return;

    if (state->history == 0)
	state->history = argv_alloc(10);
    line = concatenate(direction, STR(state->buffer), (char *) 0);
    argv_add(state->history, line, (char *) 0);
    myfree(line);
}
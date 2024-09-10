static void smtp_chat_append(SMTP_SESSION *session, const char *direction,
			             const char *data)
{
    char   *line;

    if (session->history == 0)
	session->history = argv_alloc(10);
    line = concatenate(direction, data, (char *) 0);
    argv_add(session->history, line, (char *) 0);
    myfree(line);
}
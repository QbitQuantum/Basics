static Str
news_command(News * news, char *cmd, char *arg, int *status)
{
    Str tmp;

    if (!news->host)
	return NULL;
    if (cmd) {
	if (arg)
	    tmp = Sprintf("%s %s\r\n", cmd, arg);
	else
	    tmp = Sprintf("%s\r\n", cmd);
	fwrite(tmp->ptr, sizeof(char), tmp->length, news->wf);
	fflush(news->wf);
    }
    if (!status)
	return NULL;
    *status = -1;
    tmp = StrISgets(news->rf);
    if (tmp->length)
	sscanf(tmp->ptr, "%d", status);
    return tmp;
}
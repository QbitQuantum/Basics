void do_note(COMMAND_ARGS)
{
	User	*u;
	Note	*n;
	Strp	*sp,**np;
	char	header[MSGLEN];

	/*
	 *  no-args is handled in on_msg()
	 */
	if (!(u = find_handle(rest)))
	{
		to_user(from,TEXT_UNKNOWNUSER,rest);
		return;
	}
	to_user(from,"Enter your note for %s, end with \".\" on a line by itself",
		u->name);

	set_mallocdoer(do_note);
	n = Calloc(sizeof(Note) + StrlenX(from,to,u->name,NULL));
	n->start = now;
	n->next = notelist;
	notelist = n;

	n->to = stringcat(n->from,from) + 1;
	n->user = stringcat(n->to,to) + 1;
	stringcpy(n->user,rest);

	/*
	 *  add a note header
	 */
	sprintf(header,"\001%s %s",from,time2str(now));
	append_strp(&u->note,header);
}
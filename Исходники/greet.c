/*
 *  woo.. no args? we use CurrentChan, CurrentNick and CurrentUser.
 */
void greet(void)
{
	Strp	*sp,**pp;
	char	linebuf[MSGLEN],readbuf[MSGLEN];
	char	*str;
	int	fd,sz;

	pp = &current->sendq;
	while(*pp)
		pp = &(*pp)->next;

	if (CurrentUser->x.x.greetfile)
	{
		if ((fd = open(CurrentUser->greet,O_RDONLY)) < 0)
			return;

		sz = sizeof(Strp) + 9 + strlen(CurrentNick);

		memset(readbuf,0,sizeof(readbuf));
		while(TRUE)
		{
			str = sockread(fd,readbuf,linebuf);
			if (str)
			{
				*pp = sp = (Strp*)Calloc(sz + strlen(str));
				/* Calloc sets to zero sp->next = NULL; */
				pp = &sp->next;
				sprintf(sp->p,"NOTICE %s :%s",CurrentNick,str);
			}
			else
			if (errno != EAGAIN)
				break;
		}

		close(fd);
	}
	else
	if (CurrentUser->x.x.randline)
	{
		if ((str = randstring(CurrentUser->greet)))
			goto single_line;
		return;
	}
	else
	{
		str = CurrentUser->greet;
single_line:
		*pp = sp = (Strp*)Calloc(sizeof(Strp) + 13 + Strlen(CurrentChan->name,CurrentNick,str,NULL));
		sprintf(sp->p,"PRIVMSG %s :[%s] %s",CurrentChan->name,CurrentNick,str);
		/* Calloc sets to zero sp->next = NULL; */
	}
}
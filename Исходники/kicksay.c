void do_kicksay(COMMAND_ARGS)
{
	/*
	 *  on_msg checks: CARGS
	 */
	KickSay *kick;
	char	*channel,*mask;
	int	inum;

	channel = chop(&rest);
	if (!channel)
	{
		if (!current->kicklist)
		{
			to_user(from,"Kicksay list is empty");
			return;
		}

		if (dcc_only_command(from))
			return;

		table_buffer("\037channel\037\t\037action\037\t\037string\037\t\037kick reason\037");
		for(kick=current->kicklist;kick;kick=kick->next)
		{
			table_buffer("%s\t%s\t%s\t%s",kick->chan,ks_actions[kick->action],kick->mask,kick->reason);
		}
		table_send(from,2);
		return;
	}

	if (ischannel(channel) || *channel == '*')
	{

		if (get_useraccess(from,channel) < cmdaccess)
			return;

		inum = DEFAULT_KS_LEVEL;
		if (*rest != '"')
		{
			inum = a2i(chop(&rest));
			if (errno || inum < 0 || inum > MAX_KS_LEVEL)
				return;
		}

		mask = get_token(&rest,"\"");

		if (!mask || !*mask)
			goto usage;

		/*
		 *  check for previously existing kicks
		 */
		if ((kick = find_kicksay(mask,channel)) != NULL)
		{
			to_user(from,"I'm already kicking on \"%s\"",kick->mask);
			return;
		}

		/*
		 *  dig out the reason (the rest)
		 */
		while(rest && *rest == ' ')
			rest++;
		if (!*rest)
			goto usage;

		/*
		 *  add it to the list
		 */
		set_mallocdoer(do_kicksay);
		kick = (KickSay*)Calloc(sizeof(KickSay) + Strlen(channel,mask,rest,NULL));

		kick->next = current->kicklist;
		current->kicklist = kick;
		kick->action = inum;

		if (!matches("\\*?*\\*",mask))
			kick->chan = Strcpy(kick->mask,mask) + 1;
		else
		{
			kick->mask[0] = '*';
			Strcpy(kick->mask+1,mask);
			kick->chan = Strcat(kick->mask,MATCH_ALL) + 1;
		}
		kick->reason = Strcpy(kick->chan,channel) + 1;
				Strcpy(kick->reason,rest);

		to_user(from,"Now kicking on \"%s\" on %s",mask,channel);
		current->ul_save++;
		return;
	}
usage:
	usage(from);	/* usage for CurrentCmd->name */
}
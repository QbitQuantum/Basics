void funny_namreply(char *from, char **Args)
{
char	*type,
	*channel;
static	char	format[40];
static	int	last_width = -1;
register char	*ptr;
register char	*line;
int user_count = 0;

	PasteArgs(Args, 2);
	type = Args[0];
	channel = Args[1];
	line = Args[2];

	/* protocol violation by server */
	if (!channel || !line)
		return;

	ptr = line;
	while (*ptr)
	{
		while (*ptr && (*ptr != ' '))
			ptr++;
		user_count++;
		while (*ptr && (*ptr == ' '))
			ptr++;
	}

	if (in_join_list(channel, from_server))
	{
		set_display_target(channel, LOG_CRAP);
		if (do_hook(current_numeric, "%s %s %s %s", from, type, channel,line) 
			&& do_hook(NAMES_LIST, "%s %s", channel, line)
			&& get_int_var(SHOW_CHANNEL_NAMES_VAR))
		{
			put_it("%s", convert_output_format(fget_string_var(FORMAT_NAMES_FSET), "%s %s %d",update_clock(GET_TIME), channel, user_count));
			print_funny_names(line);
		} 
		if ((user_count == 1) && (*line == '@'))
		{
			ChannelList *chan;
			if ((chan = lookup_channel(channel, from_server, CHAN_NOUNLINK)))
				if ((ptr = get_cset_str_var(chan->csets, CHANMODE_CSET)))
					my_send_to_server(from_server, "MODE %s %s", channel, ptr);
		}
		got_info(channel, from_server, GOTNAMES);
		reset_display_target();
		return;
	}
	if (last_width != get_int_var(CHANNEL_NAME_WIDTH_VAR))
	{
		if ((last_width = get_int_var(CHANNEL_NAME_WIDTH_VAR)) != 0)
			sprintf(format, "%%s: %%-%u.%us %%s",
				(unsigned char) last_width,
				(unsigned char) last_width);
		else
			strcpy(format, "%s: %s\t%s");
	}
	if (funny_min && (user_count < funny_min))
		return;
	else if (funny_max && (user_count > funny_max))
		return;
	if ((funny_flags & FUNNY_PRIVATE) && (*type == '='))
		return;
	if ((funny_flags & FUNNY_PUBLIC) && ((*type == '*') || (*type == '@')))
		return;
	if (type && channel)
	{
		if (match_str)
		{
			if (wild_match(match_str, channel) == 0)
				return;
		}
		if (do_hook(current_numeric, "%s %s %s %s", from, type, channel, line) && do_hook(NAMES_LIST, "%s %s", channel, line))
		{
			set_display_target(channel, LOG_CRAP);
			if (fget_string_var(FORMAT_NAMES_FSET))
			{
				put_it("%s", convert_output_format(fget_string_var(FORMAT_NAMES_FSET), "%s %s %d", update_clock(GET_TIME), channel, user_count));
				print_funny_names(line);
			} 
			else
			{
				switch (*type)
				{
				case '=':
					if (last_width &&(strlen(channel) > last_width))
					{
						channel[last_width-1] = '>';
						channel[last_width] = (char) 0;
					}
					put_it(format, "Pub", channel, line);
					break;
				case '*':
					put_it(format, "Prv", channel, line);
					break;
				case '@':
					put_it(format, "Sec", channel, line);
					break;
				}
			}
			reset_display_target();
		}
	}
}
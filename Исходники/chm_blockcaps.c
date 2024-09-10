static void
h_can_send(void *vdata)
{
	char *text;
	size_t contor;
	int caps = 0;
	int len = 0;

	hook_data_channel_approval *data = (hook_data_channel_approval *) vdata;

	if ((data->chptr->mode.mode & mymode) &&
	   ((strchr(ConfigChannel.exemptchanops, 'G') == NULL) ||
	    !is_any_op(data->msptr)))
	{
		/* 2 == unprintable */
		text = ((char **)data->data)[2];

		if(strlen(text) < 10)
			return;

		for(contor = 0; contor < strlen(text); contor++)
		{
			if(IsUpper(text[contor]) && !isdigit(text[contor]))
				caps++; 
			len++;
		}
		/* Added divide by 0 check --alxbl */ 
		if(len > 0 && ((caps * 100) / len) >= conf_threshold)
		{
			if(data->cmd == COMMAND_PRIVMSG)
				sendto_one_numeric(data->client, 404,
					"%s :Cannot send to channel - Your message contains more than %d%% capital letters (+G set)", 
					data->chptr->chname, conf_threshold);
			data->approved = CAN_SEND_NO_NONOTIFY;
			return;
		}
	}

	return;
}
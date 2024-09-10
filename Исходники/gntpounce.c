static void
pounce_cb(PurplePounce *pounce, PurplePounceEvent events, void *data)
{
	PurpleConversation *conv;
	PurpleAccount *account;
	PurpleBuddy *buddy;
	const char *pouncee;
	const char *alias;

	pouncee = purple_pounce_get_pouncee(pounce);
	account = purple_pounce_get_pouncer(pounce);

	buddy = purple_find_buddy(account, pouncee);
	if (buddy != NULL)
	{
		alias = purple_buddy_get_alias(buddy);
		if (alias == NULL)
			alias = pouncee;
	}
	else
		alias = pouncee;

	if (purple_pounce_action_is_enabled(pounce, "open-window"))
	{
		if (!purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, pouncee, account))
			purple_conversation_new(PURPLE_CONV_TYPE_IM, account, pouncee);
	}

	if (purple_pounce_action_is_enabled(pounce, "popup-notify"))
	{
		char *tmp = NULL;
		const char *name_shown;
		const char *reason;
		struct {
			PurplePounceEvent event;
			const char *format;
		} messages[] = {
			{PURPLE_POUNCE_TYPING, _("%s has started typing to you (%s)")},
			{PURPLE_POUNCE_TYPED, _("%s has paused while typing to you (%s)")},
			{PURPLE_POUNCE_SIGNON, _("%s has signed on (%s)")},
			{PURPLE_POUNCE_IDLE_RETURN, _("%s has returned from being idle (%s)")},
			{PURPLE_POUNCE_AWAY_RETURN, _("%s has returned from being away (%s)")},
			{PURPLE_POUNCE_TYPING_STOPPED, _("%s has stopped typing to you (%s)")},
			{PURPLE_POUNCE_SIGNOFF, _("%s has signed off (%s)")},
			{PURPLE_POUNCE_IDLE, _("%s has become idle (%s)")},
			{PURPLE_POUNCE_AWAY, _("%s has gone away. (%s)")},
			{PURPLE_POUNCE_MESSAGE_RECEIVED, _("%s has sent you a message. (%s)")},
			{0, NULL}
		};
		int i;
		reason = purple_pounce_action_get_attribute(pounce, "popup-notify",
				"reason");

		/*
		 * Here we place the protocol name in the pounce dialog to lessen
		 * confusion about what protocol a pounce is for.
		 */
		for (i = 0; messages[i].format != NULL; i++) {
			if (messages[i].event & events) {
				tmp = g_strdup_printf(messages[i].format, alias,
						purple_account_get_protocol_name(account));
				break;
			}
		}
		if (tmp == NULL)
			tmp = g_strdup(_("Unknown pounce event. Please report this!"));

		/*
		 * Ok here is where I change the second argument, title, from
		 * NULL to the account alias if we have it or the account
		 * name if that's all we have
		 */
		if ((name_shown = purple_account_get_alias(account)) == NULL)
			name_shown = purple_account_get_username(account);

		if (reason == NULL)
		{
			purple_notify_info(NULL, name_shown, tmp, purple_date_format_full(NULL));
		}
		else
		{
			char *tmp2 = g_strdup_printf("%s\n\n%s", reason, purple_date_format_full(NULL));
			purple_notify_info(NULL, name_shown, tmp, tmp2);
			g_free(tmp2);
		}
		g_free(tmp);
	}

	if (purple_pounce_action_is_enabled(pounce, "send-message"))
	{
		const char *message;

		message = purple_pounce_action_get_attribute(pounce, "send-message",
												   "message");

		if (message != NULL)
		{
			conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, pouncee, account);

			if (conv == NULL)
				conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, account, pouncee);

			purple_conversation_write(conv, NULL, message,
									PURPLE_MESSAGE_SEND, time(NULL));

			serv_send_im(purple_account_get_connection(account), (char *)pouncee, (char *)message, 0);
		}
	}

	if (purple_pounce_action_is_enabled(pounce, "execute-command"))
	{
		const char *command;

		command = purple_pounce_action_get_attribute(pounce,
				"execute-command", "command");

		if (command != NULL)
		{
			char *localecmd = g_locale_from_utf8(command, -1, NULL,
					NULL, NULL);

			if (localecmd != NULL)
			{
				int pid = fork();

				if (pid == 0) {
					char *args[4];

					args[0] = "sh";
					args[1] = "-c";
					args[2] = (char *)localecmd;
					args[3] = NULL;

					execvp(args[0], args);

					_exit(0);
				}
				g_free(localecmd);
			}
		}
	}

	if (purple_pounce_action_is_enabled(pounce, "play-beep"))
	{
		beep();
	}
}
static enum request
run_prompt_command(struct view *view, char *cmd)
{
	enum request request;

	if (!cmd)
		return REQ_NONE;

	if (string_isnumber(cmd)) {
		int lineno = view->pos.lineno + 1;

		if (parse_int(&lineno, cmd, 1, view->lines + 1) == SUCCESS) {
			select_view_line(view, lineno - 1);
			report_clear();
		} else {
			report("Unable to parse '%s' as a line number", cmd);
		}
	} else if (iscommit(cmd)) {
		string_ncopy(view->env->search, cmd, strlen(cmd));

		request = view_request(view, REQ_JUMP_COMMIT);
		if (request == REQ_JUMP_COMMIT) {
			report("Jumping to commits is not supported by the '%s' view", view->name);
		}

	} else if (strlen(cmd) == 1) {
		struct key_input input = { { cmd[0] } };

		return get_keybinding(&view->ops->keymap, &input);

	} else if (cmd[0] == '/' || cmd[0] == '?') {
		const char *search = cmd + 1;

		if (!strcmp(search, view->env->search))
			return cmd[0] == '/' ? REQ_FIND_NEXT : REQ_FIND_PREV;

		string_ncopy(view->env->search, search, strlen(search));
		return cmd[0] == '/' ? REQ_SEARCH : REQ_SEARCH_BACK;

	} else if (cmd[0] == '!') {
		struct view *next = VIEW(REQ_VIEW_PAGER);
		const char *argv[SIZEOF_ARG];
		int argc = 0;

		cmd++;
		/* When running random commands, initially show the
		 * command in the title. However, it maybe later be
		 * overwritten if a commit line is selected. */
		string_ncopy(next->ref, cmd, strlen(cmd));

		if (!argv_from_string(argv, &argc, cmd)) {
			report("Too many arguments");
		} else if (!argv_format(view->env, &next->argv, argv, FALSE, TRUE)) {
			report("Argument formatting failed");
		} else {
			next->dir = NULL;
			open_view(view, REQ_VIEW_PAGER, OPEN_PREPARED);
		}

	} else {
		request = get_request(cmd);
		if (request != REQ_UNKNOWN)
			return request;

		char *args = strchr(cmd, ' ');
		if (args) {
			*args++ = 0;
			if (set_option(cmd, args) == SUCCESS) {
				request = !view->unrefreshable ? REQ_REFRESH : REQ_SCREEN_REDRAW;
				if (!strcmp(cmd, "color"))
					init_colors();
				resize_display();
				redraw_display(TRUE);
			}
		}
		return request;
	}
	return REQ_NONE;
}
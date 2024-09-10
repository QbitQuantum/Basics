/**
 * Parse command line arguments.
 *
 * @param cmd_line structure to store parsed options data
 */
static void parse_cmdline_options(struct parsed_cmd_line_t* cmd_line)
{
	int argc;
	int n_files = 0, b_opt_end = 0;
	rsh_tchar** files;
	rsh_tchar **parg, **end_arg;
	parsed_option_t *next_opt;

#ifdef _WIN32
	parg = cmd_line->warg = CommandLineToArgvW(GetCommandLineW(), &argc);
	if( NULL == parg || argc < 1) {
		die(_("CommandLineToArgvW failed\n"));
	}
#else
	argc = cmd_line->argc;
	parg = cmd_line->argv;
#endif

	/* allocate array for files */
	files = (rsh_tchar**)rsh_malloc(argc * sizeof(rsh_tchar*));
	end_arg = parg + argc;

	/* loop by program arguments */
	for(parg++; parg < end_arg; parg++)
	{
		/* if argument is not an option */
		if((*parg)[0] != RSH_T('-') || (*parg)[1] == 0 || b_opt_end) {
			/* it's a file, note that '-' is interpreted as stdin */
			files[n_files++] = *parg;
			continue;
		}

		assert((*parg)[0] == RSH_T('-') && (*parg)[1] != 0);
		
		if((*parg)[1] == L'-' && (*parg)[2] == 0) {
			b_opt_end = 1; /* string "--" means end of options */
			continue;
		}

		/* check for "--" */
		if((*parg)[1] == RSH_T('-')) {
			cmdline_opt_t *t;

			/* allocate parsed_option */
			rsh_blocks_vector_add_empty(&cmd_line->options, 16, sizeof(parsed_option_t));
			next_opt = rsh_blocks_vector_get_item(&cmd_line->options, cmd_line->options.size - 1, 16, parsed_option_t);

			/* find the long option */
			parse_long_option(next_opt, &parg);
			t = next_opt->o;

			/* process encoding and -o/-l options early */
			if(is_output_modifier(t->type)) {
				apply_option(&opt, next_opt);
			}
		} else if((*parg)[1] != 0) {
			/* found '-'<some string> */
			rsh_tchar* ptr;
			
			/* parse short options. A string of several characters is interpreted
			 * as separate short options */
			for(ptr = *parg + 1; *ptr; ptr++) {
				cmdline_opt_t *t;
				char ch = (char)*ptr;

#ifdef _WIN32
				if(((unsigned)*ptr) >= 128) {
					ptr[1] = 0;
					fail_on_unknow_option(w2c(ptr));
				}
#endif
				/* allocate parsed_option */
				rsh_blocks_vector_add_empty(&cmd_line->options, 16, sizeof(parsed_option_t));
				next_opt = rsh_blocks_vector_get_item(&cmd_line->options, cmd_line->options.size - 1, 16, parsed_option_t);

				next_opt->buf[0] = '-', next_opt->buf[1] = ch, next_opt->buf[2] = '\0';
				next_opt->name = next_opt->buf;
				next_opt->parameter = NULL;
				
				/* search for the short option */
				for(t = cmdline_opt; t->type && ch != t->short1 && ch != t->short2; t++);
				if(!t->type) fail_on_unknow_option(next_opt->buf);
				next_opt->o = t;
				if(is_param_required(t->type)) {
					next_opt->parameter = (ptr[1] ? ptr + 1 : *(++parg));
					if(!next_opt->parameter) {
						/* note: need to check for parameter here, for early -o/-l options processing */
						log_error(_("argument is required for option %s\n"), next_opt->name);
						rsh_exit(2);
					}
				}

				/* process encoding and -o/-l options early */
				if(is_output_modifier(t->type)) {
					apply_option(&opt, next_opt);
				}
				if(next_opt->parameter) break;  /* a parameter ends the short options string */
			}
		}

	} /* for */

	cmd_line->n_files = n_files;
	cmd_line->files = files;
}
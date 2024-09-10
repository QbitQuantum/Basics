int main(int argc, char **argv)
{
	sc_context_t *ctx = NULL;
	sc_context_param_t ctx_param;
	sc_card_t *card = NULL;
	int r;
	int argind = 0;
	int exit_status = EXIT_SUCCESS;

	/* decode options */
	argind = decode_options(argc, argv);

	/* connect to the card */
	memset(&ctx_param, 0, sizeof(ctx_param));
	ctx_param.ver      = 0;
	ctx_param.app_name = app_name;

	r = sc_context_create(&ctx, &ctx_param);
	if (r) {
		util_fatal("failed to establish context: %s", sc_strerror(r));
		return EXIT_FAILURE;
	}

	r = util_connect_card(ctx, &card, opt_reader, opt_wait, verbose);
	if (r) {
		util_fatal("failed to connect to card: %s", sc_strerror(r));
		return EXIT_FAILURE;
	}

	/* check card type */
	if ((card->type != SC_CARD_TYPE_OPENPGP_BASE) &&
			(card->type != SC_CARD_TYPE_OPENPGP_V1) &&
			(card->type != SC_CARD_TYPE_OPENPGP_V2) &&
			(card->type != SC_CARD_TYPE_OPENPGP_V3) &&
			(card->type != SC_CARD_TYPE_OPENPGP_GNUK)) {
		util_error("card type %X: not an OpenPGP card", card->type);
		exit_status = EXIT_FAILURE;
		goto out;
	}

	/* fail on too many arguments */
	if (argind > argc)
		util_print_usage_and_die(app_name, options, option_help, NULL);

	/* set default action */
	if (!actions)
		opt_userinfo = 1;

	if (opt_cardinfo)
		exit_status |= do_info(card, card_data);

	if (opt_userinfo)
		exit_status |= do_info(card, user_data);

	if (opt_keyinfo)
		exit_status |= do_info(card, key_data);

	if (opt_verify && opt_pin) {
		exit_status |= do_verify(card, verifytype, pin);
	}

	if (opt_dump_do) {
		size_t n;

		for (n = 0; n < opt_dump_do; n++) {
			exit_status |= do_dump_do(card, do_dump_idx[n]);
		}
	}

	if (opt_genkey)
		exit_status |= do_genkey(card, key_id, keytype);

	if (exec_program) {
		char *const largv[] = {exec_program, NULL};
		sc_unlock(card);
		sc_disconnect_card(card);
		sc_release_context(ctx);
		#ifndef _WIN32
		execv(exec_program, largv);
		#else
		_execv(exec_program, (const char * const*)largv);
		#endif
		/* we should not get here */
		perror("execv()");
		exit(EXIT_FAILURE);
	}

	if (opt_delkey)
		exit_status |= do_delete_key(card, key_id);

	if (opt_erase)
		exit_status |= do_erase(card);

out:
	sc_unlock(card);
	sc_disconnect_card(card);
	sc_release_context(ctx);

	exit(exit_status);
}
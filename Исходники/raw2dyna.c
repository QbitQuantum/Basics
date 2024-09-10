int main(int argc, char **argv) {
	char Buf[256], *cps, *cph;

	Setup();
	ParseOptions(argc, argv);
	if (simple_to_from_hex)
		return simple_convert();

	// if no input redirection then give usage. I 'guess' we could allow
	// a user to type in hashes, but is that really likely?  It is almost
	// certain that if there is no input redirection, the user does not
	// know how to use the tool, so tell him how.
	if (isatty(fileno(stdin)))
		usage(argv[0]);

	FGETS(Buf, sizeof(Buf), stdin);
	while (!feof(stdin)) {
		strtok(Buf, "\r\n");
		if (!leading_salt) {
			cph = Buf;
			cps = &Buf[hash_len];
			if (salt_sep && *cps == salt_sep) ++cps;
		} else {
			cps = Buf;
			cph = &Buf[leading_salt];
			if (salt_sep && *cph == salt_sep) {*cph++ = 0;}
		}
		printf("$dynamic_%d$%*.*s$%s\n", dyna_num, hash_len,hash_len, cph, GetSalt(cps));
		FGETS(Buf, sizeof(Buf), stdin);
	}
	MEMDBG_PROGRAM_EXIT_CHECKS(stderr);
	return 0;
}
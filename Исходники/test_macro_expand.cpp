// runs all of the tests in non-verbose mode by default (i.e. printing only failures)
// individual groups of tests can be run by using the -t:<tests> option where <tests>
// is one or more of 
//   l   testing_lookups
//   $   testing_$_expand
//   [   testing_$$_expand
//   e   testing_$ENV_expand
//   F   testing_$F_expand and testing_$F_regressions
//   c   testing_$CHOICE_expand
//   s   testing_$SUBSTR_expand
//   i   testing_$INT_expand
//   r   testing_$REAL_expand
//   n   testing_$INT_expand and testing_$REAL_expand
//   r   testing_$RAND_expand (RANDOM_INTEGER and RANDOM_CHOICE)
//   P   testing_parser  config/submit/metaknob parser.
//
int main( int /*argc*/, const char ** argv) {

	int test_flags = 0;
	const char * pcolon;

	for (int ii = 1; argv[ii]; ++ii) {
		const char *arg = argv[ii];
		if (is_dash_arg_prefix(arg, "verbose", 1)) {
			dash_verbose = 1;
		} else if (is_dash_arg_colon_prefix(arg, "test", &pcolon, 1)) {
			if (pcolon) {
				while (*++pcolon) {
					switch (*pcolon) {
					case 'l': test_flags |= 0x0001; break; // lookup
					case '$': test_flags |= 0x0002; break; // $
					case '[': test_flags |= 0x0004; break; // $$
					case 'e': test_flags |= 0x0008; break; // $ENV
					case 'F': test_flags |= 0x0010 | 0x0020; break;	 // $F
					case 'c': test_flags |= 0x0040; break; // $CHOICE
					case 's': test_flags |= 0x0080; break; // $SUBSTR
					case 'i': test_flags |= 0x0100; break; // $INT
					case 'f': test_flags |= 0x0200; break; // $REAL
					case 'n': test_flags |= 0x0100 | 0x0200; break; // $INT, $REAL
					case 'r': test_flags |= 0x0400; break; // $RANDOM_INTEGER and $RANDOM_CHOICE
					case 'p': test_flags |= 0x1000; break; // parse
					}
				}
			} else {
				test_flags = 3;
			}
		} else {
			fprintf(stderr, "unknown argument %s\n", arg);
			return 1;
		}
	}
	if ( ! test_flags) test_flags = -1;

	TestingMacroSet.defaults->size = param_info_init((const void**)&TestingMacroSet.defaults->table);
	TestingMacroSet.options |= CONFIG_OPT_DEFAULTS_ARE_PARAM_INFO;

	insert_testing_macros(NULL, "TEST");

	optimize_macros(TestingMacroSet);

	if (test_flags & 0x0001) testing_lookups(dash_verbose);
	if (test_flags & 0x0002) testing_$_expand(dash_verbose);
	if (test_flags & 0x0004) testing_$$_expand(dash_verbose);
	if (test_flags & 0x0008) testing_$ENV_expand(dash_verbose);

	if (test_flags & 0x0010) testing_$F_expand(dash_verbose);
	if (test_flags & 0x0020) testing_$F_regressions(dash_verbose);

	if (test_flags & 0x0040) testing_$CHOICE_expand(dash_verbose);
	if (test_flags & 0x0080) testing_$SUBSTR_expand(dash_verbose);

	if (test_flags & 0x0100) testing_$INT_expand(dash_verbose);
	if (test_flags & 0x0200) testing_$REAL_expand(dash_verbose);

	if (test_flags & 0x0400) testing_$RAND_expand(dash_verbose);

	if (test_flags & 0x1000) testing_parser(dash_verbose);

	return fail_count > 0;
}
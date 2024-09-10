static void process_parameters(int argc, char **argv)
{
  int i, fich, tmpnum;

  /* process command line arguments */
  for (i=1, fich=0; i<argc; i++) {
    if (!strcmp(argv[i], "-e")) {
      param_strict = 0;
    } else if (!strcmp(argv[i], "-t") && ((i+1) < argc)) {
      param_doctype = dtd_get_dtd_index(argv[++i]);
    } else if (!strcmp(argv[i], "-o") && ((i+1) < argc)) {
      /* open the output file */
      param_outputf = fopen(argv[++i], "wb");
      if (!param_outputf) {
	perror("fopen");
	EXIT("Could not open the output file for writing");
      }
    } else if (!strcmp(argv[i], "-l") && ((i+1) < argc)) {
      tmpnum= atoi(argv[++i]);
      if (tmpnum >= 40)
	param_chars_per_line = tmpnum; 
    } else if (!strcmp(argv[i], "-b") && ((i+1) < argc)) {
      tmpnum= atoi(argv[++i]);
      if (tmpnum >= 0 && tmpnum <= 16)
	param_tab_len = tmpnum; 
    } else if (!strcmp(argv[i], "--preserve-space-comments")) {
      param_pre_comments = 1;
    } else if (!strcmp(argv[i], "--no-protect-cdata")) {
      param_protect_cdata = 0;
    } else if (!strcmp(argv[i], "--compact-block-elements")) {
      param_compact_block_elms = 1;
    } else if (!strcmp(argv[i], "--compact-empty-elem-tags")) {
      param_compact_empty_elm_tags = 1;
    } else if (!strcmp(argv[i], "--empty-elm-tags-always")) {
      param_empty_tags = 1;
    } else if (!strcmp(argv[i], "--dos-eol")) {
      param_crlf_eol = 1;
    } else if (!fich && argv[i][0]!='-') {
      fich = 1;
      param_inputf = fopen(argv[i], "r");
      if (!param_inputf) {
	perror("fopen");
	EXIT("Could not open the input file for reading");
      }
    } else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
      help();
      exit(0);
    } else if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {
      print_version();
      exit(0);
    } else if (!strcmp(argv[i], "-L")) {
      print_doctype_keys();
      exit(0);
    } else if (!strcmp(argv[i], "--ics") && ((i+1) < argc)) {
      param_charset_in = charset_lookup_alias(argv[++i]);
      if (!param_charset_in) {
	EPRINTF1("Trying to set input character set: %s\n", argv[i]);
	EXIT("Unsupported character set");
      }
    } else if (!strcmp(argv[i], "--ocs") && ((i+1) < argc)) {
      param_charset_out = charset_lookup_alias(argv[++i]);
      if (!param_charset_out) {
	EPRINTF1("Trying to set output character set: %s\n", argv[i]);
	EXIT("Unsupported character set");
      }
    } else if (!strcmp(argv[i], "--lcs")) {
      charset_dump_aliases(stdout);
      exit(0);
    } else if (!strcmp(argv[i], "--generate-snippet")) {
      param_generate_snippet = 1;
    } else {
      help();
      exit(1);
    }
  } 
}
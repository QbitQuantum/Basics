int main(int argc, char **argv)
{
  setlocale(LC_NUMERIC, "C");
  program_name = argv[0];
  string env;
  static char stderr_buf[BUFSIZ];
  setbuf(stderr, stderr_buf);
  int c;
  static const struct option long_options[] = {
    { "help", no_argument, 0, CHAR_MAX + 1 },
    { "version", no_argument, 0, 'v' },
    { NULL, 0, 0, 0 }
  };
  while ((c = getopt_long(argc, argv, "b:c:F:gI:lmp:P:vw:", long_options, NULL))
	 != EOF)
    switch(c) {
    case 'b':
      // XXX check this
      broken_flags = atoi(optarg);
      bflag = 1;
      break;
    case 'c':
      if (sscanf(optarg, "%d", &ncopies) != 1 || ncopies <= 0) {
	error("bad number of copies `%s'", optarg);
	ncopies = 1;
      }
      break;
    case 'F':
      font::command_line_font_dir(optarg);
      break;
    case 'g':
      guess_flag = 1;
      break;
    case 'I':
      include_search_path.command_line_dir(optarg);
      break;
    case 'l':
      landscape_flag = 1;
      break;
    case 'm':
      manual_feed_flag = 1;
      break;
    case 'p':
      if (!font::scan_papersize(optarg, 0,
				&user_paper_length, &user_paper_width))
	error("invalid custom paper size `%1' ignored", optarg);
      break;
    case 'P':
      env = "GROPS_PROLOGUE";
      env += '=';
      env += optarg;
      env += '\0';
      if (putenv(strsave(env.contents())))
	fatal("putenv failed");
      break;
    case 'v':
      printf("GNU grops (groff) version %s\n", Version_string);
      exit(0);
      break;
    case 'w':
      if (sscanf(optarg, "%d", &linewidth) != 1 || linewidth < 0) {
	error("bad linewidth `%1'", optarg);
	linewidth = -1;
      }
      break;
    case CHAR_MAX + 1: // --help
      usage(stdout);
      exit(0);
      break;
    case '?':
      usage(stderr);
      exit(1);
      break;
    default:
      assert(0);
    }
  font::set_unknown_desc_command_handler(handle_unknown_desc_command);
  SET_BINARY(fileno(stdout));
  if (optind >= argc)
    do_file("-");
  else {
    for (int i = optind; i < argc; i++)
      do_file(argv[i]);
  }
  return 0;
}
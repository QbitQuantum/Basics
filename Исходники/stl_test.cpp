int cpp_main(int argc, char *argv[])
{
  for (int a = 0; a < argc; ++a)
  {
    command_args += argv[a];
    if (a != argc-1)
      command_args += ' ';
  }

  cout << "command line arguments: " << command_args << '\n';

  cout << "*******************************************************************\n"
          "*  WARNING: DUMPING AND RELOADING STATE FOR RESTART NOT WORKING;  *\n"
          "*  COMMENTED OUT CODE NEEDS TO BE FIXED TO RESTART RNG AND        *\n"
          "*  DUMP AND RESTORE mapped_type DATA IF PRESENT.                  *\n"
          "*******************************************************************\n\n";

  for (; argc > 1; ++argv, --argc) 
  {
    if (*argv[1] != '-')
      path_prefix = argv[1];
    else
    {
      if (strncmp(argv[1]+1, "max=", 4) == 0)
        max = atol(argv[1]+5);
      else if (strncmp(argv[1]+1, "min=", 4) == 0)
        min = atol(argv[1]+5);
      else if (strncmp(argv[1]+1, "low=", 4) == 0)
        low = atol(argv[1]+5);
      else if (strncmp(argv[1]+1, "high=", 5) == 0)
        high = atol(argv[1]+6);
      else if (strncmp(argv[1]+1, "cycles=", 7) == 0)
        cycles = atol(argv[1]+8);
      else if (strncmp(argv[1]+1, "seed=", 5) == 0)
        rng_seed = atol(argv[1]+6);
      else if (strncmp(argv[1]+1, "node=", 5) == 0)
        node_sz = atol(argv[1]+6);
      else if (strncmp(argv[1]+1, "cache=", 6) == 0)
        cache_sz = atol(argv[1]+7);
      else if (strncmp(argv[1]+1, "dump=", 5) == 0)
        dump = atol(argv[1]+6);
      else if (strncmp(argv[1]+1, "restart", 7) == 0)
        restart = true;
      else if (strcmp(argv[1]+1, "v") == 0)
        verbose = true;
      else if ( memcmp( argv[2]+1, "sep=", 4 )==0
          && (std::ispunct(*(argv[2]+5)) || *(argv[2]+5)== '\0') )
        thou_separator = *(argv[2]+5) ? *(argv[2]+5) : ' ';
      else
      {
        cout << "Error - unknown option: " << argv[1] << "\n\n";
        argc = -1;
        break;
      }
    }
  }

  if (argc < 2) 
  {
    cout << "Usage: stl_test [Options]\n"
      "The argument n specifies the number of test cases to run\n"
      "Options:\n"
      "   path-prefix  Test files path-prefix; default '" << path_prefix << "'\n"
      "                Two files will be created; path-prefix.btr and path-prefix.stl\n"
      "   -max=#       Maximum number of test elements; default " << max << "\n"
      "   -min=#       Minimum number of test elements; default " << min << "\n"
      "   -low=#       Random key distribution low value; default 0\n"
      "   -high=#      Random key distribution high value; default max*2.\n"
      "                (high-low) must be >max, so that max is reached\n"
      "   -cycles=#    Cycle tests specified number of times; default " << cycles << "\n"
      "                -cycles=0 causes tests to cycle forever\n"
      "   -seed=#      Seed for random number generator; default "  << rng_seed << "\n"
      "   -node=#      Node size (>=128); default " << node_sz << "\n"
      "                Small node sizes increase stress\n"
      "   -cache=#     Cache size; default " << cache_sz << " nodes\n"
      "   -dump=#      Dump restart files when cycles run mod dump # == 0, except \n"
      "                dump # -1 means dump at end only, 0 means never dump;\n"
      "                default " << dump << "\n"
      "   -restart     Restart using restart files from previous run\n"
      "   -v           Verbose output statistics\n"
      "   -sep=[punct] cout thousands separator; space if punct omitted, default -sep,\n"
      "\n    Each test cycle inserts the same random values into both a btree_map\n"
      "and a std::map until the maximum number of elements is reached.\n"
      "The same sequence of random elements will then be erased, until the minimum\n"
      "number of elements is reached. The btree, std::map, and program state are\n"
      "copied to files, and the cycle ends.\n"
      "    At the maximum and minimum points of each cycle, forward iteration,\n"
      "backward iteration, find, lower_bound, and upper_bound tests are run\n"
      "against both containers. If results are not identical, the program\n"
      "issues an error message and returns 1.\n"
      "    The -restart argument causes the btree, std::map, and program to be\n"
      "initialized to the state saved in the restart files from the prior run.\n"
      ;
  }

  if (argc == -1)
    return 1;

  if (high == 0)
    high = max * 2;

  if ((high-low) <= max)
  {
    cout << "Error: (high-low) must be greater than max\n";
    return 1;
  }

  cout.imbue(std::locale(std::locale(), new thousands_separator));

  tester<boost::btree::detail::set_index_string_view> testr;
  testr.r_tests();

  cout << "all test cycles complete" << endl;

  return boost::report_errors();
}
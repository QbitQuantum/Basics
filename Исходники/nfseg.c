/***********************************************************************
************************************************************************
#cat: procargs - Process command line arguments, setting various
#cat:              static variables with file scope as appropriate.

   Input:
     argc        - standard argument count
     argv        - standard argument array

   Return Code:
     none        - return on success
     no return   - exit if invalid arguments are detected
************************************************************************/
static void procargs(int argc, char **argv)
{
   int opt, output_images_flag = 0;
   const char *const option_spec = "vbc:rRf:i:n:q:";
   const char *rest;
   REC_SEL *fgp_sel = NULL, *imp_sel = NULL, *idc_sel = NULL,
      *lrt_sel = NULL, *nqm_sel = NULL;

   if ((argc == 2) && (strcmp(argv[1], "-version") == 0)) {
      getVersion();
      exit(0);
   }

   program = strrchr(argv[0], '/');
   if (NULL == program)
      program = argv[0];
   else
      ++program;

   if (argc < 2)
      usage();

   /* The following section handles the deprecated old-style arguments. --jck */
   old_style_args_flag = ((7 == argc) && ('-' != argv[1][0]));
   if (old_style_args_flag) {
      fgp =        parse_num_arg(argv[1], "FGP");
      bthr_adj =   parse_num_arg(argv[2], "BTHR_ADJ");
      rot_search = parse_num_arg(argv[3], "ROT_SEARCH");
      comp =       parse_num_arg(argv[4], "COMP_SEG");
      rot_seg =    parse_num_arg(argv[5], "ROT_SEG");
      ifile = argv[6];
      optind = 7;
      /* End of old-style deprecated argument handling. --jck */
   } else {
      /* Processing exclusive to new-style argument handling... -- jck */
      while (-1 != (opt = getopt(argc, argv, option_spec))) {
	 switch(opt) {
	    
	 case 'v':
	    verbose = 1;
	    break;

	 case 'b':
	    bthr_adj = 1;
	    break;
	    
	 case 'c':
	    output_images_flag = 1;
	    comp = parse_num_arg(optarg, "-c <COMP_SEG>");
	    break;
	    
	 case 'r':
	    rot_search = 1;
	    break;
	    
	 case 'R':
	    rot_seg = 1;
	    break;
	    
	 case 'f':
	    if (parse_rec_sel_option(rs_fgp, optarg, &rest, &fgp_sel, verbose))
	       usage();
	    if (parse_rec_sel_option(rs_imp, rest, NULL, &imp_sel, verbose))
	       usage();
	    break;
	    
	 case 'i':
	    if (parse_rec_sel_option(rs_imp, optarg, NULL, &imp_sel, verbose))
	       usage();
	    break;
	    
	 case 'n':
	    if (parse_rec_sel_option(rs_idc, optarg, NULL, &idc_sel, verbose))
	       usage();
	    break;
	    
	 case 't':
	    if (parse_rec_sel_option(rs_lrt, optarg, NULL, &lrt_sel, verbose))
	       usage();
	    break;
	    
	 case 'q':
	    if (parse_rec_sel_option(rs_nqm, optarg, NULL, &nqm_sel, verbose))
	       usage();
	    break;
	    
	 case '?':
	    usage();
	    break;
	    
	 default:
	    fprintf(stderr, "Programming error: "
		    "incompletely implemented option: '%c'\n", opt);
	    exit(EXIT_FAILURE);
	 }
      }

      /* ANSI/NIST input file, required */
      if (optind < argc) 
	 ifile = argv[optind++];
      else
	 usage();
      
      ansi_nist_flag = is_ANSI_NIST_file(ifile);
      if (ansi_nist_flag < 0)
	 exit(EXIT_FAILURE);
      else if ( 0 == ansi_nist_flag ) {
	 fprintf(stderr, "Input is not an ANSI/NIST file: '%s'.\n", ifile);
	 usage();
      }

      /* ANSI/NIST output file, optional */
      if (optind < argc)
	 ofile = argv[optind++];
      
      if (new_rec_sel(&opt_rec_sel, rs_and, 5,
		      fgp_sel, imp_sel, idc_sel, lrt_sel, nqm_sel) < 0)
	 exit(EXIT_FAILURE);

   }

   /* This processing applies to both old- and new-style arguments. */
   if (optind < argc) {
      fprintf(stderr, "WARNING : procargs : extra arguments ignored: %s",
	      argv[optind++]);
      for (/* empty */; optind < argc; optind++)
	 fprintf(stderr, ", %s", argv[optind]);
      fprintf(stderr, "\n");
   }

   output_images = (ofile == NULL || output_images_flag);
   
   if (comp != UNSET && (comp < 0 || comp > 3)) {
      fprintf(stderr, "Invalid COMP (%d)\n", comp);
      fprintf(stderr, "0=JPEGL | 1=WSQ5:1 | 2=WSQ15:1 | 3=NONE\n");
      exit(EXIT_FAILURE);
   }

   check_tristate_value(bthr_adj, "BTHR_ADJ");
   check_tristate_value(rot_search, "ROT_SEARCH");
   check_tristate_value(rot_seg, "ROT_SEG");

   return;
}
/* initenv ()  initializes the environment */
void initenv (int argc, char **argv, struct mngmsg *m_msp, 
		 struct pstruct *ppst, unsigned char **aa0)
{
   char *cptr, ctmp;
   long l_tmp;
   int  copt, itmp, i;

   /* options for all search functions */
   /* char   *g_optstr = "b:BC:d:DE:F:HiK:l:Lm:N:O:QqR:T:v:V:w:W:X:Z:"; */

   char g_optstring[MAX_STR];
   char f_optstring[MAX_STR];
   char optstring[MAX_STR];

   build_optstr(g_optstring, sizeof(f_optstring), g_options);
   build_optstr(f_optstring, sizeof(f_optstring), f_options);

/*  these initializations will be used by all functions */

   /* prog_name[] is only used for error messages */
   strncpy(prog_name,argv[0],sizeof(prog_name));
   prog_name[sizeof(prog_name)-1]='\0';

#ifdef PCOMPLIB
#ifdef MPI_SRC
  MPI_Comm_size(MPI_COMM_WORLD,&fa_max_workers);
  if (fa_max_workers <= 1) {
    fprintf(stderr," nnodes = %d; no workers available\n",fa_max_workers);
    exit(1);
  }
  else {
    fa_max_workers -= FIRSTNODE;
    fprintf(stderr," have %d workers\n",fa_max_workers);
  }
#endif
#else
#if defined(IRIX)
   fa_max_workers = sysmp(MP_NPROCS);
#else
#if defined(UNIX) || defined(HAVE_SYSCONF)
   fa_max_workers = sysconf(_SC_NPROCESSORS_CONF);
#endif	/* UNIX || SYSCONF */
#endif  /* !IRIX */
#endif  /* !PCOMPLIB */

   m_msp->ltitle[0] = '\0';

   if ((cptr=getenv("FASTLIBS"))!=NULL) {
     strncpy(m_msp->flstr,cptr,MAX_FN);
     m_msp->flstr[MAX_FN-1] = '\0';
   }
   else m_msp->flstr[0]='\0';

   m_msp->std_output = 1;
   m_msp->hist.hist_a = NULL;
   m_msp->outfile[0] = '\0';
   m_msp->outfd = NULL;
   m_msp->ldb_info.ldnaseq = SEQT_PROT;	/* library is protein */
   m_msp->n1_low = ppst->n1_low = 0;
   m_msp->n1_high = ppst->n1_high = BIGNUM;
   m_msp->ql_start = 1;	/* start with first query sequence */
   m_msp->ql_stop = BIGNUM;	/* end with the last query sequence */
   m_msp->aa1save_buf_b = NULL;
   m_msp->bline_buf_b = NULL;

   m_msp->pamd1 = MAXSQ;
   m_msp->pamd2 = MAXSQ;

   m_msp->ldb_info.term_code = 0;
   ppst->tr_type = 0;
   ppst->debug_lib = 0;
   m_msp->nshow = 20;
   ppst->max_repeat = 50;
   m_msp->nohist = 1;
#if defined(PCOMPLIB)
   m_msp->mshow = 20;
#else
#ifdef SHOW_HIST
   m_msp->nohist = 0;
#endif
   m_msp->mshow = 50;
#endif
   m_msp->do_showbest = 1;
   m_msp->ashow = -1;
   m_msp->ashow_set = 0;
   m_msp->nmlen = DEF_NMLEN;
   m_msp->z_bits = 1;
   m_msp->mshow_set = 0;
   m_msp->mshow_min = 0;
   m_msp->aln.llen = 60;
   m_msp->aln.llcntx = 30;
   m_msp->aln.llcntx_set = 0;
   m_msp->e_low = 0.0;
   m_msp->e_cut_set = 0;
   m_msp->revcomp = 0;
   m_msp->long_info = 0;
   m_msp->ldb_info.maxn = 0;
   m_msp->ldb_info.dupn = SEQDUP;
   m_msp->dfile[0] = '\0';
   m_msp->tname[0] = '\0';
   m_msp->lname[0] = '\0';
   m_msp->link_lname[0] = '\0';
   m_msp->show_code = 0;
   m_msp->aln.showall = 0;
   m_msp->markx = 0;
   m_msp->markx_list = NULL;
   m_msp->align_done = 0;
   m_msp->sq0off = m_msp->sq1off = 1;
   strncpy(m_msp->sqnam,"aa",4);
   strncpy(m_msp->sqtype,"protein",10);
   m_msp->ann_flg = 0;
   m_msp->ann_arr[0] = '\0';
   m_msp->aa0a = NULL;
   
   ppst->LK_set = 0;
   ppst->e_cut = m_msp->e_cut = 10.0;
   ppst->e_cut_r = ppst->e_cut / 10.0;
   ppst->do_rep = 1;
   ppst->zs_win = 0;
   ppst->show_ident = 0;

   ppst->zdb_size = -1;
   ppst->zdb_size_set = 0;
   ppst->dnaseq = SEQT_PROT;	/* default is protein */
   ppst->nt_align = 0;

   ppst->other_info = NULL;

   g_init_opts(m_msp, ppst);

   f_initenv (m_msp, ppst, aa0);

   if (argc == 1) {
     show_help(m_msp->pgm_name, ppst->pgm_id);
   }
   if (strcmp(argv[1],"-help")==0) {
     show_all_help(m_msp->pgm_name, ppst->pgm_id);
   }

   strncpy (optstring, g_optstring, sizeof (optstring));
   strncat (optstring, f_optstring, sizeof (optstring));

   while ((copt = getopt (argc, argv, optstring)) != EOF)
   {
      if (strchr (g_optstring, copt) != NULL)
      {
	switch (copt) {  /* switches for all options */
	case 'C': 
	  sscanf(optarg,"%d",&m_msp->nmlen);
	  if (m_msp->nmlen > MAX_UID-1) m_msp->nmlen = MAX_UID-1;
	  break;
	case 'D': ppst->debug_lib = 1;
	  break;
	case 'e': 
	  strncpy(m_msp->link_lname, optarg, MAX_LSTR);
	  break;
	case 'F':
	  sscanf(optarg,"%lg",&m_msp->e_low);
	  m_msp->e_cut_set = 1;
	  break;
#if defined(PCOMPLIB) || !defined(SHOW_HIST)
	case 'H':
	  m_msp->nohist = 0; break;
#else
	case 'H':
	  m_msp->nohist = 1; break;
#endif
	case 'i':
	  m_msp->revcomp = 1; break;
	case 'I':
	  m_msp->quiet = 0; break;
	case 'l':
	  strncpy(m_msp->flstr,optarg,MAX_FN);
	  m_msp->flstr[MAX_FN-1]='\0';
	  break;
	case 'L':
	  m_msp->long_info = 1;
	  long_info_set = 1;
	  break;
	case 'm':
	  pre_parse_markx(optarg, m_msp);
	  break;
	case 'N':
	  sscanf(optarg,"%d",&m_msp->ldb_info.maxn);
	  break;
	case 'o':
	  sscanf (optarg,"%ld %ld",&m_msp->sq0off,&m_msp->sq1off); break;
	case 'O':
	  strncpy(m_msp->outfile,optarg,MAX_FN);
	  m_msp->outfile[MAX_FN-1]='\0';
	  break;
	case 'q':
	case 'Q':
	  m_msp->quiet = 1;
	  break;
	case 'R':
	  strncpy (m_msp->dfile, optarg, MAX_FN);
	  m_msp->dfile[MAX_FN-1]='\0';
	  break;
	case 'T':
#ifdef PCOMPLIB
	  if (strchr(optarg,'-') != NULL) {
	    sscanf(optarg,"%d-%d",&worker_1,&worker_n);
	    if (worker_1 > worker_n) {
	      worker_1 = worker_n = 0;
	    }
	  }
	  else 
#endif
	    sscanf (optarg, "%d", &fa_max_workers);
	  if (fa_max_workers < 0) fa_max_workers=1;
	  break;
	case 'v':
	  sscanf (optarg,"%d",&ppst->zs_win);
	  break;
	case 'V':
	  strncpy(m_msp->ann_arr+1,optarg,MAX_FN-2);
	  m_msp->ann_arr[0]='\0';
	  m_msp->ann_arr[MAX_FN-2]='\0';
	  m_msp->ann_flg = 1;
	  add_ascii_ann(qascii, m_msp->ann_arr);
	  break;
/*
	case 'V':
	  fprintf(stderr," -V option not currently supported in parallel\n");
	  break;
*/
	case 'w':
	  sscanf (optarg,"%d",&m_msp->aln.llen);
	  if (m_msp->aln.llen < 10) m_msp->aln.llen = 10;
	  if (m_msp->aln.llen > 200) m_msp->aln.llen = 200;
	  if (!m_msp->aln.llcntx_set) m_msp->aln.llcntx = m_msp->aln.llen/2;
	  llen_set = 1;
	  break;
	case 'Z':
	  sscanf(optarg,"%ld",&ppst->zdb_size);
	  ppst->zdb_size_set = 1;
	  break;
	}
      }
      else if (strchr (f_optstring, copt))
	 f_getopt (copt, optarg, m_msp, ppst);
   }
   optind--;

   f_lastenv (m_msp, ppst);

   if (argc - optind < 3) return;
   m_msp->tnamesize = sizeof (m_msp->tname);
   if (argc - optind > 1) {strncpy (m_msp->tname, argv[optind + 1],MAX_FN);}
   if (argc - optind > 2) {strncpy(m_msp->lname, argv[optind + 2],MAX_LSTR);}
   f_getarg (argc, argv, optind, m_msp, ppst);
}
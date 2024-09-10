int run(int argc, char **argv)
{
    args_t *args  = (args_t*) calloc(1,sizeof(args_t));
    args->nsites = 10;
    args->min_hets = 0.3;
    args->background = "X:60001-2699520";
    static struct option loptions[] =
    {
        {"verbose",1,0,'v'},
        {"ploidy",1,0,'p'},
        {"nsites",1,0,'n'},
        {"guess",1,0,'g'},
        {"min-hets",1,0,'m'},
        {"background",1,0,'b'},
        {0,0,0,0}
    };
    char c, *tmp, *ploidy_fname = NULL;
    while ((c = getopt_long(argc, argv, "p:n:g:m:vb:",loptions,NULL)) >= 0)
    {
        switch (c) {
            case 'b': 
                if ( !strcmp("-",optarg) ) args->background = NULL;
                else args->background = optarg; 
                break; 
            case 'v': args->verbose = 1; break; 
            case 'g':
                if ( !strcasecmp(optarg,"GT") ) args->guess = GUESS_GT;
                else if ( !strcasecmp(optarg,"PL") ) args->guess = GUESS_PL;
                else if ( !strcasecmp(optarg,"GL") ) args->guess = GUESS_GL;
                else error("The argument not recognised, expected --guess GT, --guess PL or --guess GL: %s\n", optarg);
                break;
            case 'm': 
                args->min_hets = strtod(optarg,&tmp); 
                if ( *tmp ) error("Unexpected argument to --min-hets: %s\n", optarg);
                break; 
            case 'p': ploidy_fname = optarg; break; 
            case 'n': 
                args->nsites = strtol(optarg,&tmp,10); 
                if (*tmp) error("Unexpected argument to --nsites: %s\n", optarg); break; 
            case 'h':
            case '?':
            default: error("%s", usage()); break;
        }
    }

    args->sr = bcf_sr_init();
    args->sr->require_index = 1;
    if ( !argv[0] ) error("%s", usage());
    if ( !bcf_sr_add_reader(args->sr,argv[0]) ) error("Error: %s\n", bcf_sr_strerror(args->sr->errnum));
    args->hdr = args->sr->readers[0].header;
    args->nsample = bcf_hdr_nsamples(args->hdr);
 
    args->dflt_ploidy = 2;
    if ( ploidy_fname )
    {
        args->ploidy = ploidy_init(ploidy_fname, args->dflt_ploidy);
        if ( !args->ploidy ) error("Could not read %s\n", ploidy_fname);
    }
    else
    {
        args->ploidy = ploidy_init_string(
                "X 1 60000 M 1\n"
                "X 2699521 154931043 M 1\n"
                "Y 1 59373566 M 1\n"
                "Y 1 59373566 F 0\n", args->dflt_ploidy);
    }
    args->nsex = ploidy_nsex(args->ploidy);
    args->sex2ploidy = (int*) malloc(sizeof(int)*args->nsex);
    args->max_ploidy = ploidy_max(args->ploidy);
    if ( args->guess && args->max_ploidy > 2 ) error("Sorry, ploidy %d not supported with -g\n", args->max_ploidy);
    args->ncounts = args->nsample * ((args->max_ploidy>2 ? args->max_ploidy : 2)+1);
    args->counts = (int*) malloc(sizeof(int)*args->ncounts);
    args->bg_counts = (count_t*) calloc(args->nsample,sizeof(count_t));
    args->sex2prob = (float*) calloc(args->nsample*args->nsex,sizeof(float));

    int i, nseq;
    for (i=0; i<args->nsample*args->nsex; i++) args->sex2prob[i] = 1;

    if ( args->verbose && args->guess )
        printf("# [1]REG\t[2]Region\t[3]Sample\t[4]Het fraction\t[5]nHet\t[6]nHom\t[7]nMissing\n");

    // First get the counts from expected haploid regions
    regidx_t *idx = ploidy_regions(args->ploidy);
    char **seqs = regidx_seq_names(idx, &nseq);
    for (i=0; i<nseq; i++)
    {
        regitr_t itr;
        regidx_overlap(idx, seqs[i], 0, UINT32_MAX, &itr);
        while ( itr.i < itr.n )
        {
            if ( args->guess )
                itr.i += process_region_guess(args, seqs[i], &itr);
            else
                itr.i += process_region_precise(args, seqs[i], &itr);
        }
    }
    // Get the counts from a PAR (the background diploid region) and see if the fraction
    // of hets is different
    if ( args->guess ) sex2prob_guess(args);

    for (i=0; i<args->nsample; i++)
    {
        int j, jmax = 0;
        float max = 0, sum = 0;
        for (j=0; j<args->nsex; j++)
        {
            sum += args->sex2prob[i*args->nsex+j];
            if ( max < args->sex2prob[i*args->nsex+j] )
            {
                jmax = j;
                max = args->sex2prob[i*args->nsex+j];
            }
        }
        if ( args->verbose )
            printf("%s\t%s\t%f\n", args->hdr->samples[i],ploidy_id2sex(args->ploidy,jmax),args->sex2prob[i*args->nsex+jmax]/sum);
        else
            printf("%s\t%s\n", args->hdr->samples[i],ploidy_id2sex(args->ploidy,jmax));
    }
   
    bcf_sr_destroy(args->sr);
    ploidy_destroy(args->ploidy);
    destroy_regs(args);
    free(args->sex2ploidy);
    free(args->counts);
    free(args->bg_counts);
    free(args->gts);
    free(args->pls);
    free(args->sex2prob);
    free(args);
    return 0;
}
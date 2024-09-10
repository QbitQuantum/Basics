int main_vcfcall(int argc, char *argv[])
{
    char *ploidy_fname = NULL, *ploidy = NULL;
    args_t args;
    memset(&args, 0, sizeof(args_t));
    args.argc = argc; args.argv = argv;
    args.aux.prior_type = -1;
    args.aux.indel_frac = -1;
    args.aux.theta      = 1.1e-3;
    args.aux.pref       = 0.5;
    args.aux.min_perm_p = 0.01;
    args.aux.min_lrt    = 1;
    args.flag           = CF_ACGT_ONLY;
    args.output_fname   = "-";
    args.output_type    = FT_VCF;
    args.aux.trio_Pm_SNPs = 1 - 1e-8;
    args.aux.trio_Pm_ins  = args.aux.trio_Pm_del  = 1 - 1e-9;

    int c;
    static struct option loptions[] =
    {
        {"help",0,0,'h'},
        {"gvcf",1,0,'g'},
        {"format-fields",1,0,'f'},
        {"output",1,0,'o'},
        {"output-type",1,0,'O'},
        {"regions",1,0,'r'},
        {"regions-file",1,0,'R'},
        {"samples",1,0,'s'},
        {"samples-file",1,0,'S'},
        {"targets",1,0,'t'},
        {"targets-file",1,0,'T'},
        {"keep-alts",0,0,'A'},
        {"insert-missed",0,0,'i'},
        {"skip-Ns",0,0,'N'},            // now the new default
        {"keep-masked-refs",0,0,'M'},
        {"skip-variants",1,0,'V'},
        {"variants-only",0,0,'v'},
        {"consensus-caller",0,0,'c'},
        {"constrain",1,0,'C'},
        {"multiallelic-caller",0,0,'m'},
        {"pval-threshold",1,0,'p'},
        {"prior",1,0,'P'},
        {"chromosome-X",0,0,'X'},
        {"chromosome-Y",0,0,'Y'},
        {"novel-rate",1,0,'n'},
        {"ploidy",1,0,1},
        {"ploidy-file",1,0,2},
        {0,0,0,0}
    };

    char *tmp = NULL;
    while ((c = getopt_long(argc, argv, "h?o:O:r:R:s:S:t:T:ANMV:vcmp:C:XYn:P:f:ig:", loptions, NULL)) >= 0)
    {
        switch (c)
        {
            case 'g':
                args.flag |= CF_GVCF;
                args.gvcf.min_dp = strtol(optarg,&tmp,10);
                if ( *tmp ) error("Could not parse, expected integer argument: -g %s\n", optarg);
                break;
            case  2 : ploidy_fname = optarg; break;
            case  1 : ploidy = optarg; break;
            case 'X': ploidy = "X"; fprintf(stderr,"Warning: -X will be deprecated, please use --ploidy instead.\n"); break;
            case 'Y': ploidy = "Y"; fprintf(stderr,"Warning: -Y will be deprecated, please use --ploidy instead.\n"); break;
            case 'f': args.aux.output_tags |= parse_format_flag(optarg); break;
            case 'M': args.flag &= ~CF_ACGT_ONLY; break;     // keep sites where REF is N
            case 'N': args.flag |= CF_ACGT_ONLY; break;      // omit sites where first base in REF is N (the new default)
            case 'A': args.aux.flag |= CALL_KEEPALT; break;
            case 'c': args.flag |= CF_CCALL; break;          // the original EM based calling method
            case 'i': args.flag |= CF_INS_MISSED; break;
            case 'v': args.aux.flag |= CALL_VARONLY; break;
            case 'o': args.output_fname = optarg; break;
            case 'O':
                      switch (optarg[0]) {
                          case 'b': args.output_type = FT_BCF_GZ; break;
                          case 'u': args.output_type = FT_BCF; break;
                          case 'z': args.output_type = FT_VCF_GZ; break;
                          case 'v': args.output_type = FT_VCF; break;
                          default: error("The output type \"%s\" not recognised\n", optarg);
                      }
                      break;
            case 'C':
                      if ( !strcasecmp(optarg,"alleles") ) args.aux.flag |= CALL_CONSTR_ALLELES;
                      else if ( !strcasecmp(optarg,"trio") ) args.aux.flag |= CALL_CONSTR_TRIO;
                      else error("Unknown argument to -C: \"%s\"\n", optarg);
                      break;
            case 'V':
                      if ( !strcasecmp(optarg,"snps") ) args.flag |= CF_INDEL_ONLY;
                      else if ( !strcasecmp(optarg,"indels") ) args.flag |= CF_NO_INDEL;
                      else error("Unknown skip category \"%s\" (-S argument must be \"snps\" or \"indels\")\n", optarg);
                      break;
            case 'm': args.flag |= CF_MCALL; break;         // multiallelic calling method
            case 'p':
                args.aux.pref = strtod(optarg,&tmp);
                if ( *tmp ) error("Could not parse: --pval-threshold %s\n", optarg);
                break;
            case 'P': args.aux.theta = strtod(optarg,&tmp);
                      if ( *tmp ) error("Could not parse, expected float argument: -P %s\n", optarg);
                      break;
            case 'n': parse_novel_rate(&args,optarg); break;
            case 'r': args.regions = optarg; break;
            case 'R': args.regions = optarg; args.regions_is_file = 1; break;
            case 't': args.targets = optarg; break;
            case 'T': args.targets = optarg; args.targets_is_file = 1; break;
            case 's': args.samples_fname = optarg; break;
            case 'S': args.samples_fname = optarg; args.samples_is_file = 1; break;
            default: usage(&args);
        }
    }
    // Sanity check options and initialize
    if ( ploidy_fname ) args.ploidy = ploidy_init(ploidy_fname, 2);
    else if ( ploidy ) args.ploidy = init_ploidy(ploidy);

    if ( optind>=argc )
    {
        if ( !isatty(fileno((FILE *)stdin)) ) args.bcf_fname = "-";  // reading from stdin
        else usage(&args);
    }
    else args.bcf_fname = argv[optind++];

    if ( !ploidy_fname && !ploidy )
    {
        fprintf(stderr,"Note: Neither --ploidy nor --ploidy-file given, assuming all sites are diploid\n");
        args.ploidy = ploidy_init_string("",2);
    }

    if ( !args.ploidy ) error("Could not initialize ploidy\n");
    if ( args.flag & CF_GVCF )
    {
        // Force some flags to avoid unnecessary branching
        args.aux.flag &= ~CALL_KEEPALT;
        args.aux.flag |= CALL_VARONLY;
    }
    if ( (args.flag & CF_CCALL ? 1 : 0) + (args.flag & CF_MCALL ? 1 : 0) + (args.flag & CF_QCALL ? 1 : 0) > 1 ) error("Only one of -c or -m options can be given\n");
    if ( !(args.flag & CF_CCALL) && !(args.flag & CF_MCALL) && !(args.flag & CF_QCALL) ) error("Expected -c or -m option\n");
    if ( args.aux.n_perm && args.aux.ngrp1_samples<=0 ) error("Expected -1 with -U\n");    // not sure about this, please fix
    if ( args.aux.flag & CALL_CONSTR_ALLELES )
    {
        if ( !args.targets ) error("Expected -t or -T with \"-C alleles\"\n");
        if ( !(args.flag & CF_MCALL) ) error("The \"-C alleles\" mode requires -m\n");
    }
    if ( args.flag & CF_INS_MISSED && !(args.aux.flag&CALL_CONSTR_ALLELES) ) error("The -i option requires -C alleles\n");
    init_data(&args);

    while ( bcf_sr_next_line(args.aux.srs) )
    {
        bcf1_t *bcf_rec = args.aux.srs->readers[0].buffer[0];
        if ( args.samples_map ) bcf_subset(args.aux.hdr, bcf_rec, args.nsamples, args.samples_map);
        bcf_unpack(bcf_rec, BCF_UN_STR);

        // Skip unwanted sites
        if ( args.aux.flag & CALL_VARONLY )
        {
            int is_ref = 0;
            if ( bcf_rec->n_allele==1 ) is_ref = 1;     // not a variant
            else if ( bcf_rec->n_allele==2 )
            {
                // second allele is mpileup's X, not a variant
                if ( bcf_rec->d.allele[1][0]=='X' ) is_ref = 1;
                else if ( bcf_rec->d.allele[1][0]=='<' && bcf_rec->d.allele[1][1]=='X' && bcf_rec->d.allele[1][2]=='>' ) is_ref = 1;
                else if ( bcf_rec->d.allele[1][0]=='<' && bcf_rec->d.allele[1][1]=='*' && bcf_rec->d.allele[1][2]=='>' ) is_ref = 1;
            }
            if ( is_ref )
            {
                // gVCF output
                if ( args.flag & CF_GVCF ) gvcf_write(args.out_fh, &args.gvcf, args.aux.hdr, bcf_rec, 1);
                continue;
            }
        }
        if ( (args.flag & CF_INDEL_ONLY) && bcf_is_snp(bcf_rec) ) continue;    // not an indel
        if ( (args.flag & CF_NO_INDEL) && !bcf_is_snp(bcf_rec) ) continue;     // not a SNP
        if ( (args.flag & CF_ACGT_ONLY) && (bcf_rec->d.allele[0][0]=='N' || bcf_rec->d.allele[0][0]=='n') ) continue;   // REF[0] is 'N'

        bcf_unpack(bcf_rec, BCF_UN_ALL);
        if ( args.nsex ) set_ploidy(&args, bcf_rec);

        // Various output modes: QCall output (todo)
        if ( args.flag & CF_QCALL )
        {
            qcall(&args.aux, bcf_rec);
            continue;
        }

        // Calling modes which output VCFs
        int ret;
        if ( args.flag & CF_MCALL )
            ret = mcall(&args.aux, bcf_rec);
        else
            ret = ccall(&args.aux, bcf_rec);
        if ( ret==-1 ) error("Something is wrong\n");

        // gVCF output
        if ( args.flag & CF_GVCF )
        {
            gvcf_write(args.out_fh, &args.gvcf, args.aux.hdr, bcf_rec, ret?0:1);
            continue;
        }

        // Normal output
        if ( (args.aux.flag & CALL_VARONLY) && ret==0 ) continue;     // not a variant
        bcf_write1(args.out_fh, args.aux.hdr, bcf_rec);
    }
    if ( args.flag & CF_GVCF ) gvcf_write(args.out_fh, &args.gvcf, args.aux.hdr, NULL, 0);
    if ( args.flag & CF_INS_MISSED ) bcf_sr_regions_flush(args.aux.srs->targets);
    destroy_data(&args);
    return 0;
}
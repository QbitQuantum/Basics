int main(int argc, char **argv) 
{
    int i;
    // init static stuff
    for (i = 0; i < MAXSMPLS; ++i)
        freq[i] = 0;
    for (i = 0; i < PRECMP; ++i)
    {
        prelog[i] = log(i+1);
        presqrt[i] = sqrt(i);
        prelgamma[i] = lgamma(i+1);
    }

    if (argc < 5)
    {
        longhelp(argv[0]);
        return 1;
    }

    int parsepvalues = 0;
    int normalize = 0;
    int smpls = -1, runs = -1;
    int *runtosmpl = 0;
    double *maxent = 0;
    int nmaxent = 0;
    char filesuffix[ROWLEN];
    char smplsfile[ROWLEN];
    char normfile[ROWLEN];
    filesuffix[0] = 0; // empty
    smplsfile[0] = 0;
    normfile[0] = 0;

    static struct option long_options[] =
        {
            {"samples",      required_argument, 0, 's'},
            {"samplefile",   required_argument, 0, 'S'},
            {"maxent",       required_argument, 0, 'm'},
            {"entstep",      required_argument, 0, 'e'},
            {"file",         required_argument, 0, 'F'},            
            {"normalize",    required_argument, 0, 'N'},
            {"minfreq",      required_argument, 0, 'M'},
            {"verbose",      no_argument,       0, 'v'},
            {"help",         no_argument,       0, 'h'},
            {0, 0, 0, 0}
        };
    int option_index = 0;
    int c;
    while ((c = getopt_long(argc, argv, "s:S:m:e:F:N:M:vh", long_options, &option_index)) != -1) 
    {
        switch(c) 
        {
        case 's':
            smpls = atoi_min(optarg, 2, "-s,--samples", argv[0]); 
            break;
        case 'S':
            strncpy(smplsfile, optarg, ROWLEN);
            break;
        case 'm':
            assert(maxent == 0);
            maxent = parse_doubles(optarg, &nmaxent, 0.0, 1.0, "-m,--maxent", argv[0]);
            break;
        case 'e':
            assert(maxent == 0);
            maxent = parse_entropy_steps(optarg, &nmaxent, 0.0, 1.0, "-e,--entstep", argv[0]);
            break;
        case 'F':
            strncpy(filesuffix, optarg, ROWLEN);
            break;
        case 'N':
            normalize = 1;
            strncpy(normfile, optarg, ROWLEN);
            break;
        case 'M':
            minfreq = atoi_min(optarg, 1, "-M,--minfreq", argv[0]); 
            break;
        case 'v':
            verbose = 1; 
            break;
        case 'h':
            longhelp(argv[0]); 
            return 1;
        default:
            myerror("invalid command line argument given!? Please check `%s --help'\n", argv[0]);
            return 1;
            break;
        }
    }

    if (argc != optind)
        fprintf(stderr, "warning: ignoring the last %d arguments\n", argc-optind);

    // sanity checks
    if (filesuffix[0] == 0)
        myerror("the argument -F,--file is mandatory.", argv[0]);
    if (nmaxent < 1)
        myerror("the argument -m,--maxent is mandatory.", argv[0]);
    if (smpls == -1 && strlen(smplsfile) == 0)
        myerror("give either the argument -s,--samples or -S,--samplefile.", argv[0]);
    if (smpls != -1 && strlen(smplsfile))
        myerror("both the arguments -s,--samples and -S,--samplefile cannot be given at the same time.", argv[0]);
    if (smpls != -1 && smpls < 2)
        myerror("the argument -s,--samples must be at least 2.", argv[0]);
    if (nmaxent == 0)
        myerror("the argument -m,--maxent is mandatory.", argv[0]);

    // Parse samples file if needed
    if (smpls == -1)
    {
        assert(strlen(smplsfile));
        runs = parse_samples_file(smplsfile, &runtosmpl, &smpls);
        if (verbose) fprintf(stderr, "sample file: got mapping from %d runs to %d samples\n", runs, smpls);
        if (smpls < 2 || runs < smpls)
            myerror("unable to parse the samples file in the argument -S,--samplefile.", argv[0]);
    }
    else
        runs = smpls;

    if (runs > MAXSMPLS)
    {
        fprintf(stderr, "error: expecting at most %d samples/runs, please increase MAXSMPLS in the source code and recompile\n", MAXSMPLS);
        abort();
    }

    // Parse normalization factors
    double *dsizes = 0;
    if (normalize || normfile[0])
    {
        assert (normalize);
        dsizes = parse_size_file(normfile, smpls);
        assert(dsizes != 0);

        // Compute norm. factors
        assert (smpls < MAXSMPLS);
        for (i = 0; i < smpls; ++i)
        {
            // Iterates over samples to precompute
            assert(dsizes[i] != 0);
            nfactor[i] = (double)1/dsizes[i];

            // Init precomputed values
            prenormlog[i] =    (double *)malloc(PRECMP * sizeof(double));
            prenormsqrt[i] =   (double *)malloc(PRECMP * sizeof(double));
//            prenormlgamma[i] = (double *)malloc(PRECMP * sizeof(double));
            int j;
            for (j = 0; j < PRECMP; ++j)
            {
                // i == sample, j == frequency
                prenormlog[i][j] = log((double)j*nfactor[i] + 1);
                prenormsqrt[i][j] = sqrt((double)j*nfactor[i]);
//                prenormlgamma[i][j] = lgamma((double)j*nfactor[i] + 1); 
            }
        }
        if (verbose) fprintf(stderr, "normalization file %s loaded\n", normfile);
        free(dsizes);
    }

    // Init the matrices
    i = 0;
    int j, nmatrices = nmaxent;
    struct parameters *param = (struct parameters *)malloc(nmatrices * sizeof(struct parameters));
    for (j = 0; j < nmaxent; ++j)
    {
        param[i].maxent = maxent[j];
        param[i].noutput = 0;
        ++i;
    }
    FILE *fileCount = open_output_file(filesuffix, "count");
    FILE *fileLog = open_output_file(filesuffix, "log");
    FILE *fileSqrt = open_output_file(filesuffix, "sqrt");
    FILE *fileLgamma = open_output_file(filesuffix, "lgamma");

    assert(i == nmatrices);
    qsort(param, nmatrices, sizeof(struct parameters), myparamcmp);

    if (verbose)
    {
        fprintf(stderr, "Computing %d matrices for <max_entropy> values:", nmatrices);
        for (i = 0; i < nmatrices; ++i)
            fprintf(stderr, (i == 0 ? " <%f>" : ", <%f>"), param[i].maxent);
        fprintf(stderr, "\n"); 
    }

    // Init matrices
    mymatrix *matrix = (mymatrix *)malloc(nmatrices * smpls * smpls * sizeof(mymatrix));
    for (i = 0; i < nmatrices * smpls * smpls; ++i)
    {
        matrix[i].count = 0;
        matrix[i].log = 0;
        matrix[i].sqrt = 0;
        matrix[i].lgamma = 0;
    }        

    // Init parsing
    time_t wctime = time(NULL);    
    char row[ROWLEN];
    unsigned long rowno = 0;
    while (!feof(stdin))
    {
        if (fgets(row, ROWLEN, stdin) == NULL)
            break;

        char *tmp = row; 
        while (*tmp && *tmp != ' ') ++tmp; // Finds the first ' ',
        assert(*tmp == ' ');
        // Check if we need to parse p-values
        if (rowno == 0)
        {
            char *t = tmp;
            while (*t && *t != '.') ++t;
            if (*t == '.')
                parsepvalues = 1;
            else
                assert(parsepvalues == 0);
        }
        if (parsepvalues)
        {
            //double entropy = atof(tmp++);  // FIXME We need to recompute the entropy if runtosmpl mapping is set
            ++tmp;
            while (*tmp && *tmp != ' ') ++tmp; // Finds the second ' ',
            assert(*tmp == ' ');
        }

        // Parse row
        unsigned uniqueids = parse(tmp, runs, runtosmpl);
        // Retrieve the difference to max. entropy
        double entr = -1;
        if (normalize)
            entr = normalized_entropy(uniqueids, smpls);
        else
            entr = entropy(uniqueids, smpls);

        // Update correct matrix (note: only one matrix needs to be updated, values are accumulated later)
        for (i = nmatrices; i > 0;)
        {
            --i;
            if (entr <= param[i].maxent)
            {
                param[i].noutput ++;
                if (normalize)
                    add_normalized(matrix, smpls, uniqueids, i);
                else
                               add(matrix, smpls, uniqueids, i);
                
                break;
            }
        }
        // Zero the vector
        for (i = 0; i < uniqueids; ++i)
            freq[samples[i]] = 0;
        
        rowno++;
        if (verbose && rowno % 1000000 == 0)
        {
            fprintf(stderr, "Reading row %lu (%.5s...). Time: %.0f s (%.2f hours)\n", rowno, row, difftime(time(NULL), wctime), difftime(time(NULL), wctime) / 3600);
            fprintf(stderr, "noutput values: ");
            int j;
            for (j = 0; j < nmatrices; ++j)
                fprintf(stderr, " %u", param[j].noutput);
            fprintf(stderr, "\n");
        }
    }

    for (i = 0; i < MAXSMPLS; ++i)
        assert(freq[i] == 0);

    // Print output matrices
    for (i = nmatrices; i > 0;)
    {
        --i;
        fprintf(fileCount,  "Matrix for <max_entropy>=<%f> was computed from %u substrings: \n", param[i].maxent, param[i].noutput);
        fprintf(fileLog,    "Matrix for <max_entropy>=<%f> was computed from %u substrings: \n", param[i].maxent, param[i].noutput);
        fprintf(fileSqrt,   "Matrix for <max_entropy>=<%f> was computed from %u substrings: \n", param[i].maxent, param[i].noutput);
        fprintf(fileLgamma, "Matrix for <max_entropy>=<%f> was computed from %u substrings: \n", param[i].maxent, param[i].noutput);
        
        int k;
        for (j = 0; j < smpls; ++j)
        {
            for (k = 0; k < smpls; ++k)
            {
                fprintf(fileCount,  " %u", matrix[OFFSET(i,j,k)].count);
                fprintf(fileLog,    " %f", matrix[OFFSET(i,j,k)].log);
                fprintf(fileSqrt,   " %f", matrix[OFFSET(i,j,k)].sqrt);
                fprintf(fileLgamma, " %f", matrix[OFFSET(i,j,k)].lgamma);
            }
            fprintf(fileCount, "\n");
            fprintf(fileLog, "\n");
            fprintf(fileSqrt, "\n");
            fprintf(fileLgamma, "\n");
        }

        // Accumulate counts from larger diffs
        if (i)
        {
            param[i-1].noutput += param[i].noutput;
            accumulate(matrix, i, i-1, smpls);        
        }
    }

    if (verbose)
    {
        fprintf(stderr, "Number of lines processed: %lu\n", rowno);
        fprintf(stderr, "Wall-clock time: %.0f s (%.2f hours)\n", difftime(time(NULL), wctime), difftime(time(NULL), wctime) / 3600);
    }

    fclose(fileCount);
    fclose(fileLog);
    fclose(fileSqrt);
    fclose(fileLgamma);
    free(param);
    free(maxent);
    free(matrix);
    if (runtosmpl) 
        free(runtosmpl);
    if (normalize)
        for (i = 0; i < smpls; ++i)
        {
            free (prenormlog[i]);
            free (prenormsqrt[i]);
//            free (prenormlgamma[i]);
        }
    return 0;
}
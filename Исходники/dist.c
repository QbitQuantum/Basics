int
parse_args (int argc, char *argv[], table_t *tab)
{
    unsigned char haveflags = 0;
    /*
        1 1 1 1 1 1 1 1
            | | | | | \- method
            | | | | \--- out fname
            | | | \----- in fname
            | | \------- cols to skip
            | \--------- rows to skip
            \----------- Field sep
    */
    char c = '\0';
    while((c = getopt(argc, argv, "mCM:r:c:o:i:s:h")) >= 0) {
        switch (c) {
            case 'm':
                haveflags |= 1;
                tab->row_fn = &dm_manhattan;
                tab->mode = D64;
                break;
            case 'M':
                haveflags |= 1;
                tab->row_fn = &dm_manhattan_binary;
                tab->mode = D64;
                binary_cutoff.d = strtold(optarg, NULL);
                break;
            case 'C':
                haveflags |= 1;
                tab->mode = D64;
                tab->row_fn = &dm_canberra;
                break;
            case 'o':
                haveflags |= 2;
                tab->outfname = strdup(optarg);
                break;
            case 'i':
                haveflags |= 4;
                tab->fname = strdup(optarg);
                break;
            case 'c':
                haveflags |= 8;
                tab->skipcol = atol(optarg);
                break;
            case 'r':
                haveflags |= 16;
                tab->skiprow = atol(optarg);
                break;
            case 's':
                haveflags |= 32;
                tab->sep = strdup(optarg);
                break;
            case 'h':
                print_usage();
                destroy_distmat_table_t(tab);
                exit(EXIT_SUCCESS);
        }
    }
    if (tab->sep == NULL) {
        tab->sep = strdup("\t");
    }
    /* Setup input fp */
    if ((!(haveflags & 4)) || tab->fname == NULL || \
            strncmp(tab->fname, "-", 1) == 0) {
        tab->fp = fdopen(fileno(stdin), "r");
        tab->fname = strdup("stdin");
        haveflags |= 4;
    } else {
        tab->fp = fopen(tab->fname, "r");
    }
    if (tab->fp == NULL) {
        fprintf(stderr, "Could not open file '%s'\n%s\n", tab->fname,
                strerror(errno));
        return 0;
    }
    /* Setup output fp */
    if ((!(haveflags & 2)) || tab->outfname == NULL || \
            strncmp(tab->outfname, "-", 1) == 0) {
        tab->outfp = fdopen(fileno(stdout), "w");
        tab->outfname = strdup("stdout");
        haveflags |= 2;
    } else {
        tab->outfp = fopen(tab->outfname, "w");
    }
    if (tab->outfp == NULL) {
        fprintf(stderr, "Could not open file '%s'\n%s\n", tab->outfname,
                strerror(errno));
        return 0;
    }
    if ((haveflags & 7) != 7) {
        fprintf(stderr, "[parse_args] Required arguments missing\n");
        return 0;
    }
    return 1; /* Successful */
}
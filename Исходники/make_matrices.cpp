int load_energies(EMATRIX *ematrix, char *dir, int verbose)
/* this program returns number of conformers loaded, or -1 if no exsiting energy table */
{
	int i, n_conf;
    char sbuff[128];
    FILE *fp, *fp2;
    CONF_HEAD *conf;
    PAIRWISE *pw;
    char version[128];

    /* Obtain the first line of the energy lookup table, which is the number of conformers */
    sprintf(sbuff, "%s/%s", dir, ENERGY_TABLE);
    if (!(fp = fopen(sbuff, "r"))) {
        printf("energies.opp not found\n");
        return -1;
    }

    // unzip the energies.opp
    fp2 = tmpfile();
    inf(fp, fp2);
    rewind(fp2);
    fclose(fp);


    fgets(sbuff, sizeof(sbuff), fp2);
    if (sscanf(sbuff, "%d %s", &n_conf, version) != 2) {

       printf("   Version mismatch: Opp file was made by pre-MCCE2.3 and this program is for %s\n", VERSION);
       printf("                     Use oppconvert to fix the mismatch\n");
       return USERERR;
    }

    if (strncmp(VERSION, version, 7)) {
    	/* Do not check the version any more, xz 07-06-2013.
       printf("   Version mismatch: Opp file was made by %s and this program is for %s\n", version, VERSION);
       printf("                     Use oppconvert to fix the mismatch\n");
       return USERERR;
         */
    }

    /* allocate memeory */
    if (ematrix->n > 0) {  /* existing table */
       if (ematrix->n != n_conf) {
          printf("error in loading Energy lookup table size %d on to %d\n", n_conf, ematrix->n);
          return USERERR;
       }
    }
    else {
       if (!(ematrix->conf = (CONF_HEAD *) calloc(n_conf, sizeof(CONF_HEAD)))) {
          printf("   Memory error in A load_energies\n");
          return 0; /* none loaded and memory cleared */
       }
       if (!(ematrix->pw = (PAIRWISE **) calloc(n_conf, sizeof(PAIRWISE *)))) {
          printf("   Memory error in B load_energies\n");
          return 0; /* none loaded and memory cleared */
       }
       for (i=0; i<n_conf; i++) {
          if (!(ematrix->pw[i] = (PAIRWISE *) calloc(n_conf, sizeof(PAIRWISE)))) {
             printf("   Memory error in C load_energies\n");
             return 0; /* none loaded and memory cleared */
          }
       }
       ematrix->n = n_conf;
    }

    /* Buffer of head part */
    if (!(conf = (CONF_HEAD *) calloc(n_conf, sizeof(CONF_HEAD)))){
          printf("   Memory error loading head in load_energies\n");
          return USERERR;
    }
    if (!(pw = (PAIRWISE *) calloc(n_conf, sizeof(PAIRWISE)))){
          printf("   Memory error loading PW buffer in load_energies\n");
          return USERERR;
    }


    if (fread(conf, sizeof(CONF_HEAD), ematrix->n, fp2) != n_conf) {
        printf("   Error in loading pairwise interaction headers at position %d\n", i);
        return USERERR;
    }
    for (i=0; i<ematrix->n; i++) {
        fread(pw, sizeof(PAIRWISE), ematrix->n, fp2);
		if ( verbose == 1 ) {
			printf("reading row %05d\r", i); fflush(stdout);
		}
        
        if (conf[i].on == 't') {
           memcpy(&ematrix->conf[i], &conf[i], sizeof(CONF_HEAD));
           memcpy(ematrix->pw[i], pw, ematrix->n*sizeof(PAIRWISE));
        }
        if (ematrix->conf[i].on != 't') /* initilize even if not a valid delphi run */
           memcpy(&ematrix->conf[i], &conf[i], sizeof(CONF_HEAD));
    }
    if ( verbose == 1) {
		printf("\n"); fflush(stdout);
    }
    free(conf);
    free(pw);
    fclose(fp2);
    return n_conf;
}
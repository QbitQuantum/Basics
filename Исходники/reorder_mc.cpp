/*---------------------------------------*/
void mulcol(csr_t *A, options_t *opts,
            precon_t *prec, int *perm) {
    /*---------------------------------------*/
    PREC_TYPE ptype;
    int n,i,maxcol,ncol,*kolrs,*il,err;
    csr_t *C;
    /*---------------------------------------*/
    n = A->n;
    ptype = opts->prectype;
    printf("begin MULTI-COLOR ...\n");
    /*------- symetrize matrix */
    Calloc(C, 1, csr_t);
    symmgraph(A, C);
    /*-------- multi-color reordering */
    if (ptype == MCSOR)
        maxcol = opts->mcsor_opt->maxcol;
    else
        maxcol = opts->mcilu0_opt->maxcol;
    /*---------------------*/
    Calloc(kolrs, n, int);
    Calloc(il, maxcol+1, int);
    /*-------- input node order */
    for (i=0; i<n; i++) perm[i] = i+1;
    /*-------- multi-coloring, greedy alg */
    multic_(&n, C->ja, C->ia, &ncol, kolrs,
            il, perm, &maxcol, &err);
    if (err != 0) {
        printf("exceed max num of colors\n");
        exit(-1);
    }
    printf("  done, %d colors\n", ncol);
    /*-----------------------*/
    if (ptype == MCSOR) {
        Calloc(prec->mcsor, 1, mcsor_prec_t);
        prec->mcsor->ncol = ncol;
        prec->mcsor->kolrs = kolrs;
        prec->mcsor->il = il;
    } else {
        Calloc(prec->mcilu0, 1, mcilu0_prec_t);
        prec->mcilu0->ncol = ncol;
        prec->mcilu0->kolrs = kolrs;
        prec->mcilu0->il = il;
    }
    /*----------------- done */
    free(C->ja);
    free(C->ia);
    free(C);
}
int main (int argc, char *argv[])
{
    FILE *ftree, *fout, *fseq;
    char ctlf[32]="pamp.ctl";
    char *Seqstr[]= {"nucleotide", "", "amino-acid", "Binary"};
    int itree, ntree, i, j, s3;
    double *space, *Ft;

#ifdef __MWERKS__
    /* Added by Andrew Rambaut to accommodate Macs -
       Brings up dialog box to allow command line parameters.
    */
    argc=ccommand(&argv);
#endif

    com.nhomo=1;
    com.print=1;
    noisy=2;
    com.ncatG=8;
    com.clock=0;
    com.cleandata=1;
    GetOptions (ctlf);
    if(argc>1) {
        strcpy(ctlf, argv[1]);
        printf("\nctlfile set to %s.\n",ctlf);
    }

    if ((fseq=fopen(com.seqf, "r"))==NULL) error2 ("seqfile err.");
    if ((fout=fopen (com.outf, "w"))==NULL) error2("outfile creation err.");
    if((fseq=fopen (com.seqf,"r"))==NULL)  error2("No sequence file!");
    ReadSeq (NULL, fseq);
    i=(com.ns*2-1)*sizeof(struct TREEN);
    if((nodes=(struct TREEN*)malloc(i))==NULL) error2("oom");

    fprintf (fout,"PAMP %15s, %s sequences\n", com.seqf, Seqstr[com.seqtype]);
    if (com.nhomo) fprintf (fout, "nonhomogeneous model\n");

    space = (double*)malloc(50000*sizeof(double));  /* *** */
    SeqDistance=(double*)malloc(com.ns*(com.ns-1)/2*sizeof(double));
    ancestor=(int*)malloc(com.ns*(com.ns-1)/2*sizeof(int));
    if (SeqDistance==NULL||ancestor==NULL) error2("oom");

    i = com.ns*(com.ns-1)/2;
    s3 = sizeof(double)*((com.ns*2-2)*(com.ns*2-2 + 4 + i) + i);
    s3 = max2(s3, com.ncode*com.ncode*(2*com.ns-2+1)*(int)sizeof(double));

    Ft = (double*) malloc(s3);
    if (space==NULL || Ft==NULL)  error2 ("oom space");

    Initialize (fout);
    if (com.ngene>1) error2 ("option G not allowed yet");

    /*
       PatternLS (fout, Ft, 0., space, &i);
       printf ("\nPairwise estimation of rate matrix done..\n");
       fflush(fout);
    */
    ftree=gfopen (com.treef,"r");
    fscanf (ftree, "%d%d", &i, &ntree);
    if (i!=com.ns) error2 ("ns in the tree file");

    FOR (itree, ntree) {

        printf ("\nTREE # %2d\n", itree+1);
        fprintf (fout,"\nTREE # %2d\n", itree+1);

        if (ReadaTreeN (ftree, &i,&j, 1)) error2 ("err tree..");
        OutaTreeN (F0, 0, 0);
        FPN (F0);
        OutaTreeN (fout, 0, 0);
        FPN (fout);

        for (i=0,maxchange=0; i<NCATCHANGE; i++) NSiteChange[i]=0;

        PathwayMP1 (fout, &maxchange, NSiteChange, Ft, space, 0);
        printf ("\nHartigan reconstruction done..\n");

        fprintf (fout, "\n\n(1) Branch lengths and substitution pattern\n");
        PatternMP (fout, Ft);
        printf ("pattern done..\n");
        fflush(fout);

        fprintf (fout, "\n\n(2) Gamma parameter\n");
        AlphaMP (fout);
        printf ("gamma done..\n");
        fflush(fout);

        fprintf (fout, "\n\n(3) Parsimony reconstructions\n");
        PathwayMP1 (fout, &maxchange, NSiteChange, Ft, space, 1);
        printf ("Yang reconstruction done..\n");
        fflush(fout);
    }
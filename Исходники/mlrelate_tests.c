int
main(int argc, char *argv[])
{
    int i,n,ids[3],t;
    double p;
    char* filename = FILENAME;
    DESCRIPTION_HASH *s;

    SIMULATION sim;       /* the sampling simulation data          */

    plan_tests(8);
    OPTIONSinit();
#ifdef HAVE_OPENMP
    n = omp_get_max_threads();
#else
    n=1;
#endif

    Options.Verbosity = 0;
    SRAND(123,i, n);
    Options.Fullsibs = true;
    Options.IgnoreAge = true;
    Options.TypingErrorDefined = 0.;
    Options.NumLoci = 5;
    DATAIOinfile(filename);
    Options.SiblingsOutformat[0] = Options.SiblingsOutformat[2] = false;
    Options.SiblingsOutformat[1] = true;
    snprintf(Options.SiblingsOutfilename[1], PATHLEN, "%s.%s", "siblings",
             D_TEXTSUFFIX);

    FREQcalcAlleleFrequencies();
    FREQcalcSummaryStatistics();
    PROBinit();
    sim = SIMstart();

    PROBcalcTriplesAndDyads();
    PROBcalcPosteriors();

    /* parentage, no missing data */
    HASH_FIND_STR(Data.sample_ids, "1574", s);
    ids[0] = s->id;
    HASH_FIND_STR(Data.sample_ids, "1578", s);
    ids[1] = s->id;
    HASH_FIND_STR(Data.sample_ids, "376", s);
    ids[2] = s->id;
    t = TIDXL(ids[0],ids[1]);
    p = Data.fs_matrix[t].ibd.fs;
    ok(fabs(p + 24.67) < 0.01, "FS ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.u;
    ok(fabs(p - 9.66) < 0.01, "delta u ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.hs;
    ok(fabs(p - 5.16) < 0.01, "delta hs ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.po;
    ok(fabs(p - 3.19) < 0.01, "delta po ibd correct");


    t = TIDXL(ids[2],ids[1]);
    p = Data.fs_matrix[t].ibd.fs;
    ok(fabs(p + 28.15) < 0.01, "FS ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.u;
    ok(fabs(p - 6.66) < 0.01, "delta u ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.hs;
    ok(fabs(p - 2.61) < 0.01, "delta hs ibd correct");
    p = Data.fs_matrix[t].ibd.fs - Data.fs_matrix[t].ibd.po;
    ok(fabs(p - 0.48) < 0.01, "delta po ibd correct");

    SIMdestroy(sim);
    PROBdestroyPreMCMC();
    DATAIOdestroyPreMCMC();
    FREQdestroyPreMCMC();
    PROBdestroyPostMCMC();
    DATAIOdestroyPostMCMC();
    FREQdestroyPostMCMC();

    RANDDESTROY(i, n);
    remove(Options.LociOutfilename);
    remove(Options.SiblingsOutfilename[1]);
    remove(Options.MismatchOutfilename);

    return exit_status();       /* Return the correct exit code */
}
int gmx_hydorder(int argc, char *argv[])
{
    static const char *desc[] = {
        "g_hydorder computes the tetrahedrality order parameters around a ",
        "given atom. Both angle an distance order parameters are calculated. See",
        "P.-L. Chau and A.J. Hardwick, Mol. Phys., 93, (1998), 511-518.",
        "for more details.[BR]"
        "This application calculates the orderparameter in a 3d-mesh in the box, and",
        "with 2 phases in the box gives the user the option to define a 2D interface in time",
        "separating the faces by specifying parameters -sgang1 and -sgang2 (It is important",
        "to select these judiciously)"
    };

    int                axis      = 0;
    static int         nsttblock = 1;
    static int         nlevels   = 100;
    static real        binwidth  = 1.0; /* binwidth in mesh           */
    static real        sg1       = 1;
    static real        sg2       = 1;   /* order parameters for bulk phases */
    static gmx_bool    bFourier  = FALSE;
    static gmx_bool    bRawOut   = FALSE;
    int                frames, xslices, yslices; /* Dimensions of interface arrays*/
    real            ***intfpos;                  /* Interface arrays (intfnr,t,xy) -potentially large */
    static char       *normal_axis[] = { NULL, "z", "x", "y", NULL };

    t_pargs            pa[] = {
        { "-d",   FALSE, etENUM, {normal_axis},
          "Direction of the normal on the membrane" },
        { "-bw",  FALSE, etREAL, {&binwidth},
          "Binwidth of box mesh" },
        { "-sgang1", FALSE, etREAL, {&sg1},
          "tetrahedral angle parameter in Phase 1 (bulk)" },
        { "-sgang2", FALSE, etREAL, {&sg2},
          "tetrahedral angle parameter in Phase 2 (bulk)" },
        { "-tblock", FALSE, etINT, {&nsttblock},
          "Number of frames in one time-block average"},
        { "-nlevel", FALSE, etINT, {&nlevels},
          "Number of Height levels in 2D - XPixMaps"}
    };

    t_filenm           fnm[] = {                      /* files for g_order    */
        { efTRX, "-f", NULL,  ffREAD },               /* trajectory file              */
        { efNDX, "-n", NULL,  ffREAD },               /* index file           */
        { efTPX, "-s", NULL,  ffREAD },               /* topology file                */
        { efXPM, "-o", "intf",  ffWRMULT},            /* XPM- surface maps	*/
        { efOUT, "-or", "raw", ffOPTWRMULT },         /* xvgr output file           */
        { efOUT, "-Spect", "intfspect", ffOPTWRMULT}, /* Fourier spectrum interfaces */
    };
#define NFILE asize(fnm)

    /*Filenames*/
    const char  *ndxfnm, *tpsfnm, *trxfnm;
    char       **spectra, **intfn, **raw;
    int          nfspect, nfxpm, nfraw;
    output_env_t oenv;

    parse_common_args(&argc, argv, PCA_CAN_VIEW | PCA_CAN_TIME | PCA_BE_NICE,
                      NFILE, fnm, asize(pa), pa, asize(desc), desc, 0, NULL, &oenv);
    bFourier = opt2bSet("-Spect", NFILE, fnm);
    bRawOut  = opt2bSet("-or", NFILE, fnm);

    if (binwidth < 0.0)
    {
        gmx_fatal(FARGS, "Can not have binwidth < 0");
    }

    ndxfnm = ftp2fn(efNDX, NFILE, fnm);
    tpsfnm = ftp2fn(efTPX, NFILE, fnm);
    trxfnm = ftp2fn(efTRX, NFILE, fnm);

    /* Calculate axis */
    if (strcmp(normal_axis[0], "x") == 0)
    {
        axis = XX;
    }
    else if (strcmp(normal_axis[0], "y") == 0)
    {
        axis = YY;
    }
    else if (strcmp(normal_axis[0], "z") == 0)
    {
        axis = ZZ;
    }
    else
    {
        gmx_fatal(FARGS, "Invalid axis, use x, y or z");
    }

    switch (axis)
    {
        case 0:
            fprintf(stderr, "Taking x axis as normal to the membrane\n");
            break;
        case 1:
            fprintf(stderr, "Taking y axis as normal to the membrane\n");
            break;
        case 2:
            fprintf(stderr, "Taking z axis as normal to the membrane\n");
            break;
    }

    /* tetraheder order parameter */
    /* If either of the options is set we compute both */
    nfxpm = opt2fns(&intfn, "-o", NFILE, fnm);
    if (nfxpm != 2)
    {
        gmx_fatal(FARGS, "No or not correct number (2) of output-files: %d", nfxpm);
    }
    calc_tetra_order_interface(ndxfnm, tpsfnm, trxfnm, binwidth, nsttblock, &frames, &xslices, &yslices, sg1, sg2, &intfpos, oenv);
    writesurftoxpms(intfpos, frames, xslices, yslices, binwidth, intfn, nlevels);

    if (bFourier)
    {
        nfspect = opt2fns(&spectra, "-Spect", NFILE, fnm);
        if (nfspect != 2)
        {
            gmx_fatal(FARGS, "No or not correct number (2) of output-files: %d", nfspect);
        }
        powerspectavg(intfpos, frames, xslices, yslices, spectra);
    }

    if (bRawOut)
    {
        nfraw = opt2fns(&raw, "-or", NFILE, fnm);
        if (nfraw != 2)
        {
            gmx_fatal(FARGS, "No or not correct number (2) of output-files: %d", nfraw);
        }
        writeraw(intfpos, frames, xslices, yslices, raw);
    }



    thanx(stderr);

    return 0;
}
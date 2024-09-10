long AOloopControl_PredictiveControl_builPFloop_WatchInput(long loop, long PFblock, long PFblockStart, long PFblockEnd)
{
    long IDinb0;
    long IDinb1;
    char imnameb0[500];
    char imnameb1[500];
    long cnt0, cnt1;
    long cnt0_old, cnt1_old;
    long IDinb;

    long twaitus = 100000; // 0.1 sec


    long PFblockSize;
    long PFblockOrder;
    float PFblockLag;
    float PFblockdgain;
    FILE *fp;
    char fname[500];
    int ret;

    int Tupdate = 0;
    time_t t;
    struct tm *uttime;
    struct timespec timenow;
    long xsize, ysize, zsize, xysize;
    int cube;

    long IDout;
    uint32_t *imsizearray;
    uint8_t atype;
    char imnameout[500];
    long ii, kk;
    long ave;

    char inmaskname[200];
    char inmaskfname[200];
    char outmaskfname[200];
    long IDinmask;


    PFblockSize = PFblockEnd - PFblockStart;


    if(sprintf(imnameb0, "aol%ld_modeval_ol_logbuff0", loop) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    if(sprintf(imnameb1, "aol%ld_modeval_ol_logbuff1", loop) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    IDinb0 = read_sharedmem_image(imnameb0);
    IDinb1 = read_sharedmem_image(imnameb1);

    cnt0_old = data.image[IDinb0].md[0].cnt0;
    cnt1_old = data.image[IDinb1].md[0].cnt0;

    xsize = data.image[IDinb0].md[0].size[0];
    ysize = data.image[IDinb0].md[0].size[1];
    xysize = xsize*ysize;
    zsize = data.image[IDinb0].md[0].size[2];
    atype = data.image[IDinb0].md[0].atype;


    list_image_ID();


    if(system("mkdir -p PredictiveControl") != 0)
        printERROR(__FILE__, __func__, __LINE__, "system() returns non-zero value");

    if(sprintf(inmaskname, "inmaskPFb%ld", PFblock) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    IDinmask = create_2Dimage_ID(inmaskname, xysize, 1);
    for(ii=0; ii<xysize; ii++)
        data.image[IDinmask].array.F[ii] = 0.0;
    for(ii=PFblockStart; ii<PFblockEnd; ii++)
        data.image[IDinmask].array.F[ii] = 1.0;

    if(sprintf(inmaskfname, "!./PredictiveControl/inmaskPF%ld.fits", PFblock) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    save_fits(inmaskname, inmaskfname);
    if(sprintf(outmaskfname, "!./PredictiveControl/outmaskPF%ld.fits", PFblock) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    save_fits(inmaskname, outmaskfname);





    printf("Create aol%ld_modevalol_PFb%ld  : %ld x 1 x %ld\n", loop, PFblock, PFblockSize, zsize);
    fflush(stdout);
    imsizearray = (uint32_t*) malloc(sizeof(uint32_t)*3);
    imsizearray[0] = PFblockSize;
    imsizearray[1] = 1;
    imsizearray[2] = zsize;

    if(sprintf(imnameout, "aol%ld_modevalol_PFb%ld", loop, PFblock) < 1)
        printERROR(__FILE__, __func__, __LINE__, "sprintf wrote <1 char");

    IDout = create_image_ID(imnameout, 3, imsizearray, atype, 1, 1);
    free(imsizearray);
    COREMOD_MEMORY_image_set_semflush(imnameout, -1);
    printf("Done\n");
    fflush(stdout);


    for(;;)
    {
        cnt0 = data.image[IDinb0].md[0].cnt0;
        cnt1 = data.image[IDinb1].md[0].cnt0;

        if(cnt0!=cnt0_old)
        {
            cube = 0;
            cnt0_old = cnt0;
            IDinb = IDinb0;
            Tupdate = 1;
        }

        if(cnt1!=cnt1_old)
        {
            cube = 1;
            cnt1_old = cnt1;
            IDinb = IDinb1;
            Tupdate = 1;
        }

        if(Tupdate == 1)
        {
            t = time(NULL);
            uttime = gmtime(&t);
            clock_gettime(CLOCK_REALTIME, &timenow);
            printf("%02d:%02d:%02ld.%09ld  NEW TELEMETRY BUFFER AVAILABLE [%d]\n", uttime->tm_hour, uttime->tm_min, timenow.tv_sec % 60, timenow.tv_nsec, cube);


            data.image[IDout].md[0].write = 1;

            for(kk=0; kk<zsize; kk++)
                for(ii=0; ii<PFblockSize; ii++)
                    data.image[IDout].array.F[kk*PFblockSize + ii] = data.image[IDinb].array.F[kk*xysize + (ii+PFblockStart)];

            for(ii=0; ii<PFblockSize; ii++)
            {
                ave = 0.0;
                for(kk=0; kk<zsize; kk++)
                    ave += data.image[IDout].array.F[kk*PFblockSize + ii];

                ave /= zsize;
                for(kk=0; kk<zsize; kk++)
                    data.image[IDout].array.F[kk*PFblockSize + ii] -= ave;
            }


            COREMOD_MEMORY_image_set_sempost_byID(IDout, -1);
            data.image[IDout].md[0].cnt0++;
            data.image[IDout].md[0].write = 0;

            Tupdate = 0;
        }


        usleep(twaitus);
    }

    return (IDout);
}
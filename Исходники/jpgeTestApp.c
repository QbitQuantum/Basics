/* Main Function acting as a client for Image Encode Call*/
XDAS_Int32 main(int argc, char *argv[])
{

    /* File I/O variables */
    FILE *fConfigFile, /**ftestFile, *finFile,*/ *fparamsFile;

#ifdef LINUX
    CMEM_AllocParams memParams;
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_NONCACHED;
    memParams.alignment=256;
#endif

    char* colorf[]={"YUV422P", "YUV420P", "YUV422P", "YUV422IL", "YUV422IL", "YUV444", "YUV411", "GRAY", "RGB", "YUV420_LINE"};
#ifdef LINUX
    XDAS_Int8 *fname = "../TestVecs/Config/Testvecs.cfg";
#else
    XDAS_Int8 *fname = "..\\..\\Test\\TestVecs\\Config\\Testvecs_ccs.cfg";
#endif
    Int32 lTemp,countConfigSet;
    Int32 retVal;
    Uint32 numAU, totalAU,repeat;
    Uint32 bytesGenerated;
    Uint16 mbSizeX, mbSizeY,mbY;

    char *RefBuffPtr;
    FILE *fp_out;
    FILE *fp_in;
    int processTime = 0, processTimeTotal = 0,algActivateTime =0, algDeactivateTime =0,copctime=0;
    int val,queue_word,queue_num=0,i,k;
    char baseParams[STRING_SIZE];
    int baseParamsOnly;
    int Offset;
    int num_markers;
    IIMGENC1_Fxns            *iimgEncfxns;
    IIMGENC1_Status  imgencStatus;
    IIMGENC1_InArgs imgencInArgs;
    IIMGENC1_OutArgs imgencOutArgs;
    IJPEGENC_Status          status;
    IJPEGENC_InArgs          inArgs;
    IJPEGENC_OutArgs         outArgs;
    unsigned int lTemp1;

    /*Algorithm specific handle */
    IALG_Handle handle;

    /* Input/Output Buffer Descriptor variables */
    XDM1_BufDesc inputBufDesc, outputBufDesc;


#ifdef ENABLE_RMAN // IRES/RMAN Related declarations
    // temp_trace_init();
    IRES_Status iresStatus;
    Int size =0;
    Int scratchId =0;
    Bool result = TRUE;
    IRES_Fxns *resFxns = &JPEGENC_TI_IRES;
    IRESMAN_Edma3ChanParams configParams;
    IRESMAN_VicpParams iresmanConfigParams;
    IRESMAN_AddrSpaceParams addrspaceConfigParams;

    iresStatus = RMAN_init();
    if (IRES_OK != iresStatus) {
        printf("RMAN initialization Failed \n");
        return -1;
    }
    printf("RMAN initialization done \n");

#ifndef LINUX
        /* Call the functions to enable ARM926 FIQ and do some basic
         * setup to AINTC to accept KLD INTC (arm968) interupt in 
         * FIQ pin of Arm926  
         */
        ARM926_enable_FIQ();  /* SWI call to enable interrupts */
        ARM926_INTC_init();  /* Init AINTC */
#endif

    /*
     * Supply initialization information for the RESMAN while registering
     */
    size = sizeof(IRESMAN_VicpParams);

    iresmanConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    iresmanConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    iresmanConfigParams.baseConfig.size = size;

    /* Register the VICP protocol/resource manager with the
    *      * generic resource manager */

    iresStatus = RMAN_register(&IRESMAN_VICP2, (IRESMAN_Params *)&iresmanConfigParams);

    if (IRES_OK != iresStatus) {
        printf("VICP Protocol Registration Failed \n");
        return -1;
    }
    printf("VICP Protocol Registration Success \n");
    /*
     *      * Supply initialization information for the EDMA3 RESMAN while registering
     *           */
    size = sizeof(IRESMAN_Edma3ChanParams);

    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = size;

    iresStatus = RMAN_register(&IRESMAN_EDMA3CHAN, (IRESMAN_Params *)&configParams);

    if (IRES_OK != iresStatus) {
        printf("EDMA3 Protocol Registration Failed \n");
        return -1;
    }
    printf("EDMA3 Protocol Registration Success \n");

    /** Supply initialization information for the ADDRSPACE RESMAN while registering
    	* */
#if 1
    size = sizeof(IRESMAN_AddrSpaceParams);
    addrspaceConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    addrspaceConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    addrspaceConfigParams.baseConfig.size = size;

    iresStatus = RMAN_register(&IRESMAN_ADDRSPACE, (IRESMAN_Params *)&addrspaceConfigParams);

    if (IRES_OK != iresStatus) {
        printf("ADDRSPACE Protocol Registration Failed \n");
        return -1;
    }
#ifdef _DBG_MSG
    printf("ADDRSPACE Protocol Registration Success \n");
#endif
#endif


#endif //IRES/RMAN related code ends here  


#ifdef LINUX
    CMEM_init();

    ExternalGlobalMemPool = ExternalGlobalMemPoolBase = CMEM_alloc(EXTERNAL_DATA_MEM_SIZE,&memParams);
#ifdef ENABLE_RING_BUF_USAGE
    ringbuf = CMEM_alloc(RINGBUFSIZE, &memParams);
#endif
    OrgPictureY_0=CMEM_alloc( (LUMABUF_SIZE*2+ORGBUF_OFFSET), &memParams);
    OrgPictureCb_0=CMEM_alloc((CHROMABUF_SIZE+ORGBUF_OFFSET), &memParams);
    OrgPictureCr_0=CMEM_alloc((CHROMABUF_SIZE+ORGBUF_OFFSET), &memParams);
    media=CMEM_alloc((ENCODED_DATA_BUFFER_SIZE), &memParams);

//#ifdef LINUX
    //      DM350MM_init();
//#endif

    if (argc==2)
    {
        strncpy(baseParams,argv[1],256);
        if (!strcmp(baseParams,"-ext"))
        {
            printf("\n----- Running in extended parameter mode -----\n");
            baseParamsOnly=0;

        }
        else
        {
            printf("Argument  -ext needed to run in  extended param mode\n");
            exit(0);
        }
    }

    else
    {
        printf("\n----- Running in base parameter mode -----\n");
        baseParamsOnly=1;
    }


#else
    baseParamsOnly=0;
#endif


    //memset(ringbuf,0xaa,RINGBUFSIZE );
    memset(media, 0xaa, ENCODED_DATA_BUFFER_SIZE);
    memset(ExternalGlobalMemPool, 0xaa,EXTERNAL_DATA_MEM_SIZE );
    memset(OrgPictureY_0, 0xaa, (LUMABUF_SIZE*2+ORGBUF_OFFSET));
    memset(OrgPictureCb_0, 0xaa, (CHROMABUF_SIZE+ORGBUF_OFFSET));
    memset(OrgPictureCr_0, 0xaa, (CHROMABUF_SIZE+ORGBUF_OFFSET));

    OrgPictureY  = &OrgPictureY_0[ORGBUF_OFFSET];
    OrgPictureCb = &OrgPictureCb_0[ORGBUF_OFFSET];
    OrgPictureCr = &OrgPictureCr_0[ORGBUF_OFFSET];


    /* Open Test Config File   */
    fConfigFile = fopen(fname, "r");

    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s\n", fname);
        return XDM_EFAIL;
    }


    countConfigSet = 1;         /* Reset countConfigSet value to 1 */

    /* Read the Config File until it reaches the end of file                    */
    while (!feof(fConfigFile))
    {
        /* Read Compliance Checking parameter */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%d\n", &testCompliance);
            printf("\nTestcompliance = %d\n",testCompliance);
        } else {
            break;
        }
        /* Read Parameters file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", paramsFile);
            printf("\nParam file = %s\n",paramsFile);
        }
        else
        {
            break;
        }
        /* Read Input file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", inFile);
            printf("\nInput file = %s\n",inFile);
        }
        else
        {
            break;
        }

        /* Read Output/Reference file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", testFile);
            printf("\nOutput file = %s\n",testFile);
        }
        else
        {
            break;
        }

        printf("\n*******************************************");
        printf("\nRead Configuration Set %d", countConfigSet);
        printf("\n*******************************************");
        countConfigSet++;



        fp_out=fopen(testFile,"wb");
        fp_in = fopen(inFile,"rb");


        if ((fp_in == NULL) || (fp_out == NULL))
        {
            printf("'Input/out file cannot be opened\n");
            exit(0);
        }

        /** Set initialization parameters
         * Parameters in structure params are default image encode parameters required by XDM
         * Paraemters in extn_params are parameters specific to jpeg encoder,
         *
         */

        /* Open Parameters file */
        fparamsFile = fopen(paramsFile, "rb");
        //fparamsFile = fopen("Testparams.cfg", "rb");
        if (!fparamsFile)
        {
            printf("\nCouldn't open Parameters file...   %s\n ",
                   paramsFile);
            printf("Exiting for this configuration...\n");
            continue;
        }

        printf("\nParameter file read starts...\n");
        if (readparamfile(fparamsFile,baseParamsOnly) < 0)
        {
            printf("\nSyntax Error in %s\n ", paramsFile);
            printf("Exiting for this configuration...\n");
            continue;
        }

        /* Close Parameters File */
        fclose(fparamsFile);
        if (testCompliance)
        {
            printf("\nRunning in Compliance Mode");
        }
        else
        {
            printf("\nRunning in Output Dump Mode");
        }


        /** Call algorithm creation function
          * See file alg_create.
          * memory allocation functions are called inside alg_malloc file.
          * Modify _ALG_allocMemory in alg_malloc.c to suit the application need (static allocation vs dynamic through malloc())
          */

        if (baseParamsOnly==0)
        {
#ifdef ENABLE_RING_BUF_USAGE
            extn_params.halfBufCB =(XDAS_Void (*)(Uint32, XDAS_Void*))JPEGENC_TI_DM350_HalfBufCB;
            extn_params.halfBufCBarg= (void*)&ring2media;

#else
            extn_params.halfBufCB = (XDAS_Void (*))NULL;
#endif


            extn_params.imgencParams = params;
            extn_params.imgencParams.size = sizeof(IJPEGENC_Params);
        }
        else
        {
            params.size = sizeof(IIMGENC1_Params);
            dynamicParams.size =sizeof(IIMGENC1_DynamicParams);
        }
        if (baseParamsOnly==0)
        {
            if ((handle =  (IALG_Handle)ALG_create (
                               (IALG_Fxns *) &JPEGENC_TI_IJPEGENC,
                               (IALG_Handle) NULL,
                               (IALG_Params *)&extn_params)) == NULL)
            {
                printf("\nFailed to Create Instance... Exiting for this configuration..");
                exit(0);
            }

            printf("\nAlgorithm Instance Creation Done...\n");
        }
        else
        {
            if ((handle =  (IALG_Handle)ALG_create (
                               (IALG_Fxns *) &JPEGENC_TI_IJPEGENC,
                               (IALG_Handle) NULL,
                               (IALG_Params *)&params)) == NULL)
            {
                printf("\nFailed to Create Instance... Exiting for this configuration..");
                exit(0);
            }

            printf("\nAlgorithm Instance Creation Done...\n");
        }



#ifdef ENABLE_RMAN // IRES/RMAN Related code

        /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
        iresStatus = RMAN_assignResources((IALG_Handle)handle, resFxns,scratchId);
        if (IRES_OK != iresStatus) {
            printf("Assign Resource Failed \n");
            result = FALSE;
        }

#endif //IRES/RMAN code ends here.

        /** Set up dynamic parameters (can be changed before each call to jpeg processing)
          * Parameters in structure dynamicParams are default image encode parameters required by XDM
          */
        if (baseParamsOnly==0)
        {
            extn_dynamicParams.imgencDynamicParams = dynamicParams;
            extn_dynamicParams.imgencDynamicParams.size  = sizeof(IJPEGENC_DynamicParams);
            extn_dynamicParams.disableEOI = 0;
            iimgEncfxns = (IIMGENC1_Fxns *)handle->fxns ;
            status.imgencStatus.size= sizeof(IJPEGENC_Status);
        }
        else
        {

            dynamicParams.size           = sizeof(IIMGENC1_DynamicParams);
            iimgEncfxns = (IIMGENC1_Fxns *)handle->fxns ;
            imgencStatus.size= sizeof(IIMGENC1_Status);

        }
        /** Request input and output buffer characteristics by calling control() function
         *  with command XDM_GETBUFINFO
         */


        // Call control function to setup dynamic params
        if (baseParamsOnly==0)
        {
            retVal=iimgEncfxns->control((IIMGENC1_Handle)handle,/*IJPEGENC_SETDEFAULT*/XDM_SETPARAMS,
                                        (IIMGENC1_DynamicParams *)&extn_dynamicParams, (IIMGENC1_Status *)&status);

            if (retVal== XDM_EFAIL) {
                printf("\n Error control SetParams  command1\n");
                exit(0);
            }

            retVal= iimgEncfxns->control((IIMGENC1_Handle)handle,
                                         XDM_GETBUFINFO,
                                         (IIMGENC1_DynamicParams *) &extn_dynamicParams,
                                         (IIMGENC1_Status *)&status);
	    if (retVal== XDM_EFAIL) {
		printf("\n Error control Getbuffinfo  command1\n");
		exit(0);
	     }


            inputBufDesc.numBufs = status.imgencStatus.bufInfo.minNumInBufs;
            Offset = 0;

            for (i=0;i<inputBufDesc.numBufs;i++)
            {
                inputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)inputData +
                                            Offset);
                Offset +=  status.imgencStatus.bufInfo.minInBufSize[i];
                inputBufDesc.descs[i].bufSize = status.imgencStatus.bufInfo.minInBufSize[i];
            }

            outputBufDesc.numBufs = status.imgencStatus.bufInfo.minNumOutBufs;
            Offset = 0;

            for (i=0;i<outputBufDesc.numBufs;i++)
            {
                outputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)outputData +
                                             Offset);
                Offset +=  status.imgencStatus.bufInfo.minOutBufSize[i];
                outputBufDesc.descs[i].bufSize = status.imgencStatus.bufInfo.minOutBufSize[i];

            }


            if (retVal== XDM_EFAIL) {
                printf("\n Error control GetInfo command\n");
                exit(0);
            }

        }
        else
        {
            retVal=iimgEncfxns->control((IIMGENC1_Handle)handle, XDM_SETPARAMS,
                                        (IIMGENC1_DynamicParams *)&dynamicParams, (IIMGENC1_Status *)&imgencStatus);

            if (retVal== XDM_EFAIL) {
                printf("\n Error control SetParams  command1\n");
                exit(0);
            }

            retVal= iimgEncfxns->control((IIMGENC1_Handle)handle,
                                         XDM_GETBUFINFO,
                                         (IIMGENC1_DynamicParams *)&dynamicParams,
                                         (IIMGENC1_Status *)&imgencStatus);
             if (retVal== XDM_EFAIL) 
	     {
		 printf("\n Error control GetBuffInfo  command1\n");
	         exit(0);
	      }

            inputBufDesc.numBufs = imgencStatus.bufInfo.minNumInBufs;
            Offset = 0;

            for (i=0;i<inputBufDesc.numBufs;i++)
            {
                inputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)inputData +
                                            Offset);
                Offset +=  imgencStatus.bufInfo.minInBufSize[i];
                inputBufDesc.descs[i].bufSize = imgencStatus.bufInfo.minInBufSize[i];
            }

            outputBufDesc.numBufs = imgencStatus.bufInfo.minNumOutBufs;
            Offset = 0;

            for (i=0;i<outputBufDesc.numBufs;i++)
            {
                outputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)outputData +
                                             Offset);
                Offset +=  imgencStatus.bufInfo.minOutBufSize[i];
                outputBufDesc.descs[i].bufSize = imgencStatus.bufInfo.minOutBufSize[i];
            }

            if (retVal== XDM_EFAIL) {
                printf("\n Error control GetInfo command\n");
                exit(0);
            }




        }
        if (baseParamsOnly==0)
        {
            /** Read input file.
               */
            printf("Number of Input bufs =%d\n",status.imgencStatus.bufInfo.minNumInBufs );
            if (status.imgencStatus.bufInfo.minNumInBufs == 3)
            {
                memset(OrgPictureY,0,(status.imgencStatus.bufInfo.minInBufSize[0]));
                memset(OrgPictureCb,0,(status.imgencStatus.bufInfo.minInBufSize[1]));
                memset(OrgPictureCr,0,(status.imgencStatus.bufInfo.minInBufSize[2]));
                printf("Input file read starts\n" );

                lTemp = fread(OrgPictureY,1,(status.imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);


                lTemp = fread(OrgPictureCb,1,((status.imgencStatus.bufInfo.minInBufSize[1])),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)/4),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);
                lTemp = fread(OrgPictureCr,1,((status.imgencStatus.bufInfo.minInBufSize[2])),fp_in);
                printf("number of bytes read from input file = %d \n",lTemp);


            }
            else if (status.imgencStatus.bufInfo.minNumInBufs == 1)
            {
                printf("status.imgencStatus.bufInfo.minInBufSize[0]=%d\n",status.imgencStatus.bufInfo.minInBufSize[0]);
                memset(OrgPictureY,0,(status.imgencStatus.bufInfo.minInBufSize[0]));
                lTemp = fread(OrgPictureY,1,(status.imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                printf("number of bytes read from input file = %d \n",lTemp);
            }
            else if (status.imgencStatus.bufInfo.minNumInBufs == 2) /* 420 semi planar*/
            {
                printf("status.imgencStatus.bufInfo.minInBufSize[0]=%d\n",status.imgencStatus.bufInfo.minInBufSize[0]);
                memset(OrgPictureY,0,(status.imgencStatus.bufInfo.minInBufSize[0]));
                printf("status.imgencStatus.bufInfo.minInBufSize[1]=%d\n",status.imgencStatus.bufInfo.minInBufSize[1]);
                memset(OrgPictureCb,'-',(status.imgencStatus.bufInfo.minInBufSize[1]));
                memset(OrgPictureCr,'-',(status.imgencStatus.bufInfo.minInBufSize[1]));

                lTemp = fread(OrgPictureY,1,(status.imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);

                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    lTemp = fread(OrgPictureCr,1,(status.imgencStatus.bufInfo.minInBufSize[1])/2,fp_in);
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)/4),SEEK_CUR);

                    lTemp += fread((OrgPictureCr+(status.imgencStatus.bufInfo.minInBufSize[1])/2),1,(status.imgencStatus.bufInfo.minInBufSize[1])/2,fp_in);

                }
                else
                {
                    lTemp = fread(OrgPictureCr,1,(status.imgencStatus.bufInfo.minInBufSize[1]),fp_in);
                }

                printf("number of bytes read from input file = %d \n",lTemp);

                /* The input file is 420 planar, the following function converts the 420P to 420 semi planar
                   i.e CbCr will be interleaved. planar chrmoa data is read into OrgPictureCr buffer and
                   converted to interleaved. output is stored in OrgPictureCb buffer*/
                /*convert the 420 planar to 420 semi planar*/
                lTemp = Convert420Pto420Semi(OrgPictureCr,OrgPictureCb,status.imgencStatus.bufInfo.minInBufSize[1]);

            }
            else
            {
                printf("Unsupported number of input buffers \n");
            }
            fclose(fp_in);
        }
        else
        {
            /** Read input file.
               */
            printf("Number of Input bufs =%d\n",imgencStatus.bufInfo.minNumInBufs );
            if (imgencStatus.bufInfo.minNumInBufs == 3)
            {
                memset(OrgPictureY,0,(imgencStatus.bufInfo.minInBufSize[0]));
                memset(OrgPictureCb,0,(imgencStatus.bufInfo.minInBufSize[1]));
                memset(OrgPictureCr,0,(imgencStatus.bufInfo.minInBufSize[2]));
                printf("Input file read starts\n" );

                lTemp = fread(OrgPictureY,1,(imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);


                lTemp = fread(OrgPictureCb,1,((imgencStatus.bufInfo.minInBufSize[1])),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)/4),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);
                lTemp = fread(OrgPictureCr,1,((imgencStatus.bufInfo.minInBufSize[2])),fp_in);
                printf("number of bytes read from input file = %d \n",lTemp);


            }
            else if (imgencStatus.bufInfo.minNumInBufs == 1)
            {
                printf("imgencStatus.bufInfo.minInBufSize[0]=%d\n",imgencStatus.bufInfo.minInBufSize[0]);
                memset(OrgPictureY,0,(imgencStatus.bufInfo.minInBufSize[0]));
                lTemp = fread(OrgPictureY,1,(imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                printf("number of bytes read from input file = %d \n",lTemp);
            }
            else if (imgencStatus.bufInfo.minNumInBufs == 2) /* 420 semi planar*/
            {
                printf("imgencStatus.bufInfo.minInBufSize[0]=%d\n",imgencStatus.bufInfo.minInBufSize[0]);
                memset(OrgPictureY,0,(imgencStatus.bufInfo.minInBufSize[0]));
                printf("imgencStatus.bufInfo.minInBufSize[1]=%d\n",imgencStatus.bufInfo.minInBufSize[1]);
                memset(OrgPictureCb,'-',(imgencStatus.bufInfo.minInBufSize[1]));
                memset(OrgPictureCr,'-',(imgencStatus.bufInfo.minInBufSize[1]));

                lTemp = fread(OrgPictureY,1,(imgencStatus.bufInfo.minInBufSize[0]),fp_in);
                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)),SEEK_CUR);
                }
                printf("number of bytes read from input file = %d \n",lTemp);

                if (dynamicParams.inputWidth < dynamicParams.captureWidth) {
                    lTemp = fread(OrgPictureCr,1,(imgencStatus.bufInfo.minInBufSize[1])/2,fp_in);
                    fseek(fp_in,(dynamicParams.captureWidth*(params.maxHeight-dynamicParams.inputHeight)/4),SEEK_CUR);

                    lTemp += fread((OrgPictureCr+(imgencStatus.bufInfo.minInBufSize[1])/2),1,(imgencStatus.bufInfo.minInBufSize[1])/2,fp_in);

                }
                else
                {
                    lTemp = fread(OrgPictureCr,1,(imgencStatus.bufInfo.minInBufSize[1]),fp_in);
                }

                printf("number of bytes read from input file = %d \n",lTemp);

                /* The input file is 420 planar, the following function converts the 420P to 420 semi planar
                   i.e CbCr will be interleaved. planar chrmoa data is read into OrgPictureCr buffer and
                   converted to interleaved. output is stored in OrgPictureCb buffer*/
                /*convert the 420 planar to 420 semi planar*/
                lTemp = Convert420Pto420Semi(OrgPictureCr,OrgPictureCb,imgencStatus.bufInfo.minInBufSize[1]);

                //	printf("OrgPictureCb=%x\n",OrgPictureCb);


            }
            else
            {
                printf("Unsupported number of input buffers \n");
            }
            fclose(fp_in);

        }

        /*Fill up the buffers as required by algorithm                            */
        if (baseParamsOnly==0) {
            inputBufDesc.numBufs  = status.imgencStatus.bufInfo.minNumInBufs ;
        }
        else
        {
            inputBufDesc.numBufs  = imgencStatus.bufInfo.minNumInBufs ;
        }
        inputBufDesc.descs[0].buf= (XDAS_Int8 *)OrgPictureY;

        if (dynamicParams.inputChromaFormat== IJPEGENC_YUV_420LINE)
        {
            inputBufDesc.descs[1].buf= (XDAS_Int8 *)OrgPictureY + dynamicParams.inputWidth;
            inputBufDesc.descs[2].buf= inputBufDesc.descs[1].buf + dynamicParams.inputWidth*3/2;
        }
        else if (dynamicParams.inputChromaFormat!= XDM_YUV_422ILE)
        {
            if (dynamicParams.inputChromaFormat== XDM_YUV_420SP)
            {
                inputBufDesc.descs[1].buf= (XDAS_Int8 *)OrgPictureCb;
            }
            else
            {
                inputBufDesc.descs[1].buf= (XDAS_Int8 *)OrgPictureCb;
                inputBufDesc.descs[2].buf= (XDAS_Int8 *)OrgPictureCr;
            }

        }
        if (baseParamsOnly==0) {
            inputBufDesc.descs[0].bufSize = status.imgencStatus.bufInfo.minInBufSize[0]; // actually ignored by codec

            outputBufDesc.numBufs     = status.imgencStatus.bufInfo.minNumOutBufs ;
        }
        else
        {
            inputBufDesc.descs[0].bufSize = imgencStatus.bufInfo.minInBufSize[0]; // actually ignored by codec

            outputBufDesc.numBufs     = imgencStatus.bufInfo.minNumOutBufs ;
        }

        if (baseParamsOnly==0)
        {
#ifdef ENABLE_RING_BUF_USAGE

            outputBufDesc.descs[0].buf     = (XDAS_Int8 *)ringbuf;
            outputBufDesc.descs[0].bufSize =  RINGBUFSIZE; // actually ignored by codec
            ring2media.mediaPtr= media;
            ring2media.ringCurPtr= ringbuf;
            ring2media.ringStartPtr=ringbuf;
            ring2media.ringEndPtr= (Uint8*)((Uint32)ringbuf +RINGBUFSIZE) ;
            inArgs.ringBufStart= (XDAS_UInt8*)ringbuf;
            inArgs.ringBufSize= RINGBUFSIZE;
            printf("RINGBUFSIZE %x\n", RINGBUFSIZE);
#else
            outputBufDesc.descs[0].buf     = (XDAS_Int8 *)media;
            outputBufDesc.descs[0].bufSize =  ENCODED_DATA_BUFFER_SIZE; // actually ignored by codec
            ring2media.mediaPtr= media;
            ring2media.ringCurPtr= media;
            ring2media.ringStartPtr=media;
            ring2media.ringEndPtr= (Uint8*)((Uint32)media +ENCODED_DATA_BUFFER_SIZE) ;
            inArgs.ringBufStart= (XDAS_UInt8*)media;
            inArgs.ringBufSize= ENCODED_DATA_BUFFER_SIZE;
#endif


            inArgs.imgencInArgs.size =  sizeof(IJPEGENC_InArgs);
            outArgs.imgencOutArgs.size= sizeof(IJPEGENC_OutArgs);
        }
        else
        {
            outputBufDesc.descs[0].buf     = (XDAS_Int8 *)media;
            outputBufDesc.descs[0].bufSize =  ENCODED_DATA_BUFFER_SIZE; // actually ignored by codec
            imgencInArgs.size = sizeof(IIMGENC1_InArgs);
            imgencOutArgs.size= sizeof(IIMGENC1_OutArgs);

        }

#ifdef LINUX
        algActStart.tv_sec = 0;
        algActStart.tv_usec = 0;
        gettimeofday(&algActStart, 0);
#endif

        handle->fxns->algActivate(handle);

#ifdef LINUX
        processStart.tv_sec = 0;
        processStart.tv_usec = 0;
        gettimeofday(&processStart, 0);
#endif



        if (baseParamsOnly==0)
        {
            inArgs.insertCommentMarker = 0;
            inArgs.appDataType =0;
            inArgs.commentSegLen = 0;

            retVal = iimgEncfxns->process((IIMGENC1_Handle)handle,
                                          (XDM1_BufDesc *)&inputBufDesc,
                                          (XDM1_BufDesc *)&outputBufDesc,
                                          (IIMGENC1_InArgs *)&inArgs,
                                          (IIMGENC1_OutArgs *)&outArgs);

            bytesGenerated= outArgs.imgencOutArgs.bytesGenerated;
        }
        else
        {
            retVal = iimgEncfxns->process((IIMGENC1_Handle)handle,
                                          (XDM1_BufDesc *)&inputBufDesc,
                                          (XDM1_BufDesc *)&outputBufDesc,
                                          (IIMGENC1_InArgs *)&imgencInArgs,
                                          (IIMGENC1_OutArgs *)&imgencOutArgs);
            bytesGenerated= imgencOutArgs.bytesGenerated;
        }

#ifdef SLICE_MODE_TEST
        /* SLICE_MODE_TEST*/
        // Call get status to get number of total AU
        if (baseParamsOnly==0)
        {
            
		
	    retVal=iimgEncfxns->control((IIMGENC1_Handle)handle, IJPEGENC_GETSTATUS,
                                        (IIMGENC1_DynamicParams *)&extn_dynamicParams, (IIMGENC1_Status *)&status);
	    
	    if (retVal== XDM_EFAIL) {
                printf("\n Error control in slice mode get status command\n");
                exit(0);
            }
            totalAU= status.imgencStatus.totalAU;

	    printf("totalAU = %d\n",totalAU);
            extn_dynamicParams.imgencDynamicParams.numAU= 50/*totalAU/5*/;
	    
            // Call control function to setup dynamic params
            retVal=iimgEncfxns->control((IIMGENC1_Handle)handle, XDM_SETPARAMS,
                                        (IIMGENC1_DynamicParams *)&extn_dynamicParams, (IIMGENC1_Status *)&status);
            numAU = status.numAU;
	    printf("numAU = %d\n",numAU);

	    if (retVal== XDM_EFAIL) {
                printf("\n Error control in slice mode SetParams command\n");
                exit(0);
            }          // Get real numAU computed by codec

            // In case of 270 rotation, must point to right most slice of the image
            
	    if (extn_dynamicParams.rotation== 90)
            {
                if (dynamicParams.inputChromaFormat==XDM_YUV_420SP)
                {
                    Uint16 sliceWidth= (numAU*16/dynamicParams.inputHeight)*(8<<(params.forceChromaFormat==XDM_YUV_420P));
                    inputBufDesc.descs[0].buf+= (dynamicParams.inputWidth - sliceWidth);
                    inputBufDesc.descs[1].buf+= (dynamicParams.inputWidth - sliceWidth);

                    //	inputBufDesc.descs[2].buf+= (dynamicParams.inputWidth - sliceWidth);//dynamicParams.inputWidth/2 - sliceWidth/2;
                }
                else
                {
                    Uint16 sliceWidth= (numAU*16/dynamicParams.inputHeight)*(8<<(params.forceChromaFormat==XDM_YUV_420P));
                    inputBufDesc.descs[0].buf+= (dynamicParams.inputChromaFormat== XDM_YUV_422ILE ? 2 : 1)*(dynamicParams.inputWidth - sliceWidth);
                    inputBufDesc.descs[1].buf+= dynamicParams.inputWidth/2 - sliceWidth/2;
                    inputBufDesc.descs[2].buf+= dynamicParams.inputWidth/2 - sliceWidth/2;
                }


            }
            else if (extn_dynamicParams.rotation== 180)
            {
                Uint16 sliceHeight = (numAU*16/dynamicParams.inputWidth)*(8<<(params.forceChromaFormat==XDM_YUV_420P));
                if (dynamicParams.inputChromaFormat != XDM_YUV_420SP)
                {
                    inputBufDesc.descs[0].buf+= dynamicParams.captureWidth*(dynamicParams.inputChromaFormat== XDM_YUV_422ILE ? 2 : 1)*(dynamicParams.inputHeight - sliceHeight);
                    inputBufDesc.descs[1].buf+= dynamicParams.captureWidth*(dynamicParams.inputHeight - sliceHeight)>>(1 + (dynamicParams.inputChromaFormat== XDM_YUV_420P));
                    inputBufDesc.descs[2].buf+= dynamicParams.captureWidth*(dynamicParams.inputHeight - sliceHeight)>>(1 + (dynamicParams.inputChromaFormat== XDM_YUV_420P));
                }
                else
                {
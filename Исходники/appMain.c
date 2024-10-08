/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{

    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    Loader_Attrs            lAttrs      = Loader_Attrs_DEFAULT;
    SPHDEC1_Params          params      = Sdec1_Params_DEFAULT;
    SPHDEC1_DynamicParams   dynParams   = Sdec1_DynamicParams_DEFAULT;
    Time_Attrs              tAttrs      = Time_Attrs_DEFAULT;
    Sdec1_Handle            hSd1        = NULL;
    Loader_Handle           hLoader     = NULL;
    Engine_Handle           hEngine     = NULL;
    Time_Handle             hTime       = NULL;
    Buffer_Handle           hOutBuf     = NULL;
    Buffer_Handle           hInBuf      = NULL;
    FILE                   *outFile     = NULL;
    Int                     numFrame    = 0;
    UInt32                  time;
    Int                     ret         = Dmai_EOK;

    printf("Starting application...\n");

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();

    /* Open the output file */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbuffer, _IOFBF, sizeof(vbuffer)) != 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to setvbuf on file descriptor\n");
        goto cleanup;   
    }
   
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }
    
    params.compandingLaw = args->compandingLaw;

    /* Create the SPHDEC1 based speech decoder */
    hSd1 = Sdec1_create(hEngine, args->codecName, &params, &dynParams);

    if (hSd1 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    bAttrs.memParams.align = lAttrs.mParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */  
    if (args->cache) {
        bAttrs.memParams.flags = lAttrs.mParams.flags = Memory_CACHED;
    } 
    
    /* Ask the codec how much input data it needs */
    lAttrs.readSize = Sdec1_getInBufSize(hSd1);

    /* Make the total ring buffer larger */
    lAttrs.readBufSize = Dmai_roundUp(lAttrs.readSize * 10, BUFSIZEALIGN);

    /* Increase the stdio buffer size for loader for better RTDX performance */
    lAttrs.vBufSize = VBUFSIZE;

    /* Create the file loader */
    hLoader = Loader_create(args->inFile, &lAttrs);

    if (hLoader == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create loader\n");
        goto cleanup;
    }

    /* Create an output buffer for decoded data */
    hOutBuf = Buffer_create(
        Dmai_roundUp(Sdec1_getOutBufSize(hSd1), BUFSIZEALIGN), &bAttrs);

    if (hOutBuf == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create contiguous buffers\n");
        goto cleanup;
    }

    /* Prime the file loader */
    Loader_prime(hLoader, &hInBuf);

    while (numFrame++ < args->numFrames) {
        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to reset timer\n");
                goto cleanup;
            }
        }

        if (args->cache) {
            /*  
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we 
             *  must writeback the cache into physical memory.  Also, per DMA 
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf),Buffer_getSize(hInBuf));
    
            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf),Buffer_getSize(hOutBuf));
            
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Pre-process cache maintenance: %uus ", (Uns) time);
            }
        }
        
        /* Decode the speech buffer */
        if (Sdec1_process(hSd1, hInBuf, hOutBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to decode speech buffer\n");
            goto cleanup;
        }

         if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Decode: %uus ", (Uns) time);
        }
        
        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
    
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Post-process cache write back: %uus ", (Uns) time);
            }
        }
         
        /* Load a new frame from the file system */
        Loader_getFrame(hLoader, hInBuf);

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Loader: %uus\n", (Uns) time);
        }

        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (numFrame >= args->startFrame) {
                printf("Frame %d: ", numFrame);
                if (writeFrame(hOutBuf, outFile) < 0) {
                    ret = Dmai_EFAIL;
                    goto cleanup;
                }
            }
        }

        if (Buffer_getUserPtr(hInBuf) == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Loader returned null, clip finished\n");
            break;
        }

        if (args->benchmark) {
            if (Time_total(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer total\n");
                goto cleanup;
            }

            printf("Total: %uus\n", (unsigned int)time);
        }
    }

cleanup:
    /* Clean up the application */
    if (hLoader) {
        Loader_delete(hLoader);
    }

    if (hSd1) {
        Sdec1_delete(hSd1);
    }

    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (outFile) {
        fclose(outFile);
    }
    
    printf("End of application.\n");

    if (ret == Dmai_EFAIL)
        return 1;
    else
        return 0;
}
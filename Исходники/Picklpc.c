void __cdecl main(int argc, char **argv)
{
    RPC_STATUS status;

    unsigned char * pbPicklingBuffer = NULL;

    char * pszStyle      = NULL;
    char * pszFileName   = "pickle.dat";
    int i;
    int fEncode = 1;
    int fFixedStyle = 1;

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'd':
                fEncode = 0;
                break;
            case 'e':
                fEncode = 1;
                break;
            case 'i':
                fFixedStyle = 0;
                break;
            case 'f':
                pszFileName = argv[i] + 2;
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    /* Fixed buffer style: the buffer should be big enough.  */
    /* Please note that the buffer has to be aligned at 8.   */

    pbPicklingBuffer = (unsigned char *)
            midl_user_allocate( BUFSIZE * sizeof(unsigned char));

    if ( pbPicklingBuffer == NULL ) {
        printf_s("Cannot allocate the pickling buffer\n");
        exit(1);
        }
    else
        memset( pbPicklingBuffer, 0xdd, BUFSIZE );

    /*
        Set the pickling handle that will be used for data serialization.
        The global ImplicitPicHandle is used, but it has to be set up.
    */

    if ( fEncode ) {

        unsigned char * pszNameId;
        OBJECT1         Object1;
        OBJECT2   *     pObject2;
        unsigned long   ulEncodedSize = 0;

        printf_s("\nEncoding run: use -d for decoding\n\n");

        if ( fFixedStyle ) {

            printf_s("Creating a fixed buffer encoding handle\n");
            status = MesEncodeFixedBufferHandleCreate( pbPicklingBuffer,
                                                       BUFSIZE,
                                                       & ulEncodedSize,
                                                       & ImplicitPicHandle );
            printf_s("MesEncodeFixedBufferHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }
        else {

            pUserState->LastSize = 0;
            pUserState->pMemBuffer = (char *)pbPicklingBuffer;
            pUserState->pBufferStart = (char *)pbPicklingBuffer;

            printf_s("Creating an incremental encoding handle\n");
            status = MesEncodeIncrementalHandleCreate( pUserState,
                                                       PicAlloc,
                                                       PicWrite,
                                                       & ImplicitPicHandle );
            printf_s("MesEncodeIncrementalHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }

        /* Creating objects to manipulate */

        pszNameId = "Procedure pickling sample";

        for (i = 0; i < ARR_SIZE; i++)
            Object1.al[i] = 0x37370000 + i;
        Object1.s = 0x4646;

        pObject2 = midl_user_allocate( sizeof(OBJECT2) + ARR_SIZE*sizeof(short) );
        if (pObject2 == NULL ) {
            printf_s("Out of memory for Object2\n");
            exit(1);
        }

        pObject2->sSize = ARR_SIZE;
        for (i = 0; i < ARR_SIZE; i++)
            pObject2->as[i] = 0x7700 + i;

        DumpData( "Data to be encoded", pszNameId, &Object1, pObject2 );

        printf_s("\nEncoding all the arguments to the buffer\n\n");
        ProcPickle( pszNameId, & Object1, pObject2 );

        printf_s("Writing the data to the file: %s\n", pszFileName);
        WriteDataToFile( pszFileName,
                         pbPicklingBuffer,
                         fFixedStyle  ? ulEncodedSize
                                      : pUserState->LastSize);

        midl_user_free( pObject2 );
    }
    else {
        char            acNameBuffer[50];
        OBJECT1         Object1;
        OBJECT2   *     pObject2;

        printf_s("\nDecoding run: use -e for encoding\n\n");

        printf_s("Reading the data from the file: %s\n\n", pszFileName );
        ReadDataFromFile( pszFileName,
                          pbPicklingBuffer,
                          BUFSIZE );

        if ( fFixedStyle ) {

            printf_s("Creating a decoding handle\n");
            status = MesDecodeBufferHandleCreate( pbPicklingBuffer,
                                                  BUFSIZE,
                                                  & ImplicitPicHandle );
            printf_s("MesDecodeFixedBufferHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }
        else {

            pUserState->LastSize = 0;
            pUserState->pMemBuffer = (char *)pbPicklingBuffer;
            pUserState->pBufferStart = (char *)pbPicklingBuffer;

            printf_s("Creating an incremental decoding handle\n");
            status = MesDecodeIncrementalHandleCreate( pUserState,
                                                       PicRead,
                                                       & ImplicitPicHandle );
            printf_s("MesDecodeIncrementalHandleCreate returned 0x%x\n", status);
            if (status) {
                exit(status);
            }
        }


        /* Creating objects to manipulate */

        pObject2 = midl_user_allocate( sizeof(OBJECT2) + ARR_SIZE*sizeof(short));
        if (pObject2 == NULL ) {
            printf_s("Out of memory for Object2\n");
            exit(1);
        }

        printf_s("\nDecoding all the arguments from the buffer\n");
        ProcPickle( acNameBuffer, & Object1, pObject2 );

        DumpData( "Decoded data", acNameBuffer, &Object1, pObject2 );

        midl_user_free( pObject2 );
    }

    printf_s("\nData serialization done.\n");

    midl_user_free( pbPicklingBuffer );

    printf_s("\nFreeing the serialization handle.\n");
    status = MesHandleFree( ImplicitPicHandle );
    printf_s("MesHandleFree returned 0x%x\n", status);

    exit(0);

}  // end main()
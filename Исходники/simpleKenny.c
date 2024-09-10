int main(int argc, char* argv[])
{
    //--- File IO ----
    FILE* inp;
    FILE* outp;
    char inname[500];
    char outname[500];

    /* Runtime statistics */
    double        rate;
    double        rateRCU;
    unsigned long totalbits = 0;
    unsigned long totalBitsRCU = 0;
    unsigned long totalsmpls =0;

    WebRtc_Word32   bottleneck = 39;
    WebRtc_Word16   frameSize = 30;           /* ms */
    WebRtc_Word16   codingMode = 1;
    WebRtc_Word16   shortdata[FRAMESAMPLES_SWB_10ms];
    WebRtc_Word16   decoded[MAX_FRAMESAMPLES_SWB];
    //WebRtc_UWord16  streamdata[1000];
    WebRtc_Word16   speechType[1];
    WebRtc_Word16   payloadLimit;
    WebRtc_Word32   rateLimit;
    ISACStruct*   ISAC_main_inst;

    WebRtc_Word16   stream_len = 0;
    WebRtc_Word16   declen;
    WebRtc_Word16   err;
    WebRtc_Word16   cur_framesmpls;
    int           endfile;
#ifdef WIN32
    double        length_file;
    double        runtime;
    char          outDrive[10];
    char          outPath[500];
    char          outPrefix[500];
    char          outSuffix[500];
    char          bitrateFileName[500];
    FILE*         bitrateFile;
    double        starttime;
    double        rateLB = 0;
    double        rateUB = 0;
#endif
    FILE*         histFile;
    FILE*         averageFile;
    int           sampFreqKHz;
    int           samplesIn10Ms;
    WebRtc_Word16   maxStreamLen = 0;
    char          histFileName[500];
    char          averageFileName[500];
    unsigned int  hist[600];
    unsigned int  tmpSumStreamLen = 0;
    unsigned int  packetCntr = 0;
    unsigned int  lostPacketCntr = 0;
    WebRtc_UWord16  payload[600];
    WebRtc_UWord16  payloadRCU[600];
    WebRtc_UWord16  packetLossPercent = 0;
    WebRtc_Word16   rcuStreamLen = 0;
	int onlyEncode;
	int onlyDecode;


    BottleNeckModel packetData;
	packetData.arrival_time  = 0;
	packetData.sample_count  = 0;
	packetData.rtp_number    = 0;
    memset(hist, 0, sizeof(hist));

    /* handling wrong input arguments in the command line */
    if(argc < 5)
    {
		int size;
		WebRtcIsac_AssignSize(&size);

        printf("\n\nWrong number of arguments or flag values.\n\n");

        printf("Usage:\n\n");
        printf("%s infile outfile -bn bottelneck [options] \n\n", argv[0]);
        printf("with:\n");
        printf("-I................... indicates encoding in instantaneous mode.\n");
        printf("-bn bottleneck....... the value of the bottleneck in bit/sec, e.g. 39742,\n");
		printf("                      in instantaneous (channel-independent) mode.\n\n");
        printf("infile............... Normal speech input file\n\n");
        printf("outfile.............. Speech output file\n\n");
        printf("OPTIONS\n");
        printf("-------\n");
        printf("-fs sampFreq......... sampling frequency of codec 16 or 32 (default) kHz.\n");
        printf("-plim payloadLim..... payload limit in bytes,\n");
        printf("                      default is the maximum possible.\n");
        printf("-rlim rateLim........ rate limit in bits/sec, \n");
        printf("                      default is the maimum possible.\n");
        printf("-h file.............. record histogram and *append* to 'file'.\n");
        printf("-ave file............ record average rate of 3 sec intervales and *append* to 'file'.\n");
        printf("-ploss............... packet-loss percentage.\n");
		printf("-enc................. do only encoding and store the bit-stream\n");
		printf("-dec................. the input file is a bit-stream, decode it.\n");

        printf("\n");
        printf("Example usage:\n\n");
        printf("%s speechIn.pcm speechOut.pcm -B 40000 -fs 32 \n\n", argv[0]);

		printf("structure size %d bytes\n", size);

        exit(0);
    }



    /* Get Bottleneck value */
    bottleneck = readParamInt(argc, argv, "-bn", 50000);
    fprintf(stderr,"\nfixed bottleneck rate of %d bits/s\n\n", bottleneck);

    /* Get Input and Output files */
    sscanf(argv[1], "%s", inname);
    sscanf(argv[2], "%s", outname);
    codingMode = readSwitch(argc, argv, "-I");
    sampFreqKHz = (WebRtc_Word16)readParamInt(argc, argv, "-fs", 32);
    if(readParamString(argc, argv, "-h", histFileName, 500) > 0)
    {
        histFile = fopen(histFileName, "a");
        if(histFile == NULL)
        {
            printf("cannot open hist file %s", histFileName);
            exit(0);
        }
    }
    else
    {
        // NO recording of hitstogram
        histFile = NULL;
    }


    packetLossPercent = readParamInt(argc, argv, "-ploss", 0);

    if(readParamString(argc, argv, "-ave", averageFileName, 500) > 0)
    {
        averageFile = fopen(averageFileName, "a");
        if(averageFile == NULL)
        {
            printf("cannot open file to write rate %s", averageFileName);
            exit(0);
        }
    }
    else
    {
        averageFile = NULL;
    }

	onlyEncode = readSwitch(argc, argv, "-enc");
	onlyDecode = readSwitch(argc, argv, "-dec");


    switch(sampFreqKHz)
    {
    case 16:
        {
            samplesIn10Ms = 160;
            break;
        }
    case 32:
        {
            samplesIn10Ms = 320;
            break;
        }
    default:
        printf("A sampling frequency of %d kHz is not supported,\
valid values are 8 and 16.\n", sampFreqKHz);
        exit(-1);
    }
    payloadLimit = (WebRtc_Word16)readParamInt(argc, argv, "-plim", 400);
    rateLimit = readParamInt(argc, argv, "-rlim", 106800);

    if ((inp = fopen(inname,"rb")) == NULL) {
        printf("  iSAC: Cannot read file %s.\n", inname);
        exit(1);
    }
    if ((outp = fopen(outname,"wb")) == NULL) {
        printf("  iSAC: Cannot write file %s.\n", outname);
        exit(1);
    }

#ifdef WIN32
    _splitpath(outname, outDrive, outPath, outPrefix, outSuffix);
    _makepath(bitrateFileName, outDrive, outPath, "bitrate", ".txt");

    bitrateFile = fopen(bitrateFileName, "a");
    fprintf(bitrateFile, "%  %%s  \n", inname);
#endif

    printf("\n");
    printf("Input.................... %s\n", inname);
    printf("Output................... %s\n", outname);
    printf("Encoding Mode............ %s\n",
        (codingMode == 1)? "Channel-Independent":"Channel-Adaptive");
    printf("Bottleneck............... %d bits/sec\n", bottleneck);
    printf("Packet-loss Percentage... %d\n", packetLossPercent);
    printf("\n");

#ifdef WIN32
    starttime = clock()/(double)CLOCKS_PER_SEC; /* Runtime statistics */
#endif

    /* Initialize the ISAC and BN structs */
    err = WebRtcIsac_Create(&ISAC_main_inst);

    WebRtcIsac_SetEncSampRate(ISAC_main_inst, (sampFreqKHz == 16)? kIsacWideband: kIsacSuperWideband);
    WebRtcIsac_SetDecSampRate(ISAC_main_inst, (sampFreqKHz == 16)? kIsacWideband: kIsacSuperWideband);
    /* Error check */
    if (err < 0) {
        fprintf(stderr,"\n\n Error in create.\n\n");
        exit(EXIT_FAILURE);
    }

    framecnt = 0;
    endfile     = 0;

    /* Initialize encoder and decoder */
    if(WebRtcIsac_EncoderInit(ISAC_main_inst, codingMode) < 0)
    {
        printf("cannot initialize encoder\n");
        return -1;
    }
    if(WebRtcIsac_DecoderInit(ISAC_main_inst) < 0)
    {
        printf("cannot initialize decoder\n");
        return -1;
    }

    //{
    //    WebRtc_Word32 b1, b2;
    //    FILE* fileID = fopen("GetBNTest.txt", "w");
    //    b2 = 32100;
    //    while(b2 <= 52000)
    //    {
    //        WebRtcIsac_Control(ISAC_main_inst, b2, frameSize);
    //        WebRtcIsac_GetUplinkBw(ISAC_main_inst, &b1);
    //        fprintf(fileID, "%5d %5d\n", b2, b1);
    //        b2 += 10;
    //    }
    //}

    if(codingMode == 1)
    {
        if(WebRtcIsac_Control(ISAC_main_inst, bottleneck, frameSize) < 0)
        {
            printf("cannot set bottleneck\n");
            return -1;
        }
    }
    else
    {
        if(WebRtcIsac_ControlBwe(ISAC_main_inst, 15000, 30, 1) < 0)
        {
            printf("cannot configure BWE\n");
            return -1;
        }
    }

    if(WebRtcIsac_SetMaxPayloadSize(ISAC_main_inst, payloadLimit) < 0)
    {
        printf("cannot set maximum payload size %d.\n", payloadLimit);
        return -1;
    }

    if (rateLimit < 106800) {
        if(WebRtcIsac_SetMaxRate(ISAC_main_inst, rateLimit) < 0)
        {
            printf("cannot set the maximum rate %d.\n", rateLimit);
            return -1;
        }
    }

    //=====================================
//#ifdef HAVE_DEBUG_INFO
//    if(setupDebugStruct(&debugInfo) < 0)
//    {
//        exit(1);
//    }
//#endif

    while (endfile == 0)
    {
        fprintf(stderr,"  \rframe = %7li", framecnt);

        //============== Readind from the file and encoding =================
        cur_framesmpls = 0;
        stream_len = 0;


		if(onlyDecode)
		{
			WebRtc_UWord8 auxUW8;
                        size_t auxSizet;
			if(fread(&auxUW8, sizeof(WebRtc_UWord8), 1, inp) < 1)
			{
				break;
			}
			stream_len = ((WebRtc_UWord8)auxUW8) << 8;
			if(fread(&auxUW8, sizeof(WebRtc_UWord8), 1, inp) < 1)
			{
				break;
			}
			stream_len |= (WebRtc_UWord16)auxUW8;
                        auxSizet = (size_t)stream_len;
                        if(fread(payload, 1, auxSizet, inp) < auxSizet)
			{
				printf("last payload is corrupted\n");
				break;
			}
		}
		else
		{
			while(stream_len == 0)
			{
				// Read 10 ms speech block
				endfile = readframe(shortdata, inp, samplesIn10Ms);
				if(endfile)
				{
					break;
				}
				cur_framesmpls += samplesIn10Ms;

				//-------- iSAC encoding ---------
				stream_len = WebRtcIsac_Encode(ISAC_main_inst, shortdata,
					(WebRtc_Word16*)payload);

				if(stream_len < 0)
				{
					// exit if returned with error
					//errType=WebRtcIsac_GetErrorCode(ISAC_main_inst);
					fprintf(stderr,"\nError in encoder\n");
					getchar();
					exit(EXIT_FAILURE);
				}


			}
			//===================================================================
			if(endfile)
			{
				break;
			}

			rcuStreamLen = WebRtcIsac_GetRedPayload(ISAC_main_inst, (WebRtc_Word16*)payloadRCU);

			get_arrival_time(cur_framesmpls, stream_len, bottleneck, &packetData,
				sampFreqKHz * 1000, sampFreqKHz * 1000);
			if(WebRtcIsac_UpdateBwEstimate(ISAC_main_inst,
				payload,  stream_len, packetData.rtp_number,
				packetData.sample_count,
				packetData.arrival_time) < 0)
			{
				printf(" BWE Error at client\n");
				return -1;
			}
		}

        if(endfile)
        {
            break;
        }

        maxStreamLen = (stream_len > maxStreamLen)? stream_len:maxStreamLen;
        packetCntr++;

        hist[stream_len]++;
        if(averageFile != NULL)
        {
            tmpSumStreamLen += stream_len;
            if(packetCntr == 100)
            {
                // kbps
                fprintf(averageFile, "%8.3f ", (double)tmpSumStreamLen * 8.0 / (30.0 * packetCntr));
                packetCntr = 0;
                tmpSumStreamLen = 0;
            }
        }

		if(onlyEncode)
		{
                  WebRtc_UWord8 auxUW8;
                  auxUW8 = (WebRtc_UWord8)(((stream_len & 0x7F00) >> 8) & 0xFF);
                  if (fwrite(&auxUW8, sizeof(WebRtc_UWord8), 1, outp) != 1) {
                    return -1;
                  }

                  auxUW8 = (WebRtc_UWord8)(stream_len & 0xFF);
                  if (fwrite(&auxUW8, sizeof(WebRtc_UWord8), 1, outp) != 1) {
                    return -1;
                  }
                  if (fwrite(payload, 1, stream_len,
                             outp) != (size_t)stream_len) {
                    return -1;
                  }
		}
		else
		{

			//======================= iSAC decoding ===========================

			if((rand() % 100) < packetLossPercent)
			{
				declen = WebRtcIsac_DecodeRcu(ISAC_main_inst, payloadRCU,
					rcuStreamLen, decoded, speechType);
				lostPacketCntr++;
			}
			else
			{
				declen = WebRtcIsac_Decode(ISAC_main_inst, payload,
					stream_len, decoded, speechType);
			}
			if(declen <= 0)
			{
				//errType=WebRtcIsac_GetErrorCode(ISAC_main_inst);
				fprintf(stderr,"\nError in decoder.\n");
				getchar();
				exit(1);
			}

			// Write decoded speech frame to file
                        if (fwrite(decoded, sizeof(WebRtc_Word16),
                                   declen, outp) != (size_t)declen) {
                          return -1;
                        }
			cur_framesmpls = declen;
		}
        // Update Statistics
        framecnt++;
        totalsmpls += cur_framesmpls;
        if(stream_len > 0)
        {
            totalbits += 8 * stream_len;
        }
        if(rcuStreamLen > 0)
        {
            totalBitsRCU += 8 * rcuStreamLen;
        }
    }
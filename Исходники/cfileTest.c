int main(int argc, char **argv)
{
	int		arg;
	char		*argp;
	int		loop;
	unsigned char	*ptext;
	unsigned	ptextLen;
	unsigned char	passwd1[PASSWD_LENGTH];
	unsigned char	passwd2[PASSWD_LENGTH];
	int		encrType;
	int		doEnc64;
	feePubKey	myPrivKey;
	feePubKey	theirPrivKey;
	feePubKey	myPubKey;
	feePubKey	theirPubKey;
	unsigned 	maxSize;
	
	/*
	 * User-spec'd params
	 */
	unsigned	loops = LOOPS_DEF;
	BOOL		seedSpec = NO;
	unsigned	seed;
	BOOL		quiet = NO;
	BOOL		verbose = NO;
	unsigned	minExp = MIN_EXP;
	unsigned	maxExp = MAX_EXP;
	BOOL		incrOffset = NO;
	unsigned	depth = DEPTH_DEFAULT;
	unsigned	minOffset = MIN_OFFSET;
	
	#if	macintosh
	argc = ccommand(&argv);
	#endif

	for(arg=1; arg<argc; arg++) {
		argp = argv[arg];
		switch(argp[0]) {
		    case 'l':
			loops = atoi(&argp[2]);
			break;
		    case 'n':
			minExp = atoi(&argp[2]);
			break;
		    case 'D':
			depth = atoi(&argp[2]);
			break;
		    case 'N':
			minOffset = atoi(&argp[2]);
			if(minOffset > MAX_OFFSET) {
				minOffset = MIN_OFFSET;
			}
			sizeOffset = minOffset;
			break;
		    case 'x':
			maxExp = atoi(&argp[2]);
			if(maxExp > MAX_EXP) {
				usage(argv);
			}
			break;
		    case 's':
			seed = atoi(&argp[2]);
			seedSpec = YES;
			break;
		    case 'I':
		    	incrOffset = YES;
			break;
		    case 'q':
		    	quiet = YES;
			break;
		    case 'v':
		    	verbose = YES;
			break;
		    case 'h':
		    default:
			usage(argv);
		}
	}
	
	if(seedSpec == NO) {
		time((unsigned long *)(&seed));
	}
	SRAND(seed);
	maxSize = dataSizeFromExp(maxExp) + MAX_OFFSET + 8;
	dataPool = fmalloc(maxSize);
	
	printf("Starting cfileTest: loops %d seed %d depth %d\n",
		loops, seed, depth);

	for(loop=1; ; loop++) {
	
	    ptext = genData(minExp, maxExp, DT_Random, incrOffset, 
		    minOffset, &ptextLen);
	    if(!quiet) {
		    printf("..loop %d plaintext size %d\n", loop, ptextLen);
	    }
	    
	    /*
	     * Generate a whole bunch of keys
	     */
	    genPasswd(passwd1, PASSWD_LENGTH, NO);	// not ascii!
	    genPasswd(passwd2, PASSWD_LENGTH, NO);
	    myPrivKey 	 = genPrivKey(passwd1, PASSWD_LENGTH, depth);
	    theirPrivKey = genPrivKey(passwd2, PASSWD_LENGTH, depth);
	    myPubKey 	 = genPubKey(myPrivKey);
	    theirPubKey  = genPubKey(theirPrivKey);
	    
	    for(encrType=CFE_PublicDES; 
		encrType<=CFE_FEEDExp; 
		encrType++) {
		
		if(verbose) {
		    printf("  ..%s\n", stringFromEncrType(encrType));
		}
		for(doEnc64=0; doEnc64<2; doEnc64++) { 
		    if(verbose) {
		        printf("    ..doEnc64 %d\n", doEnc64);
		    }   
		    
		    if(verbose) {
		        printf("      ..no sig\n");
		    }   
	    	    doTest(ptext, ptextLen, myPrivKey, myPubKey, 
		    	theirPrivKey, theirPubKey,
			encrType, doEnc64, SIG_NO, EXPLICIT_NO);
			
		    if(verbose) {
		        printf("      ..sig, implicit sendPubKey\n");
		    }   
		    doTest(ptext, ptextLen, myPrivKey, myPubKey, 
		    	theirPrivKey, theirPubKey,
			encrType, doEnc64, SIG_YES, EXPLICIT_NO);
			
		    if(verbose) {
		        printf("      ..sig, explicit sendPubKey\n");
		    }   
		    doTest(ptext, ptextLen, myPrivKey, myPubKey, 
		    	theirPrivKey, theirPubKey,
			encrType, doEnc64, SIG_YES, EXPLICIT_YES);
			
		    if(verbose) {
		        printf("      ..sig, force error\n");
		    }   
		    doTest(ptext, ptextLen, myPrivKey, myPubKey, 
		    	theirPrivKey, theirPubKey,
			encrType, doEnc64, SIG_YES, EXPLICIT_ERR);
			
		} /* for doEnc64 */
	    }	  /* for encrType */
	    
	    feePubKeyFree(myPrivKey);
	    feePubKeyFree(myPubKey);
	    feePubKeyFree(theirPrivKey);
	    feePubKeyFree(theirPubKey);
	    if(loops) {
		    if(loop == loops) {
			    break;
		    }
	    }
	}	/* main loop */
	
	if(!quiet) {
		printf("cfile test complete\n");
	}
	return 0;
}
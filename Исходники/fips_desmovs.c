int proc_file(char *rqfile)
    {
    char afn[256], rfn[256];
    FILE *afp = NULL, *rfp = NULL;
    char ibuf[2048];
    int ilen, len, ret = 0;
    char amode[8] = "";
    char atest[100] = "";
    int akeysz=0;
    unsigned char iVec[20], aKey[40];
    int dir = -1, err = 0, step = 0;
    unsigned char plaintext[2048];
    unsigned char ciphertext[2048];
    char *rp;
    EVP_CIPHER_CTX ctx;
    int numkeys=1;

    if (!rqfile || !(*rqfile))
	{
	printf("No req file\n");
	return -1;
	}
    strcpy(afn, rqfile);

    if ((afp = fopen(afn, "r")) == NULL)
	{
	printf("Cannot open file: %s, %s\n", 
	       afn, strerror(errno));
	return -1;
	}
    strcpy(rfn,afn);
    rp=strstr(rfn,"req/");
    assert(rp);
    memcpy(rp,"rsp",3);
    rp = strstr(rfn, ".req");
    memcpy(rp, ".rsp", 4);
    if ((rfp = fopen(rfn, "w")) == NULL)
	{
	printf("Cannot open file: %s, %s\n", 
	       rfn, strerror(errno));
	fclose(afp);
	afp = NULL;
	return -1;
	}
    while (!err && (fgets(ibuf, sizeof(ibuf), afp)) != NULL)
	{
	ilen = strlen(ibuf);
	/*	printf("step=%d ibuf=%s",step,ibuf);*/
	if(step == 3 && !strcmp(amode,"ECB"))
	    {
	    memset(iVec, 0, sizeof(iVec));
	    step = (dir)? 4: 5;  /* no ivec for ECB */
	    }
	switch (step)
	    {
	case 0:  /* read preamble */
	    if (ibuf[0] == '\n')
		{ /* end of preamble */
		if (*amode == '\0')
		    {
		    printf("Missing Mode\n");
		    err = 1;
		    }
		else
		    {
		    fputs(ibuf, rfp);
		    ++ step;
		    }
		}
	    else if (ibuf[0] != '#')
		{
		printf("Invalid preamble item: %s\n", ibuf);
		err = 1;
		}
	    else
		{ /* process preamble */
		char *xp, *pp = ibuf+2;
		int n;
		if(*amode)
		    { /* insert current time & date */
		    time_t rtim = time(0);
		    fprintf(rfp, "# %s", ctime(&rtim));
		    }
		else
		    {
		    fputs(ibuf, rfp);
		    if(!strncmp(pp,"INVERSE ",8) || !strncmp(pp,"DES ",4)
		       || !strncmp(pp,"TDES ",5)
		       || !strncmp(pp,"PERMUTATION ",12)
		       || !strncmp(pp,"SUBSTITUTION ",13)
		       || !strncmp(pp,"VARIABLE ",9))
			{
			/* get test type */
			if(!strncmp(pp,"DES ",4))
			    pp+=4;
			else if(!strncmp(pp,"TDES ",5))
			    pp+=5;
			xp = strchr(pp, ' ');
			n = xp-pp;
			strncpy(atest, pp, n);
			atest[n] = '\0';
			/* get mode */
			xp = strrchr(pp, ' '); /* get mode" */
			n = strlen(xp+1)-1;
			strncpy(amode, xp+1, n);
			amode[n] = '\0';
			/* amode[3] = '\0'; */
			printf("Test=%s, Mode=%s\n",atest,amode);
			}
		    }
		}
	    break;

	case 1:  /* [ENCRYPT] | [DECRYPT] */
	    if(ibuf[0] == '\n')
		break;
	    if (ibuf[0] == '[')
		{
		fputs(ibuf, rfp);
		++step;
		if (strncasecmp(ibuf, "[ENCRYPT]", 9) == 0)
		    dir = 1;
		else if (strncasecmp(ibuf, "[DECRYPT]", 9) == 0)
		    dir = 0;
		else
		    {
		    printf("Invalid keyword: %s\n", ibuf);
		    err = 1;
		    }
		break;
		}
	    else if (dir == -1)
		{
		err = 1;
		printf("Missing ENCRYPT/DECRYPT keyword\n");
		break;
		}
	    else 
		step = 2;

	case 2: /* KEY = xxxx */
	    if(*ibuf == '\n')
		{
	        fputs(ibuf, rfp);
		break;
                }
	    if(!strncasecmp(ibuf,"COUNT = ",8))
		{
	        fputs(ibuf, rfp);
		break;
                }
	    if(!strncasecmp(ibuf,"COUNT=",6))
		{
	        fputs(ibuf, rfp);
		break;
                }
	    if(!strncasecmp(ibuf,"NumKeys = ",10))
		{
		numkeys=atoi(ibuf+10);
		break;
		}
	  
	    fputs(ibuf, rfp);
	    if(!strncasecmp(ibuf,"KEY = ",6))
		{
		akeysz=64;
		len = hex2bin((char*)ibuf+6, strlen(ibuf+6)-1, aKey);
		if (len < 0)
		    {
		    printf("Invalid KEY\n");
		    err=1;
		    break;
		    }
		PrintValue("KEY", aKey, len);
		++step;
		}
	    else if(!strncasecmp(ibuf,"KEYs = ",7))
		{
		akeysz=64*3;
		len=hex2bin(ibuf+7,strlen(ibuf+7)-1,aKey);
		if(len != 8)
		    {
		    printf("Invalid KEY\n");
		    err=1;
		    break;
		    }
		memcpy(aKey+8,aKey,8);
		memcpy(aKey+16,aKey,8);
		ibuf[4]='\0';
		PrintValue("KEYs",aKey,len);
		++step;
		}
	    else if(!strncasecmp(ibuf,"KEY",3))
		{
		int n=ibuf[3]-'1';

		akeysz=64*3;
		len=hex2bin(ibuf+7,strlen(ibuf+7)-1,aKey+n*8);
		if(len != 8)
		    {
		    printf("Invalid KEY\n");
		    err=1;
		    break;
		    }
		ibuf[4]='\0';
		PrintValue(ibuf,aKey,len);
		if(n == 2)
		    ++step;
		}
	    else
		{
		printf("Missing KEY\n");
		err = 1;
		}
	    break;

	case 3: /* IV = xxxx */
	    fputs(ibuf, rfp);
	    if (strncasecmp(ibuf, "IV = ", 5) != 0)
		{
		printf("Missing IV\n");
		err = 1;
		}
	    else
		{
		len = hex2bin((char*)ibuf+5, strlen(ibuf+5)-1, iVec);
		if (len < 0)
		    {
		    printf("Invalid IV\n");
		    err =1;
		    break;
		    }
		PrintValue("IV", iVec, len);
		step = (dir)? 4: 5;
		}
	    break;

	case 4: /* PLAINTEXT = xxxx */
	    fputs(ibuf, rfp);
	    if (strncasecmp(ibuf, "PLAINTEXT = ", 12) != 0)
		{
		printf("Missing PLAINTEXT\n");
		err = 1;
		}
	    else
		{
		int nn = strlen(ibuf+12);
		if(!strcmp(amode,"CFB1"))
		    len=bint2bin(ibuf+12,nn-1,plaintext);
		else
		    len=hex2bin(ibuf+12, nn-1,plaintext);
		if (len < 0)
		    {
		    printf("Invalid PLAINTEXT: %s", ibuf+12);
		    err =1;
		    break;
		    }
		if (len >= sizeof(plaintext))
		    {
		    printf("Buffer overflow\n");
		    }
		PrintValue("PLAINTEXT", (unsigned char*)plaintext, len);
		if (strcmp(atest, "Monte") == 0)  /* Monte Carlo Test */
		    {
		    do_mct(amode,akeysz,numkeys,aKey,iVec,dir,plaintext,len,rfp);
		    }
		else
		    {
		    assert(dir == 1);
		    ret = DESTest(&ctx, amode, akeysz, aKey, iVec, 
				  dir,  /* 0 = decrypt, 1 = encrypt */
				  ciphertext, plaintext, len);
		    OutputValue("CIPHERTEXT",ciphertext,len,rfp,
				!strcmp(amode,"CFB1"));
		    }
		step = 6;
		}
	    break;

	case 5: /* CIPHERTEXT = xxxx */
	    fputs(ibuf, rfp);
	    if (strncasecmp(ibuf, "CIPHERTEXT = ", 13) != 0)
		{
		printf("Missing KEY\n");
		err = 1;
		}
	    else
		{
		if(!strcmp(amode,"CFB1"))
		    len=bint2bin(ibuf+13,strlen(ibuf+13)-1,ciphertext);
		else
		    len = hex2bin(ibuf+13,strlen(ibuf+13)-1,ciphertext);
		if (len < 0)
		    {
		    printf("Invalid CIPHERTEXT\n");
		    err =1;
		    break;
		    }
		
		PrintValue("CIPHERTEXT", ciphertext, len);
		if (strcmp(atest, "Monte") == 0)  /* Monte Carlo Test */
		    {
		    do_mct(amode, akeysz, numkeys, aKey, iVec, 
			   dir, ciphertext, len, rfp);
		    }
		else
		    {
		    assert(dir == 0);
		    ret = DESTest(&ctx, amode, akeysz, aKey, iVec, 
				  dir,  /* 0 = decrypt, 1 = encrypt */
				  plaintext, ciphertext, len);
		    OutputValue("PLAINTEXT",(unsigned char *)plaintext,len,rfp,
				!strcmp(amode,"CFB1"));
		    }
		step = 6;
		}
	    break;

	case 6:
	    if (ibuf[0] != '\n')
		{
		err = 1;
		printf("Missing terminator\n");
		}
	    else if (strcmp(atest, "MCT") != 0)
		{ /* MCT already added terminating nl */
		fputs(ibuf, rfp);
		}
	    step = 1;
	    break;
	    }
	}
    if (rfp)
	fclose(rfp);
    if (afp)
	fclose(afp);
    return err;
    }
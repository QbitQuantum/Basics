Boolean LIBCALL VastToCn3D(WWWInfoPtr www_info)
{
	FILE *pFile = NULL;
	FILE *pIn = NULL;
	Char pcBuf[100], pcLine[256], giBuf[20], URL[200];
	CharPtr pcTest, pcL1 = NULL, Name, www_arg;
	Int4 GetGi, Fid, Fsid, iFileExists = 0, indx;
	BiostrucAnnotSetPtr pbsa = NULL; 
	BiostrucAnnotSetPtr pbsaShort = NULL;
        BiostrucFeatureSetPtr pbsfs = NULL;
        BiostrucFeaturePtr pbsf = NULL;
        BiostrucResidueGraphSetPtr stdDictionary;
        ValNodePtr pvnFids = NULL, pvnFid = NULL;
        Int2 iTest = 0, iPDB = 0, iColor;
	AsnIoPtr aip = NULL; 
	Byte bRender;
	Char *IPAddress = getenv("REMOTE_HOST");
        Int4 NumLabels, iMMDBId;
	ValNode * pbsidThis;
	BiostrucPtr pbsMaster, pbsSlave, pbsSlaveHead = NULL, pbsSlaveTail, pbsTemp;
	Char szName[5], chain[2];
	Char * szTemp;
  SeqAnnotPtr psaAlignHead = NULL, psaAlignTail;
  SeqAlignPtr salpHead, salpTail;
  SeqIdPtr      sip;   
  DenseSegPtr   dsp; 
  BioseqPtr bsp;
  SeqEntryPtr sep;
    char  str [52];
    NcbiMimeAsn1Ptr pvnNcbi;
    BiostrucAlignPtr pbsaStruct;
    AsnIoPtr paiFile, aipr;
    Boolean is_network;
    Int4 uid, uidmaster = 0;
 Int2 retcode = 3;
 CharPtr JobID = NULL, pcPass;
 Char AsnPath[PATH_MAX];
 Char AsnName[10];
 Int2 ret, complexity;
 Int4 iFidCount = 0;
 Boolean Chain;

 /*    SeqAsnLoad();
    
    
    objmmdb1AsnLoad();
    objmmdb2AsnLoad();
    objmmdb3AsnLoad();
    SeqAlignAsnLoad();
    objmimeAsnLoad();
    */


	if ((indx = WWWFindName(www_info, "uid")) < 0) {
		printf("Content-type: text/html\n\n");
		printf("<h3>No accession (PDB ID) was input - nothing to report.</h3>\n"); 
		return 0;
	}

	www_arg =  WWWGetValueByIndex(www_info, indx);

	if (isdigit(www_arg[0]))
		GetGi = (Int4) atoi(www_arg);
	else {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>Non-numeric MMDB-id input - no results.</h3>\n"); 
		return 0;
	}

	/* vsid and pass are to look at alignments from VAST Search */
	if ((indx = WWWFindName(www_info, "vsid")) >= 0) {
		www_arg = WWWGetValueByIndex(www_info, indx);
		JobID = StringSave(www_arg);

		if ((indx = WWWFindName(www_info, "pass")) < 0) {
			printf("Content-type: text/html\n\n");
			printf("<body bgcolor = \"#f0f0f0\">\n");
			printf("<h2>VAST SEARCH</h2>\n");
			printf("<h3>Password required.</h3>\n");
			return 0;
		}
		else {
			www_arg = WWWGetValueByIndex(www_info, indx);
			pcPass = StringSave(www_arg);

			if ((ret = Check_VastSearch_Password(pcPass, JobID)) != 1) {
				if (ret == 2) return 0;
				printf("Content-type: text/html\n\n");
				printf("<body bgcolor = \"#f0f0f0\">\n");
				printf("<h2>VAST SEARCH</h2>\n");
				printf("<h3>Incorrect password.</h3>\n"); 
				return 0;
			}
		}
	}

	if ((indx = WWWFindName(www_info, "hit")) < 0) {
		printf("Content-type: text/html\n\n");
		printf("<body bgcolor = \"#f0f0f0\">\n");
		printf("<br>\n<h2>No alignment was selected!</h2>\n");
		printf("<h3>Please click on up to 5 boxes in the leftmost column of the table.</h3>\n"); 
		return 0;
	}
        
	/* loop over all the "hit" values in the list */
	NumLabels = WWWGetNumEntries(www_info);

	for (indx = 0; indx < NumLabels; indx++) {
		Name = WWWGetNameByIndex(www_info, indx);

		if (StrICmp(Name, "hit") == 0) {
			www_arg = WWWGetValueByIndex(www_info, indx);

			if (isdigit(www_arg[0]))
				Fid = (Int4) atol(www_arg);
			else {
				printf("Content-type: text/html\n\n");
				printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
				printf("<h3>Non-numeric slave alignment code - no results.</h3>\n");
				return 0;
			}

			if (++iFidCount > 5) break;
			pvnFid = ValNodeAddInt(&pvnFids, 0, Fid);
		}
 	}

	if ((indx = WWWFindName(www_info, "chaindom")) < 0) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>No feature set ID (master alignment code) - nothing to report.</h3>\n");
		return 0;
	}

	www_arg = WWWGetValueByIndex(www_info, indx);

	if (isdigit(www_arg[0]))
		Fsid = (Int4) atoi(www_arg);
	else {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>Non-numeric master alignment code - no results.</h3>\n");
		return 0;
	}
        
        if ((indx = WWWFindName(www_info, "chn_complexity")) < 0)
            Chain = TRUE;
        else
        {
          www_arg = WWWGetValueByIndex(www_info, indx);
          complexity =(Int2)atoi(www_arg);

          if (complexity) Chain = TRUE;
          else Chain = FALSE;
        }
  
	if ((indx = WWWFindName(www_info, "atm_complexity")) < 0)
		/* select alpha Carbons only by default */
		complexity = ONECOORDRES;
	else {
		www_arg = WWWGetValueByIndex(www_info, indx);

		if (isdigit(www_arg[0]))
			complexity = (Int2) atoi(www_arg);
		else
			complexity = ONECOORDRES;
	}

	if ((complexity != ONECOORDRES) && (complexity != ONECOORDATOM))
		/* bizarre value, but default to alpha-Carbons only */
		complexity = ONECOORDRES;

	/* action == 0 indicates MIME; action == 1 is text; action == 2 is save */
	if ((indx = WWWFindName(www_info, "action")) < 0)
		iPDB = 0;
	else {
		www_arg = WWWGetValueByIndex(www_info, indx);

		if (isdigit(www_arg[0]))
			iPDB = (Int4) atoi(www_arg);
		else
			iPDB = 0;
	}

	if (VASTInit() != TRUE) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>Can't find VAST data on server.\n");
		printf("Contact [email protected]</h3>\n"); 
		return 0;
	}

	OpenMMDBAPI((POWER_VIEW /* ^ FETCH_ENTREZ */), NULL);
	pbsa = LocalGetFeatureSet(GetGi, Fsid, JobID);
	
        if (pbsa == NULL) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>No master alignment record exists for %ld.</h3>\n", (long) GetGi);
		return 0; 
	}
        
	if (iFidCount == 1)
          pbsaShort = BiostrucAnnotSetGetByFid(pbsa, Fid, Fsid);
        else
          pbsaShort = PruneBiostrucAnnotHits(pbsa, Fsid, pvnFids);
	
        if (pbsaShort == NULL) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>Can't find alignment record.</h3>\n");
		return 0; 
	}
  
	if (MMDBInit() == FALSE) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>MMDBInit failed.</h3>\n");
		return 0;
	}

        pbsfs = pbsaShort->features;
        
        pbsaStruct = BiostrucAlignNew();
         
        if (pbsfs)
        {
          pbsf = pbsfs->features;
          szTemp = pbsf->name;
	  szName[0] = szTemp[0];
	  szName[1] = szTemp[1];
	  szName[2] = szTemp[2];
	  szName[3] = szTemp[3];
	  szName[4] = '\0';
        }
        
        if (JobID == NULL)
        pbsMaster = FetchBiostrucPDB(szName, complexity, 1);
        else
        {
          AsnName[0]='\0';
          StringCpy(AsnName, "/b");
          StringCat(AsnName, szName);
	
          AsnPath[0]='\0';
          StringCpy(AsnPath, VSPATH);
          StringCat(AsnPath, JobID);
          StringCat(AsnPath, AsnName);
   
          pbsMaster = FetchBS(AsnPath, 0, complexity, 1, POWER_VIEW);
        }

        if (pbsMaster == NULL)
        {
	  printf("Content-type: text/html\n\n");
	  printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
	  printf("<h3> Unable to load master structure.</h3>\n");
	  return 0;
	}
       
        /* Load in Standard Dictionary to make sequences - Ken */
        aipr = NULL;
        aipr = AsnIoOpen("bstdt", "rb");
        
        if (aipr == NULL) 
        {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		printf("<h3>Can't find standard dictionary.</h3>\n");
		return 0; 
	}
        
        stdDictionary = BiostrucResidueGraphSetAsnRead(aipr, NULL);
        AsnIoFlush(aipr);
        aipr = AsnIoClose(aipr);
       
       /* retrieve the bioseq for master and put in ValNode */
       sep = (SeqEntryPtr) MakeBioseqs(pbsMaster, stdDictionary);
       if ( sep == NULL ) 
       {
         printf("Content-type: text/html\n\n");
         printf("<h2>VASTSERV Error (VastToCn3d)</h2>\n");
         printf("<h3>Unable to get SeqEntry.</h3>\n");
         return 0;
       } 
       ValNodeLink(&(pbsaStruct->sequences), sep);
       /* PruneBiostruc if Aligned Chain Options has been chosen */
       if (Chain)
       {
         if (szTemp[4] != ' ')
         {
           chain[0] = szTemp[4];
           chain[1] = '\0';
           pbsTemp = (BiostrucPtr)PruneBiostruc(pbsMaster, chain);
           pbsMaster = NULL;
           pbsMaster = pbsTemp;
         }
       }
    
        /* Make a linked list of Biostrucs of the slave structures*/   
         while (pbsf)
         {
            szTemp = pbsf->name;
            szName[0] = szTemp[7];
	    szName[1] = szTemp[8];
	    szName[2] = szTemp[9];
	    szName[3] = szTemp[10];
	    szName[4] = '\0';

	    if (!pbsSlaveHead) 
            {
                pbsSlaveHead =  FetchBiostrucPDB(szName, complexity, 1); 
		if (!pbsSlaveHead)
                {
                  printf("Content-type: text/html\n\n");
		  printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		  printf("<h3> Unable to load slave structure.</h3>\n");
		  return 0;
                }
                /* Make Bioseq for Slaves */
                sep = (SeqEntryPtr) MakeBioseqs(pbsSlaveHead, stdDictionary);
                if ( sep == NULL ) 
                {
		  printf("Content-type: text/html\n\n");
		  printf("<h2>VASTSERV Error (VastToCn3d)</h2>\n");
		  printf("<h3>Unable to get SeqEntry.</h3>\n");
		  return 0;
	        } 
                ValNodeLink(&(pbsaStruct->sequences), sep);
                /* PruneBiostruc if Aligned Chain Options has been chosen */
                if (Chain)
                {
                  if (szTemp[11] != ' ')
                  {
                    chain[0] = szTemp[11];
                    chain[1] = '\0';
                    pbsTemp = (BiostrucPtr)PruneBiostruc(pbsSlaveHead, chain);
                    pbsSlaveHead = NULL;
                    pbsSlaveHead = pbsTemp;
                  }
                }   
                pbsSlaveTail = pbsSlaveHead;
	    }
            else
            { 
		pbsSlave = FetchBiostrucPDB(szName, complexity, 1);
		if (!pbsSlave) 
                {
                  printf("Content-type: text/html\n\n");
		  printf("<h2>VASTSERV Error (VastToCn3D)</h2>\n");
		  printf("<h3> Unable to load slave structure.</h3>\n");
		  return 0;
                }
		/* Make Bioseq for Slaves */
                sep = (SeqEntryPtr) MakeBioseqs(pbsSlave, stdDictionary);
                if ( sep == NULL ) 
                {
		  printf("Content-type: text/html\n\n");
		  printf("<h2>VASTSERV Error (VastToCn3d)</h2>\n");
		  printf("<h3>Unable to get SeqEntry.</h3>\n");
		  return 0;
	        } 
                ValNodeLink(&(pbsaStruct->sequences), sep);
                /* PruneBiostruc if Aligned Chain Options has been chosen */
                if (Chain)
                {
                  if (szTemp[11] != ' ')
                  {
                    chain[0] = szTemp[11];
                    chain[1] = '\0';
                    pbsTemp = (BiostrucPtr)PruneBiostruc(pbsSlave, chain);
                    pbsSlave = NULL;
                    pbsSlave = pbsTemp;
                  }
                }
                pbsSlaveTail->next = pbsSlave;
                pbsSlaveTail = pbsSlaveTail->next;
                pbsSlaveTail->next = NULL;
            }
          
            pbsf = pbsf->next;
         }
        /* Make a linked list of sequence alignments of master and slaves */
        pbsf=pbsfs->features;
        while (pbsf) {
          if (!psaAlignHead) {
            psaAlignHead = fnPBSFtoPSA (pbsf);  /* get the sequence alignments */
            if (psaAlignHead == NULL || psaAlignHead->data == NULL) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3d)</h2>\n");
		printf("<h3>Unable to create SeqAnnot.</h3>\n");
		return 0;
	    }
            salpHead = (SeqAlignPtr)(psaAlignHead->data);
            salpTail = salpHead;
          }
          else {
             psaAlignTail = fnPBSFtoPSA (pbsf);
             salpTail->next = (SeqAlignPtr)(psaAlignTail->data);
             if (psaAlignTail == NULL || psaAlignTail->data == NULL) {
		printf("Content-type: text/html\n\n");
		printf("<h2>VASTSERV Error (VastToCn3d)</h2>\n");
		printf("<h3>Unable to create SeqAnnot.</h3>\n");
		return 0;
	     }
             salpTail = salpTail->next;
             salpTail->next = NULL;
          }
          pbsf = pbsf->next;
        }
        
  pbsaStruct->master = pbsMaster;
  pbsaStruct->slaves = pbsSlaveHead;
  pbsaStruct->alignments = pbsaShort;
  pbsaStruct->seqalign = psaAlignHead;

  pvnNcbi = ValNodeNew(NULL);
  pvnNcbi->choice =  NcbiMimeAsn1_alignstruc;
  pvnNcbi->data.ptrvalue = pbsaStruct;
  pvnNcbi = (NcbiMimeAsn1Ptr) CheckId(pvnNcbi, JobID);      /* to check identity, yanli  */

  OutputFile = stdout;

  if (iPDB == 0)		/* cn3d MIME */
    printf ("Content-type: chemical/ncbi-asn1-binary\n\n");

  else if (iPDB == 1) {		/* "See File" */
    printf ("Content-type: text/html\n\n");
    printf ("<HTML><body><pre>\n");
  }

  else				/* "Save File" */
    printf ("Content-type: application/octet-stream\n\n");

  if (iPDB != 1)
    paiFile = AsnIoNew(ASNIO_BIN_OUT, stdout, NULL, NULL, NULL);

  else
    paiFile = AsnIoNew(ASNIO_TEXT_OUT, stdout, NULL, NULL, NULL);

  NcbiMimeAsn1AsnWrite(pvnNcbi, paiFile, NULL);
  AsnIoFlush(paiFile);
  AsnIoClose(paiFile);

  CloseMMDBAPI();
  MMDBFini();
  VASTFini();
  return 0;

} /* end of VastToCn3D */
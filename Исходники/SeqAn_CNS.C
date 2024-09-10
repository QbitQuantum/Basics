int32
main(int32 argc, char **argv) {
   int32 arg = 1;
   int32 err = 0;
   int32 hlp = 0;

   char * gkpStoreName  = NULL;
   int32  gkpStorePart  = 0;
   char * msgFile       = NULL;
   char * outputFileName= NULL;
   char * seqAn         = NULL;
   char * wrkDir        = NULL;
   char * seqStoreName  = NULL;
   int32  seqStoreVer   = 0;
   int32  seqStorePart  = 0;     

   argc = AS_configure(argc, argv);

   while (arg < argc) {
      if (strcmp(argv[arg], "-c") == 0) {
         msgFile = argv[++arg];
      } else if (strcmp(argv[arg], "-G") == 0) {
         gkpStoreName = argv[++arg];
      } else if (strcmp(argv[arg], "-S") == 0) {
         gkpStorePart = atoi(argv[++arg]);
      } else if (strcmp(argv[arg], "-o") == 0) {
         outputFileName = argv[++arg];
      } else if (strcmp(argv[arg], "-s") == 0) {
         seqAn = argv[++arg];
      } else if (strcmp(argv[arg], "-w") == 0) {
         wrkDir = argv[++arg];
      } else if (strcmp(argv[arg], "-u") == 0) {
         seqStoreName = argv[++arg];
      } else if (strcmp(argv[arg], "-V") == 0) {
         seqStoreVer = atoi(argv[++arg]);
      } else if (strcmp(argv[arg], "-p") == 0) {
         seqStorePart = atoi(argv[++arg]);
      } else {
         err++;
      }
      arg++;
   }

   if ((err) || (gkpStoreName == NULL) || (msgFile == NULL) || (outputFileName == NULL) || seqAn == NULL) {
      fprintf(stderr, "USAGE: SeqAn_CNS -G <gkpStore> -c <input.cgb> -o <output.cgi> -s <seqan_executable> [-u seqstore, required for contig consensus] [-w working directory]\n");      
      exit(1);
   }

   gkStore        *gkpStore = new gkStore(gkpStoreName, FALSE, FALSE);

   gkpStore->gkStore_loadPartition(gkpStorePart);
   
   gkFragment      fr;
   GenericMesg    *pmesg;
   tSequenceDB    *sequenceDB = NULL;   

   FILE *infp = fopen(msgFile,"r");
   FILE *tempReads;
   FILE *outfp = fopen(outputFileName, "w");
   char fileName[AS_SEQAN_MAX_BUFFER_LENGTH];
   char *prefix = outputFileName;
   getFileName(prefix, wrkDir, AS_SEQAN_INPUT_NAME, fileName);

   int32 i = 0;
   
   while ((EOF != ReadProtoMesg_AS(infp, &pmesg))) {
      int32 freeMem = 0;
     
      if (pmesg->t == MESG_IUM) {
         IntUnitigMesg *ium_mesg = (IntUnitigMesg *)pmesg->m;         
         
         if (strlen(ium_mesg->consensus) == 0) {
            tempReads = fopen(fileName,"w");

            for (i =0; i < ium_mesg->num_frags; i++) {
               // get the fragment sequence
               gkpStore->gkStore_getFragment(ium_mesg->f_list[i].ident, &fr, GKFRAGMENT_QLT);
               uint32   clrBeg = fr.gkFragment_getClearRegionBegin();
               uint32   clrEnd = fr.gkFragment_getClearRegionEnd  ();
               char    *seqStart = fr.gkFragment_getSequence();
               char     *seq      = seqStart+clrBeg;

               seq[clrEnd] = 0;
               AS_UTL_writeFastA(tempReads,
                  seq, clrEnd-clrBeg,
                   ">"F_IID","F_IID"\n", ium_mesg->f_list[i].position.bgn, ium_mesg->f_list[i].position.end);
            }
            fclose(tempReads);
            updateRecord(ium_mesg, fileName, seqAn, prefix, wrkDir);
            freeMem = 1;
         }
         WriteProtoMesg_AS(outfp, pmesg);

         if (freeMem) {
            safe_free(ium_mesg->consensus);
            safe_free(ium_mesg->quality);
         }
      }
      else if (pmesg->t == MESG_ICM) {         
         IntConConMesg *icm_mesg = (IntConConMesg *)pmesg->m;

         if (seqStoreName == NULL) {
            fprintf(stderr, "USAGE: The -u option is required for contig consensus\n");
            exit(1);
         }
         if (sequenceDB == NULL) {
            sequenceDB = openSequenceDB(seqStoreName, FALSE, seqStoreVer);
            openSequenceDBPartition(sequenceDB, seqStorePart);
         }
         
         if (strlen(icm_mesg->consensus) == 0) {
            tempReads = fopen(fileName,"w");

            for (i =0; i < icm_mesg->num_pieces; i++) {
               // get the fragment sequence
               gkpStore->gkStore_getFragment(icm_mesg->pieces[i].ident, &fr, GKFRAGMENT_QLT);
               uint32   clrBeg   = fr.gkFragment_getClearRegionBegin();
               uint32   clrEnd   = fr.gkFragment_getClearRegionEnd  ();
               char    *seqStart = fr.gkFragment_getSequence();
               char    *seq      = seqStart+clrBeg;

               seq[clrEnd] = 0;
               AS_UTL_writeFastA(tempReads,
                  seq, clrEnd-clrBeg,
                   ">"F_IID","F_IID"\n", icm_mesg->pieces[i].position.bgn, icm_mesg->pieces[i].position.end);
            }
            
            // now handle the unitig messages
            for (i =0; i < icm_mesg->num_unitigs; i++) {
               VA_TYPE(char) *ungappedSequence = CreateVA_char(0);
               VA_TYPE(char) *ungappedQuality  = CreateVA_char(0);
               MultiAlignT *uma = loadMultiAlignTFromSequenceDB(sequenceDB, icm_mesg->unitigs[i].ident, 1);
               assert(uma != NULL);
               
               GetMultiAlignUngappedConsensus(uma, ungappedSequence, ungappedQuality);
               char * seq = Getchar(ungappedSequence,0);

               AS_UTL_writeFastA(tempReads,
                  seq, strlen(seq),
                   ">"F_IID","F_IID"\n", icm_mesg->unitigs[i].position.bgn, icm_mesg->unitigs[i].position.end);
            }
            fclose(tempReads);

            updateICMRecord(icm_mesg, fileName, seqAn, prefix, wrkDir);
            freeMem = 1;
         }
         WriteProtoMesg_AS(outfp, pmesg);

         if (freeMem) {
            safe_free(icm_mesg->consensus);
            safe_free(icm_mesg->quality);
         }
      }
   }
      
   fclose(infp);
   fclose(outfp);

   return 0;
}
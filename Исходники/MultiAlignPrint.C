void
PrintMultiAlignT(FILE *out,
                 MultiAlignT *ma,
                 gkStore *frag_store,
                 int32 show_qv,
                 int32 dots,
                 uint32 clrrng_flag)  {

  int32 depth;
  int32 i;
  int32 window;
  char **multia=NULL;
  int32 **idarray;
  int32 **oriarray;
  char *consensus = Getchar(ma->consensus,0);
  char *quality   = Getchar(ma->quality,0);

  gkFragment rsp;

  dots = 0;

  if ((consensus == NULL) || (consensus[0] == 0)) {
    fprintf(out, "No MultiAlignment to print for tig %d -- no consensus sequence present.\n", ma->maID);
    return;
  }

  int32 length = strlen(consensus);

  IMP2Array(GetIntMultiPos(ma->f_list,0),
            GetNumIntMultiPoss(ma->f_list),
            GetNumchars(ma->consensus),
            frag_store,
            &depth,
            &multia,
            &idarray,
            &oriarray,
            clrrng_flag);

  fprintf(out,"<<< begin Contig %d >>>",ma->maID);;

  char  gruler[MULTIALIGN_PRINT_WIDTH + 200];
  char  uruler[MULTIALIGN_PRINT_WIDTH + 200];

  int32 ungapped = 1;
  int32 tick     = 1;

  for (window=0;window<length;) {
    int32 row_id  = 0;
    int32 orient  = 0;
    int32 rowlen  = (window + MULTIALIGN_PRINT_WIDTH < length) ? MULTIALIGN_PRINT_WIDTH : length - window;

    fprintf(out, "\n");
    fprintf(out, "\n");
    fprintf(out, "<<<  Contig %d, gapped length: %d  >>>\n",ma->maID, length);

    {
      memset(gruler, 0, MULTIALIGN_PRINT_WIDTH + 200);
      memset(uruler, 0, MULTIALIGN_PRINT_WIDTH + 200);

      for (int32 rowind=0; rowind<rowlen; rowind++) {
        if (((window + 1 + rowind) % 25) == 0)
          sprintf(gruler + rowind, "| GAP=%d", window + 1 + rowind);

        if ((ungapped % 25) == 0)
          sprintf(uruler + rowind, "| UNG=%d", ungapped);

        if (consensus[window + rowind] != '-')
          ungapped++;
      }

      for (int32 i=0; i<MULTIALIGN_PRINT_WIDTH; i++) {
        if (gruler[i] == 0)
          gruler[i] = ' ';
        if (uruler[i] == 0)
          uruler[i] = ' ';
      }

      for (int32 i=MULTIALIGN_PRINT_WIDTH-1; (i >= 0) && (gruler[i] == ' '); i--)
        gruler[i] = 0;
      for (int32 i=MULTIALIGN_PRINT_WIDTH-1; (i >= 0) && (uruler[i] == ' '); i--)
        uruler[i] = 0;

      fprintf(out, "%s\n", gruler);
      fprintf(out, "%s\n", uruler);
    }


    {
      char save = consensus[window + rowlen];
      consensus[window+rowlen] = 0;
      fprintf(out,"%s  cns  (uid,iid) type\n", consensus+window);
      consensus[window+rowlen] = save;
    }

    {
      char save = quality[window + rowlen];
      quality[window+rowlen] = 0;
      fprintf(out,"%s  qlt\n", quality+window);
      quality[window+rowlen] = save;
    }

    for (i=0;i<depth;i++) {
      assert(multia[2*i] != NULL);

      //  Change matching bases to '.' or lowercase.
      //  Count the number of non-blank letters.

      int32  nonBlank = 0;

      for (int32 j=0; j<MULTIALIGN_PRINT_WIDTH; j++) {
        if (window + j > length)
          break;

        if (multia[2*i][window+j] == consensus[window+j]) {
          if (dots) {
            multia[2*i]  [window+j] = '.';
            multia[2*i+1][window+j] = ' ';
          } else {
            multia[2*i][window+j] = tolower(multia[2*i][window+j]);
          }
        }

        if (multia[2*i][window+j] != ' ')
          nonBlank++;

        if (idarray[i][window + j] > 0) {
          row_id = idarray[i][window + j];
          orient = oriarray[i][window + j];
        }
      }

      if (nonBlank == 0)
        continue;

      //  Figure out the ID and orientation for this block

      frag_store->gkStore_getFragment(row_id, &rsp, GKFRAGMENT_INF);

      {
        char save = multia[2*i][window + MULTIALIGN_PRINT_WIDTH];
        multia[2*i][window + MULTIALIGN_PRINT_WIDTH] = 0;
        fprintf(out, "%s   %c   (%s,%d)\n",
                multia[2*i]+window,
                (orient>0)?'>':'<',
                AS_UID_toString(rsp.gkFragment_getReadUID()),
                row_id);
        multia[2*i][window + MULTIALIGN_PRINT_WIDTH] = save;
      }

      if (show_qv) {
        char save = multia[2*i+1][window + MULTIALIGN_PRINT_WIDTH];
        multia[2*i+1][window + MULTIALIGN_PRINT_WIDTH] = 0;
        fprintf(out, "%s\n", multia[2*i+1]+window);
        multia[2*i+1][window + MULTIALIGN_PRINT_WIDTH] = save;
      }
    }

    window += MULTIALIGN_PRINT_WIDTH;
  }
  fprintf(out,"\n<<< end Contig %d >>>\n", ma->maID);



  for (i=0;i<2*depth;i++)
    safe_free(multia[i]);

  safe_free(multia);

  for (i=0;i<depth;i++) {
    safe_free(idarray[i]);
    safe_free(oriarray[i]);
  }

  safe_free(idarray);
  safe_free(oriarray);
}
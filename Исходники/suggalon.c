static Boolean Get_Params (void)

{
  FILE  *f;
  FILE  *g;
  Int4  i;
  Int2  j;
  Int4  len;
  Int4  num_nuc;
  Int4  num_prt;

  if (GetArgs ("suggest", NUMARG, myargs)) {
    if (NUMARG == TOTARG && myargs [8].intvalue) {
      suggestRec.lookForStop = (Boolean) (myargs [6].intvalue);
      StringNCpy (inputFile, myargs [0].strvalue, sizeof (inputFile));
      if (inputFile [0] == '\0') {
        StringCpy (inputFile, "stdin");
      }
      StringNCpy (outputFile, myargs [1].strvalue, sizeof (outputFile));
      if (outputFile [0] == '\0') {
        StringCpy (outputFile, "stdout");
      }
      f = FileOpen (inputFile, "r");
      if (f != NULL) {
        Get_DNA (f, &suggestRec);
        FileClose (f);
        dna_seq = suggestRec.nucleotide.sequence;
        dna_len = StringLen (dna_seq);
        if (dna_len > 3 && dna_seq != NULL) {
          dna_len -= 3;
          dna_seq [dna_len] = '\0';
        }
        rev_seq = MemNew(dna_len+1);
        if (rev_seq != NULL) {
          reverse (dna_len);
          f = FileOpen (outputFile, "w");
          if (f != NULL) {
            j = 0;
            for (i = 0; i < dna_len; i++) {
              fputc ((int) (rev_seq [i]), f);
              j++;
              if (j >= 50) {
                fputc ((int) '\n', f);
                j = 0;
              }
            }
            if (j > 0) {
              fputc ((int) '\n', f);
            }
            FileClose (f);
          }
        }
      }
    } else {
      suggestRec.lookForStop = (Boolean) (myargs [6].intvalue);
      StringNCpy (inputFile, myargs [0].strvalue, sizeof (inputFile));
      if (inputFile [0] == '\0') {
        StringCpy (inputFile, "stdin");
      }
      StringNCpy (outputFile, myargs [1].strvalue, sizeof (outputFile));
      if (outputFile [0] == '\0') {
        StringCpy (outputFile, "stdout");
      }
      f = FileOpen (inputFile, "r");
      if (f != NULL) {
        g = FileOpen (outputFile, "w");
        if (g != NULL) {
	  suggestOut.out.fileOut = g;
          while (! feof (f)) {
            if ((Boolean) (myargs [7].intvalue)) {
              Get_DNA (f, &suggestRec);
              Get_Protein (f, &suggestRec);
            } else {
              Get_Protein (f, &suggestRec);
              Get_DNA (f, &suggestRec);
            }
            Get_Genetic_Code (myargs [2].intvalue, &suggestRec);
            suggestRec.minVal = (myargs [3].intvalue);
            suggestRec.maxVal = (myargs [4].intvalue);
            suggestRec.minExon = (myargs [5].intvalue);

	    ProcessData(&suggestOut);
          }
          FileClose (g);
        }
        FileClose (f);
      }
    }
    return TRUE;
  } else {
    return FALSE;
  }
}
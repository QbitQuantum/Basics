int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s seqfile indexfile readfile\n", argv[0]);
    exit(-1);
  }
  char *seq, *seqfile, *indexfile, *readfile, *buf = malloc(256*256), *revbuf = malloc(256*256), c;
  fm_index *fmi;
  int len;
  int i, j, k, jj;
  FILE *sfp, *ifp, *rfp;
  seqfile = argv[1];
  indexfile = argv[2];
  readfile = argv[3];
  sfp = fopen(seqfile, "rb");
  if (sfp == 0) {
    fprintf(stderr, "Could not open sequence\n");
    exit(-1);
  }
  fseek(sfp, 0L, SEEK_END);
  len = ftell(sfp);
  rewind(sfp);
  seq = malloc(len/4+1);
  for (i = 0; i < len/4 + 1; ++i) {
    switch(fgetc(sfp)) {
    case 'C': c = 64; break;
    case 'G': c = 128; break;
    case 'T': c = 192; break;
    default: c = 0;
    }
    switch(fgetc(sfp)) {
    case 'C': c ^= 16; break;
    case 'G': c ^= 32; break;
    case 'T': c ^= 48;
    }
    switch(fgetc(sfp)) {
    case 'C': c ^= 4; break;
    case 'G': c ^= 8; break;
    case 'T': c ^= 12;
    }
    switch(fgetc(sfp)) {
    case 'C': c ^= 1; break;
    case 'G': c ^= 2; break;
    case 'T': c ^= 3;
    }
    seq[i] = c;
  }
  // Handle the last character (which is at seq[len/4]
  c = 0;
  for (i = 0; i < len&3; ++i) {
    switch(fgetc(sfp)) {
    case 'C': c ^= 64 >> (2 * i); break;
    case 'G': c ^= 128 >> (2 * i); break;
    case 'T': c ^= 192 >> (2 * i);
    }
    seq[len/4] = c;
  }
  fclose(sfp);
  
  // Open index file
  ifp = fopen(indexfile, "rb");
  if (ifp == 0) {
    fprintf(stderr, "Could not open index file");
    exit(-1);
  }
  fmi = read_index(seq, ifp);
  fclose(ifp);

  // And now we go read the index file
  rfp = fopen(readfile, "r");
  if (rfp == 0) {
    fprintf(stderr, "Could not open reads file");
    exit(-1);
  }
  // Read one line ("read") and try aligning it
  
  int naligned = 0;
  int nread = 0;
  while (!feof(rfp)) {
    // Align the read using mms and mms_mismatch (which is a sort of wrapper
    // for the correct calls to mms_continue)
    if (!fgets(buf, 256*256-1, rfp))
      break;
    nread++;
    if (buf[strlen(buf)-1] == '\n')
      buf[strlen(buf)-1] = 0;
    int len = strlen(buf);
    for (int i = 0; i < len; ++i) {
      // Replace with "compressed" characters
      switch(buf[i]) {
      case 'A':
	buf[i] = 0;
	revbuf[len-i-1] = 3;
	break;
      case 'C':
	buf[i] = 1;
	revbuf[len-i-1] = 2;
	break;
      case 'T':
	buf[i] = 3;
	revbuf[len-i-1] = 0;
	break;
      case 'G':
	buf[i] = 2;
	revbuf[len-i-1] = 1;
	break;
      default: // 'N'
	buf[i] = 5;
	revbuf[len-i-1] = 5;
	break;
      }
    }

    int aligned = 0;

    int score = 0;
    stack *s = stack_make();
    //    int thresh = (int) (-1.2 * (1+len));

    //    int pos = align_read(fmi, seq, buf, len, 10);
    int pos = align_read_anchored(fmi, seq, buf, len, 12, s);
    if (pos) {
      naligned++;
      printf("%d\n", pos + 1);
      stack_print_destroy(s);
    }
    else {
      stack_destroy(s);
      s = stack_make();
      //      pos = align_read(fmi, seq, revbuf, len, 10);
      pos = align_read_anchored(fmi, seq, revbuf, len, 12, s);
      if (pos) {
	naligned++;
	printf("%d\n", pos + 1);
	stack_print_destroy(s);
      }
      else {
	printf("0\n");
	stack_destroy(s);
      }
    }

    /*
    while(len) {
      if (score <= thresh) {
	break;
      }
      int start, end;
      int matched = mms(fmi, buf, len, &start, &end);
      if (matched < 10) {
      	len -= 1;
      	score -= 3;
      	continue;
      }
      // Try continuing from these results
      int res_len = len - matched;
      int tscore = score;
      while(res_len && tscore > thresh) {
	int penalty;
	int matched_cont = mms_mismatch(fmi, seq, buf, res_len, &start, &end, &penalty);
	//printf("%d\n", matched_cont);
	if (matched_cont == -1) {
	  tscore = thresh;
	  break; // too many matches
	}
	tscore += penalty;
	res_len -= matched_cont;
      }
      if (tscore <= thresh) {
	len -= 1;
	score -= 3;
	continue;
      }
      else {
	// we're good
	printf("%d\n", unc_sa(fmi, start) + 1);
	aligned = 1;
	naligned++;
	break;
      }
    }

    if (!aligned) {
      // Try aligning as a reverse complement
      int score = 0;
      while(len) {
	if (score <= thresh) {
	  printf("0\n");
	  break;
	}
	int start, end;
	int matched = mms(fmi, revbuf, len, &start, &end);
	//	printf("Matched %d\n", matched);
	if (matched < 10) {
	  len -= 1;
	  score -= 3;
	  continue;
	}
	// Try continuing from these results
	int res_len = len - matched;
	int tscore = score;
	while(res_len && tscore > thresh) {
	  int penalty;
	  int matched_cont = mms_mismatch(fmi, seq, revbuf, res_len, &start, &end, &penalty);
	  //printf("%d\n", matched_cont);
	  if (matched_cont == -1) {
	    tscore = thresh;
	    break; // too many matches
	  }
	  tscore += penalty;
	  res_len -= matched_cont;
	}
	if (tscore <= thresh) {
	  len -= 1;
	  score -= 3;
	  continue;
	}
	else {
	  // we're good
	  printf("%d\n", unc_sa(fmi, start) + 1);
	  naligned++;
	  break;
	}
      }
    }
    */
  }
  fclose(rfp);
  fprintf(stderr, "%d of %d reads aligned\n", naligned, nread);
  
  free(buf);
  free(revbuf);
  destroy_fmi(fmi);
  free(seq);
  return 0;
}
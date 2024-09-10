/*
  dpAlign_Local_DNA_MillerMyers uses Gotoh algorithm to find the 
  start points and end points of a local alignment. Then extracts
  the sequences within the end points to use Miller-Myers algorithm
  to run an global alignment for the subsequences to obtain the 
  actual alignment between the end points.
  It takes two character string sequences seq1 and seq2, together 
  with the scoring parameters for match, mismatch, gap opening and 
  gap extension as arguments. At the end, it returns the 
  dpAlign_AlignOutput data structure which can be translated into a 
  Bio::SimpleAlign object pretty easily.
 */
dpAlign_AlignOutput *
dpAlign_Local_DNA_MillerMyers(char * seq1, char * seq2, int match, int mismatch, int gap, int ext)
{
    sw_AlignStruct * as;
    int ** s;
    int i, j;

    if (seq1 == NULL)
	dpAlign_fatal("Sequence 1 is a NULL pointer!\n");
    if (seq2 == NULL)
	dpAlign_fatal("Sequence 2 is a NULL pointer!\n");

/* initialize DNA scoring matrix */
    s = (int **) malloc(17*sizeof(int *));
    if (s == NULL)
        dpAlign_fatal("Cannot allocate memory for scoring matrix row!\n");
    for (i = 0; i < 17; ++i) {
	s[i] = (int *) malloc(17*sizeof(int));
	if (s[i] == NULL)
	    dpAlign_fatal("Cannot allocate memory for scoring matrix col!\n");
        for (j = 0; j < 17; ++j) {
            if (i == 16 || j == 16) s[i][j] = mismatch; /* X mismatches all */
            else if (i == 15 || j == 15) s[i][j] = match; /* N matches all but X */
            else if (i == 14 && j != 0 || i != 0 && j == 14) s[i][j] = match; /* B is not A */
            else if (i == 13 && j != 3 && j != 4 || i != 3 && i != 4 && j == 13) s[i][j] = match; /* V is not T/U */
            else if (i == 12 && j != 2 || i != 2 && j == 12) s[i][j] = match; /* H is not G */
            else if (i == 11 && j != 1 || i != 1 && j == 11) s[i][j] = match; /* D is not C */
            else if (i == 10 && j != 0 && j != 1 && j != 7 || i != 0 && i != 1 && i != 7 && j == 10) s[i][j] = match; /* K is not A/C/M */
            else if (i == 9 && j != 0 && j != 3 && j != 4 && j != 8 || i != 0 && i != 3 && i != 4 && i != 8 && j == 9) s[i][j] = match; /* S is not T/U/A/W */
            else if (i == 8 && j != 1 && j != 2 && j != 9 || i != 1 && i != 2 && i != 9 && j == 10) s[i][j] = match; /* W is not G/C/S */
            else if (i == 7 && j != 2 && j != 3 && j != 4 && j != 10 || i != 2 && i != 3 && i != 4 && i != 10 && j == 7) s[i][j] = match; /* M is not T/U/G/K */
            else if (i == 3 && j == 4 || i == 4 && j == 3) s[i][j] = match; /* T matches U */ 
	    else if (i == j) s[i][j] = match;
            else s[i][j] = mismatch;
        }
    }

/* initialize the alignment data structure */
    as = init_AlignStruct(seq1, seq2, s, gap, ext);

/* uppercase the sequence and then encode it */
    for (i = 0; i < as->len1; ++i) {
	if (as->seq1[i] >= 'a' && as->seq1[i] <= 'z') as->seq1[i] -= 0x20;
        as->s1[i] = dna_encode(as->seq1[i]);
    }
    for (i = 0; i < as->len2; ++i) {
	if (as->seq2[i] >= 'a' && as->seq2[i] <= 'z') as->seq2[i] -= 0x20;
        as->s2[i] = dna_encode(as->seq2[i]);
    }

/* locate the end points of the subsequences that gives you the maximal 
   score */
    find_ends(as);

    if (as->score < 0)
	return NULL;

/* align the subsequences bounded by the end points */
    as->score = align(as->s1 + as->start1 - 1, as->s2 + as->start2 - 1, as->end1 - as->start1 + 1, as->end2 - as->start2 + 1, as->s, as->gap, as->ext, as->FF, as->RR, as->spc1, as->spc2);
    return traceback(as);
}
/* Function: EmitBestSequence()
 * Date:     SRE, Tue Nov 10 16:21:59 1998 [St. Louis]
 *
 * Purpose:  Given a model, emit the maximum probability sequence
 *           from it: argmax_{seq} P(seq | model).
 *           This is a sensible HMM equivalent to a "consensus"
 *           sequence.
 *           The model should be Plan7NakedConfig()'ed; 
 *           in particular, if we allowed B->M and M->E,
 *           the highest probability sequence would be
 *           artifactually short. (We could do the highest
 *           scoring sequence instead, to get around this problem,
 *           but the highest scoring sequence is prone to
 *           other artifacts -- any looping state N,C,J, or I
 *           with a positively scoring residue leads to
 *           an infinitely long "best scoring" sequence.)
 *
 * Args:     hmm     - the model
 *           ret_seq - RETURN: best sequence
 *           ret_L   - RETURN: length of sequence
 *           ret_tr  - RETURN: traceback of the model/seq alignment; or NULL.
 *
 * Returns:  void
 */
void
EmitBestSequence(struct plan7_s *hmm, char **ret_dsq, int *ret_L, struct p7trace_s **ret_tr)
{
  char              *seq;                  /* RETURN: best seq */
  struct p7trace_s  *tr;                   /* RETURN: traceback */
  float             *mmx, *imx, *dmx;      /* log P forward scores for M,D,I */
  char              *mtb, *itb, *dtb;      /* traceback ptrs for M,D,I */
  int  x;		        /* counter for symbols */
  int  k;			/* counter for nodes   */
  float sc;			/* tmp var for a log P */
  int  bestsym;
  int  rpos;			/* position in a sequence */
  int  tpos;			/* position in a trace */
  int  tlen;			/* length of the traceback */

  /* Initial allocations. We only need a 1D matrix and its shadow;
   * it's overkill to use the Plan7Matrix structures, so don't.
   */
  mmx = MallocOrDie(sizeof(float) * (hmm->M+1));
  imx = MallocOrDie(sizeof(float) * (hmm->M));
  dmx = MallocOrDie(sizeof(float) * (hmm->M));
  mtb = MallocOrDie(sizeof(char)  * (hmm->M+1));
  itb = MallocOrDie(sizeof(char)  * (hmm->M));
  dtb = MallocOrDie(sizeof(char)  * (hmm->M));

  /* Initialization. 
   * We can safely assume a max probability path of S->N->B->(M1 or D1),
   * so just init M1 and D1.
   */
  mmx[1] = log(hmm->xt[XTN][MOVE]) + log(1.F - hmm->tbd1);
  dmx[1] = 


  /* Main recursion, done as a push.
   * The model is used in probability form; no wing folding needed.
   */
  for (k = 1; k < hmm->M; k++)
    {
      /* Transits out of match state (init with these)
       */
      mmx[k+1] = mmx[k] + log(hmm->t[k][TMM]); mtb[k+1] = STM;
      dmx[k+1] = mmx[k] + log(hmm->t[k][TMD]); dtb[k+1] = STM;
      if (k < hmm->M-1) 
	imx[k]   = mmx[k] + log(hmm->t[k][TMI]); itb[k]   = STM;
      
      /* Transits out of delete state
       */
      if ((sc = dmx[k] + log(hmm->t[k][TDM])) > mmx[k+1]) 
	{ mmx[k+1] = sc; mtb[k+1] = STD; }
      if ((sc = dmx[k] + log(hmm->t[k][TDD])) > dmx[k+1])
	{ dmx[k+1] = sc; dtb[k+1] = STD; }

      /* Transits out of insert state (self-loops are never good)
       */
      if ((sc = imx[k] + log(hmm->t[k][TIM])) > mmx[k+1])
	{ mmx[k+1] = sc; mtb[k+1] = STI; }
      
      /* Best emissions
       */
      x = FMax(hmm->mat[k+1], Alphabet_size);
      mmx[k+1] += log(hmm->mat[k+1][x]);

      if (k < hmm->M-1) {
	x = FMax(hmm->ins[k+1], Alphabet_size);
	imx[k+1] += log(hmm->ins[k+1][x]);
      }
    }
}
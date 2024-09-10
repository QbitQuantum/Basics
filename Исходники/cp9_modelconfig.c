/* Function: CPlan9ELConfig()
 * Incept:   EPN, Tue Jun 19 09:50:52 2007
 * 
 * Purpose:  Turn EL local ends in a CM Plan 9 HMM on based on 
 *           the local end probs in the CM. 
 *           
 * Args:     cm     - the CM, must have valid CP9 HMM
 *                    
 * Return:   (void)
 *           HMM probabilities are modified.
 */
void
CPlan9ELConfig(CM_t *cm)
{
  /*printf("IN CPlan9ELConfig\n");*/
  /* Contract checks */
  if(cm->cp9 == NULL)
    cm_Fail("ERROR in CPlan9ELConfig, cm->cp9 is NULL.\n");
  if(cm->cp9map == NULL)
    cm_Fail("ERROR in CPlan9ELConfig, cm->cp9map is NULL.\n");
  if(!(cm->flags & CMH_CP9))
     cm_Fail("ERROR in CPlan9ELConfig, CMH_CP9 flag is down.");
  if(cm->cp9->flags & CPLAN9_EL)
     cm_Fail("ERROR in CPlan9ELConfig, CP9_EL flag is already up.");
  
  int v;
  int k;                     /* counter over HMM nodes */
  int nd;
  int seen_exit;
  float to_el_prob;
  float norm_factor;
  int   nexits;

  /* If the CM has local ends on, check to make sure all non-zero 
   * local end probabilities in the CM are identical (within reasonable 
   * precision), use that probability to set all HMM transitions to 
   * EL states.
   */
  if(cm->flags & CMH_LOCAL_END) { 
    seen_exit  = FALSE;
    to_el_prob = 0.;
    for(v = 0; v < cm->M; v++) {
      nd = cm->ndidx[v];
      if (((cm->ndtype[nd] == MATP_nd || cm->ndtype[nd] == MATL_nd ||
	  cm->ndtype[nd] == MATR_nd || cm->ndtype[nd] == BEGL_nd ||
	  cm->ndtype[nd] == BEGR_nd) && 
	 cm->ndtype[nd+1] != END_nd) && cm->nodemap[nd] == v) {
      /* this should have a non-zero local end probability */
      if(fabs(cm->end[v] - 0.) < 0.00001) /* non-zero */
	cm_Fail("In CPlan9ELConfig(), CM state %d should have non-zero local end prob, but it doesn't.\n", v);
      if(!seen_exit) {
	to_el_prob = cm->end[v];
	seen_exit  = TRUE;
      }
      else if(fabs(to_el_prob - cm->end[v]) > 0.00001)
	cm_Fail("In CPlan9ELConfig(), not all CM states EL probs are identical.\n");
      }
    }
    if(! seen_exit && cm->nodes != 3) cm_Fail("In CPlan9ELConfig(), CM_LOCAL_END flag up, cm->nodes != 3, but all CM local end probs are zero."); 
  }
  else {
    /* CM_LOCAL_END flag is down, local ends are off in the CM 
     * We figure out what the local end prob would be given cm->pend
     * and set the HMM local end probs based on that. 
     * First, count internal nodes MATP, MATL, MATR, BEGL, BEGR that aren't
     * adjacent to END nodes.
     */
    nexits = 0;
    for (nd = 1; nd < cm->nodes; nd++) {
      if ((cm->ndtype[nd] == MATP_nd || cm->ndtype[nd] == MATL_nd ||
	   cm->ndtype[nd] == MATR_nd || cm->ndtype[nd] == BEGL_nd ||
	   cm->ndtype[nd] == BEGR_nd) && 
	  cm->ndtype[nd+1] != END_nd)
	nexits++;
    } 
    to_el_prob = cm->pend / (float) nexits;
  }

  /* transitions from HMM node 0 to EL is impossible */
  cm->cp9->t[0][CTMEL] = 0.;
  for(k = 1; k <= cm->cp9->M; k++) 
    {
      if(cm->cp9->has_el[k])
	{
	  cm->cp9->t[k][CTMEL] = to_el_prob;
	  norm_factor = 1. - (cm->cp9->t[k][CTMEL] / (1. - cm->cp9->end[k]));
	  cm->cp9->t[k][CTMM] *= norm_factor;
	  cm->cp9->t[k][CTMI] *= norm_factor;
	  cm->cp9->t[k][CTMD] *= norm_factor;
	  /* cm->cp9->end[k] untouched */
	}
    }
  cm->cp9->flags &= ~CPLAN9_HASBITS;	/* clear the log-odds ready flag */

  CP9Logoddsify(cm->cp9);

  cm->cp9->flags |= CPLAN9_EL;          /* EL end locals now on */
  /*debug_print_cp9_params(cm->cp9);*/
  return;
}
static unsigned
decode_nd_tree (wfa_t *wfa, bitfile_t *input)
/*
 *  Read 'wfa' prediction tree of given 'input' stream.
 *
 *  No return value.
 *
 *  Side effects:
 *	'wfa->into' is filled with the decoded values
 */
{
   lqueue_t *queue;			/* queue of states */
   int       next, state;		/* state and its current child */
   unsigned  total = 0;			/* total number of predicted states */
   u_word_t  sum0, sum1;		/* Probability model */
   u_word_t  code;			/* The present input code value */
   u_word_t  low;			/* Start of the current code range */
   u_word_t  high;			/* End of the current code range */

   /*
    *  Initialize arithmetic decoder
    */
   code = get_bits (input, 16);
   low  = 0;
   high = 0xffff;
   sum0 = 1;
   sum1 = 11;

   queue = alloc_queue (sizeof (int));
   state = wfa->root_state;
   queue_append (queue, &state);

   /*
    *  Traverse the WFA tree in breadth first order (using a queue).
    */
   while (queue_remove (queue, &next))
   {
      unsigned label;

      if (wfa->level_of_state [next] > wfa->wfainfo->p_max_level + 1) 
      {
	 /*
	  *  Nondetermismn is not allowed at levels larger than
	  *  'wfa->wfainfo->p_max_level'.
	  */
	 for (label = 0; label < MAXLABELS; label++)
	    if (ischild (state = wfa->tree [next][label]))
	       queue_append (queue, &state); /* continue with childs */
      }
      else if (wfa->level_of_state [next] > wfa->wfainfo->p_min_level)
      {
	 for (label = 0; label < MAXLABELS; label++)
	    if (ischild (state = wfa->tree [next][label]))
	    {
	       unsigned count;		/* Current interval count */
	       unsigned range;		/* Current interval range */
	       
	       count = (((code - low) + 1) * sum1 - 1) / ((high - low) + 1);
	       if (count < sum0)
	       {
		  /*
		   *  Decode a '0' symbol
		   *  First, the range is expanded to account for the
		   *  symbol removal.
		   */
		  range = (high - low) + 1;
		  high = low + (u_word_t) ((range * sum0) / sum1 - 1 );
		  RESCALE_INPUT_INTERVAL;
		  /*
		   *  Update the frequency counts
		   */
		  sum0++;
		  sum1++;
		  if (sum1 > 50) /* scale the symbol frequencies */
		  {
		     sum0 >>= 1;
		     sum1 >>= 1;
		     if (!sum0)
			sum0 = 1;
		     if (sum0 >= sum1)
			sum1 = sum0 + 1;
		  }
		  if (wfa->level_of_state [state] > wfa->wfainfo->p_min_level)
		     queue_append (queue, &state);
	       }
	       else
	       {
		  /*
		   *  Decode a '1' symbol
		   *  First, the range is expanded to account for the
		   *  symbol removal.
		   */
		  range = (high - low) + 1;
		  high = low + (u_word_t) ((range * sum1) / sum1 - 1);
		  low  = low + (u_word_t) ((range * sum0) / sum1);
		  RESCALE_INPUT_INTERVAL;
		  /*
		   *  Update the frequency counts
		   */
		  sum1++;
		  if (sum1 > 50) /* scale the symbol frequencies */
		  {
		     sum0 >>= 1;
		     sum1 >>= 1;
		     if (!sum0)
			sum0 = 1;
		     if (sum0 >= sum1)
			sum1 = sum0 + 1;
		  }
		  append_edge (next, 0, -1, label, wfa);
		  total++;
	       }
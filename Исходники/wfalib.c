word_t *
compute_hits (unsigned from, unsigned to, unsigned n, const wfa_t *wfa)
/*
 *  Selects the 'n' most popular domain images of the given 'wfa'.
 *  Consider only linear combinations of state images
 *  {i | 'from' <= i <= 'to'}. I.e. domains are in {i | from <= i < 'to'}
 *  Always ensure that state 0 is among selected states even though from
 *  may be > 0.
 *  
 *  Return value:
 *	pointer to array of the most popular state images
 *	sorted by increasing state numbers and terminated by -1
 */
{
   word_t   *domains;
   unsigned  state, label, edge;
   int       domain;
   pair_t   *hits = Calloc (to, sizeof (pair_t));

   for (domain = 0; domain < (int) to; domain++)
   {
      hits [domain].value = domain;
      hits [domain].key   = 0;
   }
   
   for (state = from; state <= to; state++)
      for (label = 0; label < MAXLABELS; label++)
	 for (edge = 0; isedge (domain = wfa->into [state][label][edge]);
	      edge++)
	    hits [domain].key++;

   qsort (hits + 1, to - 1, sizeof (pair_t), sort_desc_pair);

   n       = min (to, n);
   domains = Calloc (n + 1, sizeof (word_t));

   for (domain = 0; domain < (int) n && (!domain || hits [domain].key);
	domain++)
      domains [domain] = hits [domain].value;
   if (n != domain)
      debug_message ("Only %d domains have been used in the luminance.",
		     domain);
   n = domain;
   qsort (domains, n, sizeof (word_t), sort_asc_word);
   domains [n] = -1;
   
   Free (hits);
   
   return domains;
}
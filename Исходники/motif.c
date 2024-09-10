/***********************************************************************
 * Free dynamic memory used by one motif. 
 ***********************************************************************/
void free_motif
  (MOTIF_T *a_motif)
{
  /* Don't bother with empty motifs. */
  if (a_motif == NULL) 
    return;

  // Reset all memeber values
  a_motif->id[0] = 0;
  a_motif->id2[0] = 0;
  a_motif->length = 0;
  a_motif->alph_size = 0;
  a_motif->ambigs = 0;
  a_motif->evalue = NaN();
  a_motif->num_sites = NaN();
  a_motif->complexity = NaN();
  free_matrix(a_motif->freqs);
  a_motif->freqs = NULL;
  free_matrix(a_motif->scores);
  a_motif->freqs = NULL;
  if (a_motif->url) free(a_motif->url);
  a_motif->url = NULL;
}
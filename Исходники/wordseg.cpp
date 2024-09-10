inT32 row_words2(                  //compute space size
                 TO_BLOCK *block,  //block it came from
                 TO_ROW *row,      //row to operate on
                 inT32 maxwidth,   //max expected space size
                 FCOORD rotation,  //for drawing
                 BOOL8 testing_on  //for debug
                ) {
  BOOL8 testing_row;             //contains testpt
  BOOL8 prev_valid;              //if decent size
  BOOL8 this_valid;              //current blob big enough
  inT32 prev_x;                  //end of prev blob
  inT32 min_width;               //min interesting width
  inT32 valid_count;             //good gaps
  inT32 total_count;             //total gaps
  inT32 cluster_count;           //no of clusters
  inT32 prev_count;              //previous cluster_count
  inT32 gap_index;               //which cluster
  inT32 smooth_factor;           //for smoothing stats
  BLOBNBOX *blob;                //current blob
  float lower, upper;            //clustering parameters
  ICOORD testpt;
  TBOX blob_box;                  //bounding box
                                 //iterator
  BLOBNBOX_IT blob_it = row->blob_list ();
  STATS gap_stats (0, maxwidth);
                                 //gap sizes
  float gaps[BLOCK_STATS_CLUSTERS];
  STATS cluster_stats[BLOCK_STATS_CLUSTERS + 1];
  //clusters

  testpt = ICOORD (textord_test_x, textord_test_y);
  smooth_factor =
    (inT32) (block->xheight * textord_wordstats_smooth_factor + 1.5);
  //      if (testing_on)
  //              tprintf("Row smooth factor=%d\n",smooth_factor);
  prev_valid = FALSE;
  prev_x = -MAX_INT16;
  testing_row = FALSE;
                                 //min blob size
  min_width = (inT32) block->pr_space;
  total_count = 0;
  for (blob_it.mark_cycle_pt (); !blob_it.cycled_list (); blob_it.forward ()) {
    blob = blob_it.data ();
    if (!blob->joined_to_prev ()) {
      blob_box = blob->bounding_box ();
      this_valid = blob_box.width () >= min_width;
      if (this_valid && prev_valid
      && blob_box.left () - prev_x < maxwidth) {
        gap_stats.add (blob_box.left () - prev_x, 1);
      }
      total_count++;             //count possibles
      prev_x = blob_box.right ();
      prev_valid = this_valid;
    }
  }
  valid_count = gap_stats.get_total ();
  if (valid_count < total_count * textord_words_minlarge) {
    gap_stats.clear ();
    prev_x = -MAX_INT16;
    for (blob_it.mark_cycle_pt (); !blob_it.cycled_list ();
    blob_it.forward ()) {
      blob = blob_it.data ();
      if (!blob->joined_to_prev ()) {
        blob_box = blob->bounding_box ();
        if (blob_box.left () - prev_x < maxwidth) {
          gap_stats.add (blob_box.left () - prev_x, 1);
        }
        prev_x = blob_box.right ();
      }
    }
  }
  if (gap_stats.get_total () == 0) {
    row->min_space = 0;          //no evidence
    row->max_nonspace = 0;
    return 0;
  }

  cluster_count = 0;
  lower = block->xheight * words_initial_lower;
  upper = block->xheight * words_initial_upper;
  gap_stats.smooth (smooth_factor);
  do {
    prev_count = cluster_count;
    cluster_count = gap_stats.cluster (lower, upper,
      textord_spacesize_ratioprop,
      BLOCK_STATS_CLUSTERS, cluster_stats);
  }
  while (cluster_count > prev_count && cluster_count < BLOCK_STATS_CLUSTERS);
  if (cluster_count < 1) {
    row->min_space = 0;
    row->max_nonspace = 0;
    return 0;
  }
  for (gap_index = 0; gap_index < cluster_count; gap_index++)
    gaps[gap_index] = cluster_stats[gap_index + 1].ile (0.5);
  //get medians
  if (testing_on) {
    tprintf ("cluster_count=%d:", cluster_count);
    for (gap_index = 0; gap_index < cluster_count; gap_index++)
      tprintf (" %g(%d)", gaps[gap_index],
        cluster_stats[gap_index + 1].get_total ());
    tprintf ("\n");
  }

  //Try to find proportional non-space and space for row.
  for (gap_index = 0; gap_index < cluster_count
    && gaps[gap_index] > block->max_nonspace; gap_index++);
  if (gap_index < cluster_count)
    lower = gaps[gap_index];     //most frequent below
  else {
    if (testing_on)
      tprintf ("No cluster below block threshold!, using default=%g\n",
        block->pr_nonsp);
    lower = block->pr_nonsp;
  }
  for (gap_index = 0; gap_index < cluster_count
    && gaps[gap_index] <= block->max_nonspace; gap_index++);
  if (gap_index < cluster_count)
    upper = gaps[gap_index];     //most frequent above
  else {
    if (testing_on)
      tprintf ("No cluster above block threshold!, using default=%g\n",
        block->pr_space);
    upper = block->pr_space;
  }
  row->min_space =
    (inT32) ceil (upper - (upper - lower) * textord_words_definite_spread);
  row->max_nonspace =
    (inT32) floor (lower + (upper - lower) * textord_words_definite_spread);
  row->space_threshold = (row->max_nonspace + row->min_space) / 2;
  row->space_size = upper;
  row->kern_size = lower;
  if (testing_on) {
    if (testing_row) {
      tprintf ("GAP STATS\n");
      gap_stats.print();
      tprintf ("SPACE stats\n");
      cluster_stats[2].print_summary();
      tprintf ("NONSPACE stats\n");
      cluster_stats[1].print_summary();
    }
    tprintf ("Row at %g has minspace=%d(%g), max_non=%d(%g)\n",
      row->intercept (), row->min_space, upper,
      row->max_nonspace, lower);
  }
  return 1;
}
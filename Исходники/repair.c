void uninitRepair (PROG_INFO *prog_struct, BLOCK_INFO *block_struct) {
  /*
  **  If output was sent to a file, then put an end of file marker
  **  on the prelude file and close both the seq and prel files.
  */
  if (prog_struct -> prel_file != NULL) {
    writeBits (prog_struct -> prel_file, 1, 1, R_FALSE);
    writeBits (prog_struct -> prel_file, 0, 0, R_FALSE);
    writeBits (prog_struct -> prel_file, 0, 0, R_FALSE);
    writeBits (prog_struct -> prel_file, 0, 0, R_TRUE);

    FCLOSE (prog_struct -> seq_file);
    FCLOSE (prog_struct -> prel_file);
    if (prog_struct -> prel_text_file != NULL) {
      FCLOSE (prog_struct -> prel_text_file);
    }

  }
  
#ifdef DEBUG
    fprintf (stderr, "\nOverall Statistics:\n\n");
    fprintf (stderr, "Input filename:  %s\n", prog_struct -> base_filename != NULL ? prog_struct -> base_filename : "N/A");
    fprintf (stderr, "Input file size:  %d\n", prog_struct -> base_filename != NULL ? prog_struct -> in_file_size : 0);
    fprintf (stderr, "Total number of phrases:  %d\n", prog_struct -> total_num_phrases);
    fprintf (stderr, "Total number of blocks:  %d\n", prog_struct -> total_blocks);
    fprintf (stderr, "Total sequence length:  %d\n", prog_struct -> total_num_symbols);
    if (prog_struct -> prel_text_file != NULL) {
      fprintf (stderr, "Average length of phrases:  %f per phrase\n", (R_DOUBLE) prog_struct -> total_sum_phrase_length / (R_DOUBLE) prog_struct -> total_num_phrases);
      fprintf (stderr, "The longest phrases was:\n");
      fprintf (stderr, "\tphrase number:  %d\n", prog_struct -> max_longest_phrase_num);
      fprintf (stderr, "\tblock number:  %d\n", prog_struct -> max_longest_phrase_block);
      fprintf (stderr, "\tphrase length:  %d\n", prog_struct -> max_longest_phrase_length);
    }

    fprintf (stderr, "\nMaximum for one phrase hierarchy:\n");
    fprintf (stderr, "\tNumber of primitives and phrases:  %d\n", prog_struct -> maximum_total_num_phrases);
    fprintf (stderr, "\tGeneration:  %d\n", prog_struct -> maximum_generations + 1);
                                   /*  Add 1 since generation is 0-based  */
    fprintf (stderr, "\tNumber of primitives:  %d\n", prog_struct -> maximum_primitives);
#endif

  /*  Must add 1 to maximum_generations since it is 0-based  */
  if (prog_struct -> verbose_level == R_TRUE) {
    fprintf (stderr, "-------------------------------------------------------------------------\n");
    fprintf (stderr, "%5u\t%5u\t%7u\t  %15u\t%11u\t%7u\n", prog_struct -> total_blocks, prog_struct -> total_num_prims, prog_struct -> total_num_phrases, prog_struct -> total_num_prims + prog_struct -> total_num_phrases, prog_struct -> maximum_generations + 1, prog_struct -> total_num_symbols);
  }

  wfree (prog_struct -> seq_nodelist);
  wfree (prog_struct -> progname);
  wfree (prog_struct -> base_filename);

  return;
}
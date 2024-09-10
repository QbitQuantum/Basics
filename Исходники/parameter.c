/* This procedure will dump the configuration data into an organized format,
   optionally into a file. Between the dumped data one may find the current
   date of the test and the output and input file name. For understand these
   lines, go through the printed strings. It can't be hard. */
void dump_config(FILE* fp, const parameter_t* par) 
{
  time_t current_time = time(NULL); /* just a dummy variable for timing */
  char temp[100]; /* for temporary strings */

  fprintf(fp, "-+- CONFIGURATION PARAMETERS\n");
  fprintf(fp, " +- Date: %s", ctime(&current_time));
  fprintf(fp, " +- Input File: %s\n", par->ifname);

  if (par->output_file)
    fprintf(fp, " +- Output File: %s.data \n", par->ofhint);
  else
    fprintf(fp, " +- Output File: [redirected to standard output]\n");

  fprintf(fp, " +- Output Information: ");
  if (par->dump_rings) fprintf(fp, "Rings\n");
  else if (par->dump_digis) fprintf(fp, "Digis\n");
  else if (par->dump_uniform_digis) fprintf(fp, "Uniform Digis\n");
  else fprintf(fp, "Uniform Rois\n");

  /* The type of dumped information and normalization */
  if (! par->dump_digis ) {
    fprintf(fp, " +- Uniformizing Selection: %s\n",
	    layer2string(&par->layer_flags,temp));
    if (! par->dump_uniform_digis ) {
      fprintf(fp, " +- Printing Selection: %s\n",
	      layer2string(&par->print_flags,temp));
      fprintf(fp, " +- Normalization: %s\n",
	      normalization2string(&par->normalization,temp));

      if ( normal_is_weighted_all(&par->normalization) ||
	   normal_is_weighted_seg(&par->normalization) ) {
	int i;
	fprintf(fp, " +- Stop Rings (Weighted Norm.): ");
	for (i=0; i<par->config_weighted.nlayers; ++i)
	  fprintf(fp, "%d ", par->config_weighted.last2norm[i]);
	fprintf(fp, "\n");
      }

      if ( par->max_radius > 0 )
	fprintf(fp, " +- Maximum normalization radius: %e\n", par->max_radius);
    }
  }

  /* The event accouting */
  fprintf(fp, " +- Event number dumping: %s\n", 
	  (par->dump_eventno)?"Yes":"No" );

  /* The event number filename */
  if (par->eventno_file && par->dump_eventno) {
    if (par->evfp != par->ofp)
      fprintf(fp, " +- Event-number File: %s.eventno \n", par->ofhint); 
    else
      fprintf(fp, " +- Event-number File: %s.data \n", par->ofhint);
  }

  /* The event number comment string, if it exists */
  if (strcmp(par->event_comment_str, "") != 0 )
    fprintf(fp, " +- Event number comment string: %s\n", 
	    par->event_comment_str);

  /* What types of energy are going to be printed */
  fprintf(fp, " +- Energy printing: %s\n", 
	  edump2string(&par->dump_energy,temp));

  /* The energy filename */
  if (par->energy_file && par->dump_energy) {
    if (par->efp != par->ofp)
      fprintf(fp, " +- Energy File: %s.energy \n", par->ofhint); 
    else 
      fprintf(fp, " +- Energy File: %s.data \n", par->ofhint);
  }

  /* The energy comment string, if it exists */
  if (strcmp(par->edump_comment_str, "") != 0 )
    fprintf(fp, " +- Energy comment string: %s\n", par->edump_comment_str);

  fprintf(fp, " +- Output Format: ");
  if (par->format_snns) {
    fprintf(fp, "SNNS\n");
    fprintf(fp, " +- Particle Type for SNNS targets: ");
    if (par->particle == JET) fprintf(fp, "Jet\n");
    else fprintf(fp, "Electron\n");
  }
  else fprintf(fp, "Raw\n");

  if (par->process_all_rois)
    fprintf(fp, " +- Processing: All Events\n");
  else
    fprintf(fp, " +- Processing: Event %ld, RoI %ld\n", 
	    par->event_no, par->roi_no);
  
  fprintf(fp, " +- Verbose output: %s\n", (par->verbose)?"YES":"NO");

  if (par->run_fast)
    fprintf(fp, " +- Fast Processing: YES (using obstacks)\n");
  else
    fprintf(fp, " +- Fast Processing: NO (using common files)\n");

  fprintf(fp, " +- Number of events per DB read in: %ld", par->load_events);
  fprintf(fp, " (total no. of events could be less)\n");

  fprintf(fp, "==========================================\n");

  /* close the configuration file pointer, so, no need to do it
     afterwards. This can only be done *IF* the pointer is *NOT* a pointer to
     stdout or to a common output file! */
  if (fp != stdout || fp != par->ofp) fclose(fp);
  
}
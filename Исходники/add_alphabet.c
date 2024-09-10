int main(int argc, char* argv[])
{
  int i;
  FILE *hmmfile, *outfile, *alphafile, *outfile_tmp;
  int nr_alphabets;
  int alphabet_nr;
  int hmmfiletype;

  struct gengetopt_args_info args_info;

  hmmfile = NULL;
  outfile = NULL;
  alphafile = NULL;
  outfile_tmp = NULL;
  verbose = NO;
  
  /* parse command line */

  if(cmdline_parser(argc, argv, &args_info) != 0) {
    exit(1);
  }
  
  /* compulsory options */
  if(args_info.hmminfile_given) {
    if((hmmfile = fopen(args_info.hmminfile_arg, "r")) == NULL) {
      perror(args_info.hmminfile_arg);
      exit(0);

    }
    else {
      printf("Opened file %s for reading model file\n",args_info.hmminfile_arg);
    }
  }
  if(args_info.outfile_given) {
    if((outfile = fopen(args_info.outfile_arg, "w")) == NULL) {
      perror(args_info.outfile_arg);
      exit(0);
    }
    else {
      printf("Opened file %s for writing\n",args_info.outfile_arg);
    }
  }
  

  
  if(args_info.alphafile_given) {
    if((alphafile = fopen(args_info.alphafile_arg, "r")) == NULL) {
      perror(args_info.alphafile_arg);
      exit(0);
    }
    else {
      printf("Opened file %s for reading alphabet file\n",args_info.alphafile_arg);
    }
  }
  
  if(args_info.verbose_given) {
    verbose = YES;
  }
  
  
  /* find out nr of alphabets */
  nr_alphabets = get_nr_alphabets(hmmfile);
  rewind(hmmfile);
  

  
  /* get hmm from file */
  printf("starting reading\n");  
  if(hmmfile != NULL) {
    hmmfiletype = readhmm_check(hmmfile);
    if(hmmfiletype == SINGLE_HMM) {
      readhmm(hmmfile, &hmm);
    }
    else if(hmmfiletype == MULTI_HMM) {
      readhmm_multialpha(hmmfile, &hmm);
    }
  }
  else {
    /* cannot happen */
    printf("Internal error: hmmfile not found, should have been detected earlier\n");
  }



  /* read additional alphabet info */
  if(hmm.nr_alphabets > 3) {
    printf("Error: maximum number of alphabets is 4\n");
    exit(0);
  }
  else {
    alphabet_nr = hmm.nr_alphabets + 1;
    read_additional_alphabet(alphafile, &hmm, alphabet_nr);
  }
  


  /* save adjusted hmm */
  printf("finished reading, starting save\n");
  savehmm_multialpha(outfile, &hmm);
  printf("finished save\n");
  

  /* garbage collection */
  hmm_garbage_collection_multi(hmmfile, &hmm);
  fclose(outfile);
  fclose(alphafile);
 
  /*****************************************************************************************/
  /* remember that garbage collection has not been done here */

}
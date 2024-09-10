void model3::viterbi_loop(Perplexity& perp, Perplexity& viterbiPerp, sentenceHandler& sHandler1, 
			   bool dump_files, const char* alignfile, 
			   bool collect_counts, string model )
{
  WordIndex i, j, l, m ;
  ofstream of2 ;
  int pair_no;
  LogProb temp;

  if (dump_files)
    of2.open(alignfile);
  pair_no = 0 ; // sentence pair number 
  // for each sentence pair in the corpus
  perp.clear() ; // clears cross_entrop & perplexity 
  viterbiPerp.clear();
  sentPair sent ;
  while(sHandler1.getNextSentence(sent)){
    Vector<WordIndex>& es = sent.eSent;
    Vector<WordIndex>& fs = sent.fSent;
    const float count  = sent.getCount();
    if ((sent.sentenceNo % 1000) == 0)
      cerr <<sent.sentenceNo << '\n'; 
    time_t sent_s = time(NULL) ;
    pair_no++ ;
    l = es.size() - 1 ;
    m = fs.size() - 1 ;
    if (Log){
      logmsg << "Processing sentence pair:\n\t";
      printSentencePair(es, fs, logmsg);
      for (i = 0 ; i <= l ; i++)
	  logmsg << Elist.getVocabList()[es[i]].word << " ";
	logmsg << "\n\t";
	for (j = 1 ; j <= m ; j++)
	  logmsg << Flist.getVocabList()[fs[j]].word << " ";
	logmsg << "\n";
      } 

      LogProb align_total_count=0;
      //      LogProb best_score;

      Vector<WordIndex> viterbi_alignment;
      LogProb  viterbi_score ;
      alignmodel neighborhood;
      neighborhood.clear();
      align_total_count = 0;
      findAlignmentsNeighborhood(/*tTable, aTable,*/ /*p1_count, p0_count,*/ es, fs, align_total_count, neighborhood) ;
      if (Peg){
	for (i = 0 ; i <= l ; i++)
	  for (j = 1 ; j <= m ; j++){
	    if ( (tTable.getProb(es[i], fs[j]) > PROB_SMOOTH) &&
		 (aTable.getValue(i, j, l, m) > PROB_SMOOTH) &&
		 (dTable.getValue(j, i, l, m) > PROB_SMOOTH))
	      findAlignmentsNeighborhood(/*tTable, aTable,*/ /*p1_count, 
							   p0_count, */ es, fs, align_total_count, neighborhood, i, j);  
	  }
      }
      //  Now Collect counts over saved neighborhoods
      viterbi_score = 0 ;
      if (Verbose)
	cerr << "\nCollecting counts over found alignments, total prob: " 
	     << align_total_count <<  "\n";
      if (Log)
	logmsg << "\nCollecting counts over found alignments, total prob: " 
	       << align_total_count <<  "\n";
      hash_map<Vector<WordIndex>, LogProb, hashmyalignment, equal_to_myalignment >::iterator align ;
      int acount = 0 ;
      if (align_total_count == 0 ){
	cerr << " WARNINIG: For the following sentence pair : \n";
	printSentencePair(es, fs, cerr);
	cerr << "The collection of alignments found have 0 probability!!\n";
	cerr << "No counts will be collected of it \n";
	if (Log){
	  logmsg << "The collection of alignments found have 0 probability!!\n";
	  logmsg << "No counts will be collected of it \n";
	}
      }
      else {
	if (collect_counts) {
	  for(align = neighborhood.begin(); align != neighborhood.end(); align++){
	    temp = (*align).second/align_total_count ;	  
	    collectCountsOverAlignement(/*tTable, aCountTable, */es, fs, /*p1_count, 
					  p0_count ,*/ ((*align).first), temp , count);
	    acount++;
	    if (viterbi_score < temp){
	      viterbi_alignment = ((*align).first);
	      viterbi_score = temp;
	    }
	  }
	} // end of if (collect_counts)
	perp.addFactor(log(double(align_total_count)), count, l, m,0);
	viterbiPerp.addFactor(log(double(viterbi_score)), count, l, m,0);
	
      if (Verbose){
	cerr << "Collected counts over "<<acount <<" (of "
	     << pow(double(m), double(l+1)) <<") differnet alignments\n";
	cerr << "Bucket count of alignments hash: "<<
	  neighborhood.getHash().bucket_count()<< ", size " <<
	  neighborhood.getHash().size() << "\n";
	}
	if (Log){
	  logmsg << "Collected counts over "<<acount <<" (of "
		 << pow(double(m), double(l+1)) <<") differnet alignments\n";
	  logmsg << "Bucket count of alignments hash: "<<
	    neighborhood.getHash().bucket_count()<< "\n";
	}
      } // end of else 
      // write best alignment (viterbi) for this sentence pair to alignment file 
      if (collect_counts){
	if (viterbi_score <= 0){
	  cerr << "Viterbi Alignment for this pair have score zero!!\n";
	  of2 << "\n\n";
	}
	else {
	  if (dump_files)
	    printAlignToFile(es, fs, Elist.getVocabList(), Flist.getVocabList(), of2, viterbi_alignment, pair_no, viterbi_score);
	  addAL(viterbi_alignment,sent.sentenceNo,l);
	}
      } // end of if (collect_counts) 
      double period = difftime(time(NULL), sent_s);
      if (Log)
      	logmsg << "processing this sentence pair ("<<l+1<<"x"<<m<<") : "<<
      	  (l+1)*m << " took : " << period << " seconds\n";
      if (Verbose)
	cerr << "processing this sentence pair took : " << period
	     << " seconds\n";
      
    } /* of sentence pair E, F */
    sHandler1.rewind();
    errorReportAL(cerr,model);
    perp.record(model);
    viterbiPerp.record(model);
    if (dump_files)
      of2.close();

}
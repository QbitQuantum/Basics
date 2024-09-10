void model1::em_loop(int it,Perplexity& perp, sentenceHandler& sHandler1, bool seedModel1, 
		     bool dump_alignment, const char* alignfile, Dictionary& dict, bool useDict, Perplexity& viterbi_perp, bool test)
{
  WordIndex i, j, l, m ;
  double cross_entropy;
  int pair_no=0 ;
  perp.clear();
  viterbi_perp.clear();
  ofstream of2;
  // for each sentence pair in the corpus
  if (dump_alignment||FEWDUMPS)
    of2.open(alignfile);
  cerr <<" number of French (target) words = " << noFrenchWords << endl;
  PROB uniform = 1.0/noFrenchWords ;
  cerr << "initial unifrom prob = " << uniform << endl;
  sentPair sent ;
  sHandler1.rewind();
  while(sHandler1.getNextSentence(sent)){
    Vector<WordIndex>& es = sent.eSent;
    Vector<WordIndex>& fs = sent.fSent;
    const float so  = sent.getCount(); // number of times sentence occurs in corpus
    //std::cerr << "\n\nNEW sentence (#" << (pair_no + 1) << ") with count = " << so << endl;
    l = es.size() - 1;  // source length
    m = fs.size() - 1;  // target length
    cross_entropy = log(1.0);
    Vector<WordIndex> viterbi_alignment(fs.size());
    double viterbi_score = 1 ;

    /*mebool eindict[l + 1];
    bool findict[m + 1];
    bool indict[m + 1][l + 1];
    if(it == 1 && useDict){
      for(unsigned int dummy = 0; dummy <= l; dummy++) eindict[dummy] = false;
      for(unsigned int dummy = 0; dummy <= m; dummy++){
	findict[dummy] = false;
	for(unsigned int dummy2 = 0; dummy2 <= l; dummy2++) 
	  indict[dummy][dummy2] = false;
      }
      for(j = 0; j <= m; j++)
	for(i = 0; i <= l; i++)
	  if(dict.indict(fs[j], es[i])){
	    eindict[i] = findict[j] = indict[j][i] = true;
	  }
    }me*/

    for(j=1; j <= m; j++){
      //cerr << "Current french (TARGET) word = " << fs[j] << endl;
      // entries  that map fs to all possible ei in this sentence.
      Vector<LpPair<COUNT,PROB> *> sPtrCache(es.size(),0); // cache pointers to table 
      LpPair<COUNT,PROB> **sPtrCachePtr;

      PROB denom = 0.0;
      WordIndex best_i = 0 ; // i for which fj is best maped to ei
      PROB word_best_score = 0 ;  // score for the best mapping of fj
      if (it == 1 && !seedModel1){
        //cerr << "Using uniform denominator\n";
	denom = uniform  * es.size() ;
	word_best_score = uniform ;
      }
      else 
	for((i=0),(sPtrCachePtr=&sPtrCache[0]); i <= l; i++,sPtrCachePtr++){
          //cerr << "current english (SOURCE) word = " << es[i] << endl;
	  PROB e(0.0) ;
          srcHits_.insert(es[i]);
	  (*sPtrCachePtr) = tTable.getPtr(es[i], fs[j]) ;
	  if ((*sPtrCachePtr) != 0 && (*((*sPtrCachePtr))).prob > PROB_SMOOTH) 
	    e = (*((*sPtrCachePtr))).prob;
	  else e = PROB_SMOOTH ;
	  denom += e  ;
	  if (e > word_best_score){
	    word_best_score = e ;
	    best_i = i ;
	  }	
        }
      viterbi_alignment[j] = best_i ;
      viterbi_score *= word_best_score ; /// denom ;
      if (denom == 0){
	if (test)
	  cerr << "WARNING: denom is zero (TEST)\n";
	else 
	  cerr << "WARNING: denom is zero (TRAIN)\n";
      }
      cross_entropy += log(denom) ;
      if (!test){
	if(denom > 0){	  
	  COUNT val = COUNT(so) / (COUNT) double(denom) ;
	  /* this if loop implements a constraint on counting:
	     count(es[i], fs[j]) is implemented if and only if
	     es[i] and fs[j] occur together in the dictionary, 
	     OR
	     es[i] does not occur in the dictionary with any fs[x] and
	     fs[j] does not occur in the dictionary with any es[y]
	  */
	  /*meif(it == 1 && useDict){
	    for((i=0),(sPtrCachePtr=&sPtrCache[0]); i <= l; i++,sPtrCachePtr++){
	      if(indict[j][i] || (!findict[j] && !eindict[i])){
		PROB e(0.0) ;
		if (it == 1 && !seedModel1)
		  e =  uniform  ;
		else if ((*sPtrCachePtr) != 0 &&  (*((*sPtrCachePtr))).prob > PROB_SMOOTH) 
		  e = (*((*sPtrCachePtr))).prob;
		else e = PROB_SMOOTH ;
		COUNT x=e*val;
		if( it==1||x>MINCOUNTINCREASE )
		  if ((*sPtrCachePtr) != 0)
		    (*((*sPtrCachePtr))).count += x;
		  else 	      
		    tTable.incCount(es[i], fs[j], x);
	      } 
	    } 	  } 
	  // Old code:
	  else{me*/
	    for((i=0),(sPtrCachePtr=&sPtrCache[0]); i <= l; i++,sPtrCachePtr++){
	      //for(i=0; i <= l; i++) {	    
	      PROB e(0.0) ;
	      if (it == 1 && !seedModel1)
		e =  uniform  ;
	      else if ((*sPtrCachePtr) != 0 &&  (*((*sPtrCachePtr))).prob > PROB_SMOOTH) 
		e = (*((*sPtrCachePtr))).prob;
	      else e = PROB_SMOOTH ;
	      //if( !(i==0) )
	      //cout << "COUNT(e): " << e << " " << MINCOUNTINCREASE << endl;
	      COUNT x=e*val;  // new count
	      if( pair_no==VerboseSentence )
		cout << i << "(" << evlist[es[i]].word << ")," << j << "(" << fvlist[fs[j]].word << ")=" << x << endl;
	      if( it==1||x>MINCOUNTINCREASE ) {
                if(step_k != 0) tTable.stepCounts_[wordPairIds(es[i], fs[j])] += x;
                else if( NoEmptyWord==0 || i!=0 )
		  if ((*sPtrCachePtr) != 0){ 
                    // handles single sentence updates
                    //x = getInterpolatedCount(x, (*((*sPtrCachePtr))).count); // get interpolated count here
		    (*((*sPtrCachePtr))).count += x;
                  }
		  else {	      
                    //x = getInterpolatedCount(x, (*((*sPtrCachePtr))).count); // get interpolated count here
		    tTable.incCount(es[i], fs[j], x);
                  }
                // increment temp table instead
              }
	    } /* end of for i */
	  //me} // end of else
	} // end of if (denom > 0)
      }// if (!test)
    } // end of for all (j) target words;
    sHandler1.setProbOfSentence(sent,cross_entropy);
    //cerr << sent << "CE: " << cross_entropy << " " << so << endl;
    perp.addFactor(cross_entropy-m*log(l+1.0), so, l, m,1);
    viterbi_perp.addFactor(log(viterbi_score)-m*log(l+1.0), so, l, m,1);
    if (dump_alignment||(FEWDUMPS&&sent.sentenceNo<1000))
      printAlignToFile(es, fs, evlist, fvlist, of2, viterbi_alignment, sent.sentenceNo, viterbi_score);
    addAL(viterbi_alignment,sent.sentenceNo,l);
    pair_no++;
  } /* of while */
  sHandler1.rewind();
  perp.record("Model1");
  viterbi_perp.record("Model1");
  errorReportAL(cout, "IBM-1");
}
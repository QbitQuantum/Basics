void hmm::em_loop(Perplexity& perp, sentenceHandler& sHandler1, 
		  bool dump_alignment, const char* alignfile, Perplexity& viterbi_perp, 
		     bool test,bool doInit,int 
)
{
  WordIndex i, j, l, m ;
  double cross_entropy;
  int pair_no=0 ;
  perp.clear();
  viterbi_perp.clear();
  ofstream of2;
  // for each sentence pair in the corpus
  if (dump_alignment||FEWDUMPS )
    of2.open(alignfile);
  sentPair sent ;
  sHandler1.rewind();
  while(sHandler1.getNextSentence(sent)){
    const Vector<WordIndex>& es = sent.get_eSent();
    const Vector<WordIndex>& fs = sent.get_fSent();
    const float so  = sent.getCount();
    l = es.size() - 1;
    m = fs.size() - 1;
    cross_entropy = log(1.0);
    Vector<WordIndex> viterbi_alignment(fs.size());

    unsigned int I=2*l,J=m;
    bool DependencyOfJ=(CompareAlDeps&(16|8))||(PredictionInAlignments==2);
    bool DependencyOfPrevAJ=(CompareAlDeps&(2|4))||(PredictionInAlignments==0);
    HMMNetwork *net=makeHMMNetwork(es,fs,doInit);
    Array<double> gamma;
    Array<Array2<double> > epsilon(DependencyOfJ?(m-1):1);
    double trainProb;
      trainProb=ForwardBackwardTraining(*net,gamma,epsilon);
    if( !test )
      {
      /*  bool eIsPunct[l + 1];
        bool fIsPunct[m + 1];

        for(unsigned int dummy = 0; dummy <= l; dummy++) {
           eIsPunct[dummy] = isPunctuation(evlist[es[dummy]].word);
        }
        for(unsigned int dummy = 0; dummy <= m; dummy++){
           fIsPunct[dummy] = isPunctuation(fvlist[fs[dummy]].word);
        }*/
	double *gp=conv<double>(gamma.begin());
	for(unsigned int i2=0;i2<J;i2++)for(unsigned int i1=0;i1<I;++i1,++gp)
	  if( *gp>MINCOUNTINCREASE )
	    {
	      COUNT add= *gp*so;
	      if( i1>=l )
		{
		  tTable.incCount(es[0],fs[1+i2],add);
		  aCountTable.getRef(0,i2+1,l,m)+=add;
		}
          else //if((eIsPunct[i1 + 1] && fIsPunct[i2 + 1] && evlist[es[i1 + 1]].word == fvlist[fs[i2 + 1]].word) || (!eIsPunct[i1 + 1] && !fIsPunct[i2 + 1]) )

		{
		  tTable.incCount(es[1+i1],fs[1+i2],add);
		  aCountTable.getRef(1+i1,1+i2,l,m)+=add;
		}
	    }
	double p0c=0.0,np0c=0.0;
	for(unsigned int jj=0;jj<epsilon.size();jj++)
	  {
	    int frenchClass=fwordclasses.getClass(fs[1+min(int(m)-1,int(jj)+1)]);
	    double *ep=epsilon[jj].begin();
	    if( ep )
	      {
		//for(i=0;i<I;i++)
		//  normalize_if_possible_with_increment(ep+i,ep+i+I*I,I);
		//		for(i=0;i<I*I;++i)
		//  ep[i] *= I;
		//if( DependencyOfJ )
		//  if( J-1 )
		//    for(i=0;i<I*I;++i)
		//      ep[i] /= (J-1);
		double mult=1.0;
		mult*=l;
		//if( DependencyOfJ && J-1)
		//  mult/=(J-1);
		for(i=0;i<I;i++)
		  {
		    for(unsigned int i_bef=0;i_bef<I;i_bef++,ep++)
		      {
			CLASSIFY(i,i_empty,ireal);
			CLASSIFY2(i_bef,i_befreal);
			if( i_empty )
			  p0c+=*ep * mult;
			else
			  {
			    counts.addAlCount(i_befreal,ireal,l,m,ewordclasses.getClass(es[1+i_befreal]),
					      frenchClass ,jj+1,*ep * mult,0.0);
			    np0c+=*ep * mult; 
			  }
			massert( &epsilon[jj](i,i_bef)== ep);
		      }
		  }
	      }
	  }
	double *gp1=conv<double>(gamma.begin()),*gp2=conv<double>(gamma.end())-I;
	Array<double>&ai=counts.doGetAlphaInit(I);
	Array<double>&bi=counts.doGetBetaInit(I);
	int firstFrenchClass=(fs.size()>1)?(fwordclasses.getClass(fs[1+0])):0;
	for(i=0;i<I;i++,gp1++,gp2++)
	  {
	    CLASSIFY(i,i_empty,ireal);
	    ai[i]+= *gp1;
	    bi[i]+= *gp2;
	    if( DependencyOfPrevAJ==0 )
	      {
		if( i_empty )
		  p0c+=*gp1;
		else
		  {
		    counts.addAlCount(-1,ireal,l,m,0,firstFrenchClass,0,*gp1,0.0);
		    np0c+=*gp1;
		  }
	      }
	  }
    if( Verbose )
      cout << "l: " << l << "m: " << m << " p0c: " << p0c << " np0c: " << np0c << endl;
      }
    cross_entropy+=log(max(trainProb,1e-100))+log(max(net->finalMultiply,1e-100));
    Array<int>vit;
    double viterbi_score=1.0;
    if( (HMMTrainingSpecialFlags&1) )
      HMMViterbi(*net,gamma,vit);
    else
      viterbi_score=HMMRealViterbi(*net,vit);
    for(j=1;j<=m;j++)
      {
	viterbi_alignment[j]=vit[j-1]+1;
	if( viterbi_alignment[j]>l)
	  viterbi_alignment[j]=0;
      }
    sHandler1.setProbOfSentence(sent,cross_entropy);
    perp.addFactor(cross_entropy, so, l, m,1);
    viterbi_perp.addFactor(log(viterbi_score)+log(max(net->finalMultiply,1e-100)), so, l, m,1);
    if( Verbose )
      cout << "Viterbi-perp: " << log(viterbi_score) << ' ' << log(max(net->finalMultiply,1e-100)) << ' ' << viterbi_score << ' ' << net->finalMultiply << ' ' << *net << "gamma: " << gamma << endl;
    delete net;net=0;
    if (dump_alignment||(FEWDUMPS&&sent.getSentenceNo()<1000) )
      printAlignToFile(es, fs, Elist.getVocabList(), Flist.getVocabList(), of2, viterbi_alignment, sent.getSentenceNo(), viterbi_score);
    addAL(viterbi_alignment,sent.getSentenceNo(),l);    
    pair_no++;
  } /* of while */
  sHandler1.rewind();
  perp.record("HMM");
  viterbi_perp.record("HMM");
  errorReportAL(cout,"HMM");
}
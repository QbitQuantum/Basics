void M2MFstAligner::Sequences2FSTNoInit( VectorFst<LogArc>* fst, vector<string>* seq1, vector<string>* seq2 ){
  /*
    Build an FST that represents all possible alignments between seq1 and seq2, given the 
     parameter values input by the user.  Here we encode the input and output labels, in fact
     creating a WFSA.  This simplifies the training process, but means that we can only 
     easily compute a joint maximization.  In practice joint maximization seems to give the 
     best results anyway, so it probably doesn't matter.
  */
  int istate=0; int ostate=0;
  for( unsigned int i=0; i<=seq1->size(); i++ ){
    for( unsigned int j=0; j<=seq2->size(); j++ ){
      fst->AddState();
      istate = i*(seq2->size()+1)+j;

      //Epsilon arcs for seq1
      if( seq1_del==true )
	for( unsigned int l=1; l<=seq2_max; l++ ){
	  if( j+l<=seq2->size() ){
	    vector<string> subseq2( seq2->begin()+j, seq2->begin()+j+l );
	    int is = isyms->Find(skip+s1s2_sep+vec2str(subseq2, seq2_sep));
	    ostate = i*(seq2->size()+1) + (j+l);
	    LogArc arc( is, is, alignment_model[is], ostate );
	    _compute_penalties( arc.ilabel, 1, l, true, false );
	    fst->AddArc( istate, arc );
	  }
	}

      //Epsilon arcs for seq2
      if( seq2_del==true )
	for( unsigned int k=1; k<=seq1_max; k++ ){
	  if( i+k<=seq1->size() ){
	    vector<string> subseq1( seq1->begin()+i, seq1->begin()+i+k );
	    int is = isyms->Find(vec2str(subseq1, seq1_sep)+s1s2_sep+skip);
	    ostate = (i+k)*(seq2->size()+1) + j;
	    LogArc arc( is, is, alignment_model[is], ostate );
	    _compute_penalties( arc.ilabel, k, 1, false, true );
	    fst->AddArc( istate, arc );
	  }
	}

      //All the other arcs
      for( unsigned int k=1; k<=seq1_max; k++ ){
	for( unsigned int l=1; l<=seq2_max; l++ ){
	  if( i+k<=seq1->size() && j+l<=seq2->size() ){
	    vector<string> subseq1( seq1->begin()+i, seq1->begin()+i+k );
	    string s1 = vec2str(subseq1, seq1_sep);
	    vector<string> subseq2( seq2->begin()+j, seq2->begin()+j+l );
	    string s2 = vec2str(subseq2, seq2_sep);
	    if( restrict==true && l>1 && k>1)
	      continue;
	    int is = isyms->Find(s1+s1s2_sep+s2);
	    ostate = (i+k)*(seq2->size()+1) + (j+l);
	    LogArc arc( is, is, alignment_model[is], ostate );
	    _compute_penalties( arc.ilabel, k, l, false, false );
	    fst->AddArc( istate, arc );
	  }
	}
      }

    }
  }

  fst->SetStart(0);
  fst->SetFinal( ((seq1->size()+1)*(seq2->size()+1))-1, LogWeight::One() );
  //Unless seq1_del==true && seq2_del==true we will have unconnected states
  // thus we need to run connect to clean out these states
  if( seq1_del==false || seq2_del==false )
    Connect(fst);
  return;
}
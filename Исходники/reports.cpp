void printOverlapReport(const tmodel<COUNT, PROB>& tTable, 
			sentenceHandler& testHandler,  vcbList& trainEList, 
			vcbList& trainFList, vcbList& testEList, vcbList& testFList)
{
  set<pair<WordIndex, WordIndex> > testCoocur ;
  sentPair s ;
  /*  string unseenCoocurFile = Prefix + ".tst.unseen.cooc" ;
      ofstream of_unseenCoocur(unseenCoocurFile.c_str());
      
      string seenCoocurFile = Prefix + ".tst.seen.cooc" ;
      ofstream of_seenCoocur(seenCoocurFile.c_str());
  */  
  testHandler.rewind();
  int seen_coocur = 0, unseen_coocur = 0, srcUnk = 0, trgUnk = 0 ;
  while(testHandler.getNextSentence(s)){    
    for (WordIndex i = 1 ; i < s.eSent.size() ; i++)
      for (WordIndex j = 1 ; j < s.fSent.size() ; j++)	
	testCoocur.insert(pair<WordIndex, WordIndex> (s.eSent[i], s.fSent[j])) ;
  }
  set<pair<WordIndex, WordIndex> >::const_iterator i ;
  for (i = testCoocur.begin() ; i != testCoocur.end() ; ++i){
    if (tTable.getProb((*i).first, (*i).second) > PROB_SMOOTH){
      seen_coocur ++ ;
      //      of_seenCoocur << (*i).first << ' ' << (*i).second << '\n';
    }
    else {
      unseen_coocur++;
      //      of_unseenCoocur << (*i).first << ' ' << (*i).second << '\n';
    }
  }
  
  string trgUnkFile = Prefix + ".tst.trg.unk" ;
  ofstream of_trgUnk(trgUnkFile.c_str());

  for (WordIndex i = 0 ; i <  testFList.getVocabList().size() && i < testFList.uniqTokens();i++)
    if (testFList.getVocabList()[i].freq > 0 && trainFList.getVocabList()[i].freq <= 0){
      of_trgUnk << i << ' ' << testFList.getVocabList()[i].word << ' ' << testFList.getVocabList()[i].freq
		<< '\n';
      trgUnk++ ;
    }
  string srcUnkFile = Prefix + ".tst.src.unk" ;
  ofstream of_srcUnk(srcUnkFile.c_str());

  for (WordIndex j = 0 ; j <  testEList.getVocabList().size() && j < testEList.uniqTokens();j++)
    if (testEList.getVocabList()[j].freq > 0 && trainEList.getVocabList()[j].freq <= 0){
      srcUnk++ ;
      of_srcUnk << j << ' ' << testEList.getVocabList()[j].word << ' ' << testEList.getVocabList()[j].freq
		<< '\n';
    }
  string summaryFile = Prefix + ".tst.stats" ;  
  ofstream of_summary(summaryFile.c_str());
  of_summary << "\t\t STATISTICS ABOUT TEST CORPUS\n\n";
  of_summary << "source unique tokens: " <<  testEList.uniqTokens() << '\n';
  of_summary << "target unique tokens: " <<  testFList.uniqTokens() << '\n';
  of_summary << "unique unseen source tokens: " << srcUnk << '\n';
  of_summary << "unique unseen target tokens: " << trgUnk << '\n';
  of_summary << "cooccurrences not found in the final t table: " << unseen_coocur << '\n';
  of_summary << "cooccurrences found in the final t table: " << seen_coocur << '\n';
  
}
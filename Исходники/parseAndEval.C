/* the function called by each thread is "mainLoop" */
void*
mainLoop(void* arg)
{
  loopArg *loopA = (loopArg*)arg;
  istream* testSStream = loopA->inpt;
  ostream* pstatStream = loopA->outpt;
  int id = loopA->id;
  double log600 = log2(600.0);
  PrintStack printStack;
  for( ;  ; )
    {
      InputTree     correct;  
      InputTree*    cuse;

      /* first lock to read in the material */
      pthread_mutex_lock(&readlock);
      if( !*testSStream ) {
	pthread_mutex_unlock(&readlock);
	break;
      }
      *testSStream >> correct;
      if( !*testSStream ){
	pthread_mutex_unlock(&readlock);
	break;
      }
      totWords += correct.length()+1;
      int locCount = sentenceCount++;
      list<ECString>  wtList;
      correct.make(wtList);
      SentRep sr( wtList );  // used in precision calc

      ExtPos extPos;
      if(params.extPosIfstream)
	extPos.read(params.extPosIfstream,sr);
      pthread_mutex_unlock(&readlock);

      cuse = &correct;
      int len = correct.length();
      if(len > params.maxSentLen) continue;
      //cerr << "Len = " << len << endl;
      /*
	if( !params.field().in(sentenceCount) )
	{
	sentenceCount++;
	continue;
	}
	if(sentenceCount < -1)
	{
	sentenceCount++;
	continue;
	}
	sentenceCount++;
      */
      vector<ECString> poslist;
      correct.makePosList(poslist);
      ScoreTree sc;
      sc.setEquivInts(poslist);
      MeChart*	chart = new MeChart( sr,extPos,id );
       
      chart->parse( );
      Item* topS = chart->topS();
      if(!topS)
	{
	  cerr << "Parse failed" << endl;
	  cerr << correct << endl;
	  error(" could not parse "); 
	  delete chart;
	  continue;
	}
       
      // compute the outside probabilities on the items so that we can
      // skip doing detailed computations on the really bad ones 

      chart->set_Alphas();

      Bst& bst = chart->findMapParse();
      if( bst.empty()) error( "mapProbs did not return answer");
      float bestF = -1;
      int i;
      int numVersions = 0;
      Link diffs(0);
      //cerr << "Need num diff: " << Bchart::Nth << endl;
      printStruct printS;
      printS.sentenceCount = locCount;
      printS.numDiff = 0;
      for(numVersions = 0 ; ; numVersions++)
	{
	  short pos = 0;
	  Val* val = bst.next(numVersions);
	  if(!val)
	    {
	      //cerr << "Breaking" << endl;
	      break;
	    }
	  InputTree*  mapparse = inputTreeFromBsts(val,pos,sr);
	  bool isU;
	  int dummy = 0;
	  diffs.is_unique(mapparse, isU, dummy);
	  // cerr << "V " << isU << " " << numVersions << *mapparse << endl;
	  if(isU)
	    {
	      printS.probs.push_back(val->prob());
	      printS.trees.push_back(mapparse);
	      printS.numDiff++;
	    }
	  else
	    {
	      delete mapparse;
	    }
	  if(printS.numDiff >= Bchart::Nth) break;
	  if(numVersions > 20000) break;
	}

      ParseStats* locPst = new ParseStats[Bchart::Nth];
      ParseStats bestPs;
      for(i = 0 ; i <printS.numDiff ; i++)
	{
	  InputTree *mapparse = printS.trees[i];
	  assert(mapparse);
	  sc.trips.clear();
	  ParseStats pSt;
	  sc.recordGold(cuse,pSt);
	  sc.precisionRecall(mapparse,pSt);
	  float newF = pSt.fMeasure();
	  cerr << printS.sentenceCount << "\t" << newF << endl;
	  if(newF > bestF)
	    {
	      bestF = newF;
	      bestPs = pSt;
	    }
	  if(histPoints[i])
	    {
	      locPst[i] += bestPs;
	    }
	}
      if(printS.numDiff < Bchart::Nth)
	{
	  for(i = printS.numDiff ; i < Bchart::Nth ; i++)
	    {
	      if(histPoints[i]) locPst[i] += bestPs;
	    }
	}

      pthread_mutex_lock(&scorelock);
      for(i = 0 ; i < Bchart::Nth ; i++) totPst[i]+=locPst[i];
      pthread_mutex_unlock(&scorelock);

      int numPrinted;

      /* put the sentence with which we just finished at the end of the printStack*/
      printStack.push_back(printS);
      PrintStack::iterator psi = printStack.begin();
      /* now look at each item from the front of the print stack
	 to see if it should be printed now */
      pthread_mutex_lock(&writelock);
      for( numPrinted =0; psi != printStack.end(); numPrinted++ )
	{
	  printStruct& pstr=(*psi);
	  if(pstr.sentenceCount != printCount) break;
	  *pstatStream << pstr.sentenceCount << "\t" << pstr.numDiff << "\n";
	  printCount++;
	  for(i = 0 ; i < pstr.numDiff ; i++)
	    {
	      InputTree*  mapparse = pstr.trees[i];
	      assert(mapparse);
	      double logP =log2(pstr.probs[i]);
	      logP -= (sr.length()*log600);
	      *pstatStream <<  logP << "\n";
	      if(Bchart::prettyPrint) *pstatStream << *mapparse << "\n\n";
	      else
		{
		  mapparse->printproper(*pstatStream);
		  *pstatStream << "\n";
		}
	      delete mapparse;
	    }
	  *pstatStream << endl;
	  psi++;
	}
      pthread_mutex_unlock(&writelock);
      for(i = 0 ; i < numPrinted ; i++) printStack.pop_front();
      if(Feature::isLM)
	{
	  double lgram = log2(bst.sum());
	  lgram -= (sr.length()*log600);
	  double pgram = pow(2,lgram);
	  double iptri = chart->triGram();;
	  double ltri = (log2(iptri)-sr.length()*log600);
	  double ptri = pow(2.0,ltri);
	  double pcomb1 = (0.667 * pgram)+(0.333 * ptri);
	  double lcom1 = log2(pcomb1);
	  totGram -= lgram;
	  totTri -= ltri;
	  totMix -= lcom1;
	  if(locCount%10 == 9)
	    {
	      cerr << locCount << "\t";
	      cerr << pow(2.0,totGram/(double)totWords);
	      cerr <<"\t" <<  pow(2.0,totTri/(double)totWords);
	      cerr << "\t" << pow(2.0,totMix/(double)(totWords));
	      cerr << endl;
	    }
	}
      if(locCount%50 == 1)
	{
	  cerr << sentenceCount << "\t";
	  for(int i = 0 ; i < Bchart::Nth ; i++)
	    if(histPoints[i])
	      {
		cerr << i << " " << totPst[i].fMeasure() << "\t";
	      }
	  cerr << endl;
	}

      delete chart;
      delete [] locPst;
    }
  return 0;
}
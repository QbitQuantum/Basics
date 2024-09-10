int RefinerTemp::refine()
{
#ifdef TEMP_LDB
  int i;
  int finish = 1;
  maxHeap *heavyProcessors = new maxHeap(P);

  Set *lightProcessors = new Set();
  for (i=0; i<P; i++) {
    if (isHeavy(&processors[i])) {  
//            CPrintf("Processor %d is HEAVY: load:%f averageLoad:%f!\n",
//      	       i, processors[i].load, averageLoad);
      heavyProcessors->insert((InfoRecord *) &(processors[i]));
    } else if (isLight(&processors[i])) {
//            CkPrintf("Processor %d is LIGHT: load:%f averageLoad:%f!\n",
//      	       i, processors[i].load, averageLoad);
      lightProcessors->insert((InfoRecord *) &(processors[i]));
    }
  }
  int done = 0;

  while (!done) {
    double bestSize;
    computeInfo *bestCompute;
    processorInfo *bestP;
    
    processorInfo *donor = (processorInfo *) heavyProcessors->deleteMax();
    if (!donor) break;

    //find the best pair (c,receiver)
    Iterator nextProcessor;
    processorInfo *p = (processorInfo *) 
      lightProcessors->iterator((Iterator *) &nextProcessor);
    bestSize = 0;
    bestP = 0;
    bestCompute = 0;

    while (p) {
      Iterator nextCompute;
      nextCompute.id = 0;
      computeInfo *c = (computeInfo *) 
	donor->computeSet->iterator((Iterator *)&nextCompute);
      // iout << iINFO << "Considering Procsessor : " 
      //      << p->Id << "\n" << endi;
      while (c) {
          int ind1 = c->id.getID()[0];
        int ind2 = c->id.getID()[1];

        if (!c->migratable) {
	  nextCompute.id++;
	  c = (computeInfo *) 
	    donor->computeSet->next((Iterator *)&nextCompute);
          continue;
        }
//				else CkPrintf("c->id:%f\n",c->load);
//	CkPrintf("c->load: %f p->load:%f overLoad*averageLoad:%f \n",
//	c->load, p->load, overLoad*averageLoad);
//	if ( c->load + p->load < overLoad*averageLoad) {

	if ( c->load*procFreq[c->oldProcessor] + p->load < overLoad*(totalInst*procFreqNew[p->Id]/sumFreqs)
       && ind1!=0 && ind2!=0/* && ind2>=10*/) {
	  // iout << iINFO << "Considering Compute : " 
	  //      << c->Id << " with load " 
	  //      << c->load << "\n" << endi;
//	  if(c->load > bestSize) {
	if(c->load*procFreq[c->oldProcessor] > bestSize/* &&  (c->omid==10 && procFreq[donor->Id]>procFreqNew[donor->Id])*/) {
//	CkPrintf("c:%d is going to PE%d load:%d\n",c->Id,p->Id,c->load);
	bestSize = c->load*procFreq[c->oldProcessor];
	    bestCompute = c;
	    bestP = p;
	  }
	}
	nextCompute.id++;
	c = (computeInfo *) 
	  donor->computeSet->next((Iterator *)&nextCompute);
      }
      p = (processorInfo *) 
	lightProcessors->next((Iterator *) &nextProcessor);
    }
//	CkPrintf("best load:%f\n",bestCompute->load);

    if (bestCompute) {
//CkPrintf("best load:%f\n",bestCompute->load);
//CkPrintf("TTT c->omid:%d c->load:%f P#%d -> P#%d %d -> %d\n",bestCompute->omid,bestCompute->load,donor->Id,bestP->Id,procFreq[donor->Id],procFreqNew[donor->Id]);
      //      CkPrintf("Assign: [%d] with load: %f from %d to %d \n",
      //	       bestCompute->id.id[0], bestCompute->load, 
      //	       donor->Id, bestP->Id);
      deAssign(bestCompute, donor);      
      assign(bestCompute, bestP);
    } else {
      finish = 0;
      break;
    }

//    if (bestP->load > averageLoad)
	if(bestP->load > totalInst*procFreqNew[bestP->Id]/sumFreqs)
      lightProcessors->remove(bestP);
    
    if (isHeavy(donor))
      heavyProcessors->insert((InfoRecord *) donor);
    else if (isLight(donor))
      lightProcessors->insert((InfoRecord *) donor);
  }  

  delete heavyProcessors;
  delete lightProcessors;

  return finish;
#else
	return 0;
#endif
}
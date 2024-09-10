// Reset the GA's statistics based on the population.  To do this right you
// should initialize the population before you pass it to this routine.  If you
// don't, the stats will be based on a non-initialized population.
void
GAStatistics::reset(const GAPopulation & pop){
  curgen = 0;
  numsel = numcro = nummut = numrep = numeval = numpeval = 0;

  memset(gen, 0, Nscrs*sizeof(int));
  memset(aveScore, 0, Nscrs*sizeof(float));
  memset(maxScore, 0, Nscrs*sizeof(float));
  memset(minScore, 0, Nscrs*sizeof(float));
  memset(devScore, 0, Nscrs*sizeof(float));
  memset(divScore, 0, Nscrs*sizeof(float));
  nscrs = 0;
  setScore(pop);
  if(Nscrs > 0) flushScores();

  memset(cscore, 0, Nconv*sizeof(float));
  nconv = 0;			// should set to -1 then call setConv
  cscore[0] = 
    ((pop.order() == GAPopulation::HIGH_IS_BEST) ? pop.max() : pop.min());
//  cscore[0] = pop.max();
//  setConvergence(maxScore[0]);

  updateBestIndividual(pop, gaTrue);
  aveCur = aveInit = pop.ave();
  maxCur = maxInit = maxever = pop.max();
  minCur = minInit = minever = pop.min();
  devCur = devInit = pop.dev();
  divCur = divInit = ((dodiv == gaTrue) ? pop.div() : (float)-1.0);

  on = pop.ave();
  offmax = pop.max();
  offmin = pop.min();
  numpeval = pop.nevals();
  for(int i=0; i<pop.size(); i++)
    numeval += pop.individual(i).nevals();
}
int main(int argc, char* argv[])
{
  ///////////////////////////  read & prepare parameters ///////////////////////
  amcmcBurnMaxSteps = -1;
  amcmcBurnMinSteps = -1;
  amcmcMaxSteps = -1;
  amcmcMaxSeconds = -1;
  ARGS::parse(argc, argv, &cout);
  Timer timer;
  double begSec = timer.time();
  Array<Predicate *> queryPreds;
  Array<TruthValue> queryPredValues;
  GroundPredicateHashArray queries;
  Domain* domain = new Domain;
  MLN* mln = new MLN();
  if(processInput(domain,mln,queries)==-1)
  {
	  cout<<"Error processing input..exiting"<<endl;
	  return -1;
  }
  LiftedAlgsConvertor* liftedAlgsConvertor = new LiftedAlgsConvertor(mln,domain,queries);
    if(aisLIS)
	{
    	bool computeZ=true;
    	//check if marginals are to be computed
    	if(queries.size() > 0)
    		computeZ=false;
    	runLIS(liftedAlgsConvertor,computeZ);
	}
	else if(aisLiftedGibbsWithCluster || aisLiftedGibbs || aisClustering)
	{
		runLBGibbs(liftedAlgsConvertor);
	}
	else if(aisWMPTPEZ || aisWMPTPAZ)
	{
		runPTP(liftedAlgsConvertor);
	}
	else
	{
		if(queries.size() == 0)
		{
			cout<<"No algorithm or query is specified to be run. Running LIS to compute approxZ.."<<endl;
			aisLIS = true;
			runLIS(liftedAlgsConvertor);
		}
		else
		{
			cout<<"No algorithm is specified to be run. Running Lifted Gibbs Sampling to compute Marginals.."<<endl;
			aisLiftedGibbsWithCluster=true;
			runLBGibbs(liftedAlgsConvertor);
		}
	}
  if (domain) delete domain;
  if(mln) delete mln;
  delete liftedAlgsConvertor;
  cout << "total time taken = "; Timer::printTime(cout, timer.time()-begSec);
  cout << endl;
  return 0;
}
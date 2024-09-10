void mcmc(tree *tr, analdef *adef)
{
  int i=0;

  tr->startLH = tr->likelihood;
  printBothOpen("start minimalistic search with LH %f\n", tr->likelihood);
  printBothOpen("tr LH %f, startLH %f\n", tr->likelihood, tr->startLH);
  
  int insert_id;
  int j;

  int maxradius = 30;
  int accepted_spr = 0, accepted_nni = 0, accepted_bl = 0, accepted_model = 0, accepted_gamma = 0, inserts = 0;
  int rejected_spr = 0, rejected_nni = 0, rejected_bl = 0, rejected_model = 0, rejected_gamma = 0;
  int num_moves = 10000;
  boolean proposalAccepted;
  boolean proposalSuccess;
  prop which_proposal;
  double testr;
  double acceptance;

  srand (440);
  double totalTime = 0.0, proposalTime = 0.0, blTime = 0.0, printTime = 0.0;
  double t_start = gettime();
  double t;


  //allocate states
  double bl_prior_exp_lambda = 0.1;
  double bl_sliding_window_w = 0.005;
  double gm_sliding_window_w = 0.75;
  double rt_sliding_window_w = 0.5;
  state *curstate = state_init(tr, adef, maxradius, bl_sliding_window_w, rt_sliding_window_w, gm_sliding_window_w, bl_prior_exp_lambda);
  printStateFileHeader(curstate);
  set_start_bl(curstate);
  printf("start bl_prior: %f\n",curstate->bl_prior);
  set_start_prior(curstate);
  curstate->hastings = 1;//needs to be set by the proposal when necessary

  /* Set the starting LH with a full traversal */
  evaluateGeneric(tr, tr->start, TRUE);	 
  tr->startLH = tr->likelihood;
  printBothOpen("Starting with tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);

  /* Set reasonable model parameters */
  evaluateGeneric(curstate->tr, curstate->tr->start, FALSE); // just for validation 
  printBothOpen("tr LH before modOpt %f\n",curstate->tr->likelihood);
  printSubsRates(curstate->tr, curstate->model, curstate->numSubsRates);

  /* optimize the model with Brents method for reasonable starting points */
  modOpt(curstate->tr, curstate->adef, 5.0); /* not by proposal, just using std raxml machinery... */
  evaluateGeneric(curstate->tr, curstate->tr->start, FALSE); // just for validation 
  printBothOpen("tr LH after modOpt %f\n",curstate->tr->likelihood);
  printSubsRates(curstate->tr, curstate->model, curstate->numSubsRates);
  recordSubsRates(curstate->tr, curstate->model, curstate->numSubsRates, curstate->curSubsRates);

  int first = 1;
  /* beginning of the MCMC chain */
  for(j=0; j<num_moves; j++)
  {
    //printBothOpen("iter %d, tr LH %f, startLH %f\n",j, tr->likelihood, tr->startLH);
    //printRecomTree(tr, TRUE, "startiter");
    proposalAccepted = FALSE;
    t = gettime(); 

    /*
      evaluateGeneric(tr, tr->start); // just for validation 
      printBothOpen("before proposal, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
    */

    which_proposal = proposal(curstate);
    if (first == 1)
    {
      first = 0;
      curstate->curprior = curstate->newprior;
    }
   //printBothOpen("proposal done, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
    assert(which_proposal == SPR || which_proposal == stNNI ||
           which_proposal == UPDATE_ALL_BL || 
           which_proposal == UPDATE_MODEL || which_proposal == UPDATE_GAMMA);
    proposalTime += gettime() - t;
    /* decide upon acceptance */
    testr = (double)rand()/(double)RAND_MAX;
    //should look something like 
    acceptance = fmin(1,(curstate->hastings) * 
		      (exp(curstate->newprior-curstate->curprior)) * (exp(curstate->tr->likelihood-curstate->tr->startLH)));
    
    /*
      //printRecomTree(tr, FALSE, "after proposal");
      printBothOpen("after proposal, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
    */
    if(testr < acceptance)
    {
      proposalAccepted = TRUE;

      switch(which_proposal)
	{
	case SPR:      
	  //printRecomTree(tr, TRUE, "after accepted");
	  // printBothOpen("SPR new topology , iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
	   accepted_spr++;
	  break;
	case stNNI:	  
	  printBothOpen("NNI new topology , iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
	  accepted_nni++;
	  break;
	case UPDATE_ALL_BL:	  
	  //      printBothOpen("BL new , iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
	  accepted_bl++;
	  break;
	case UPDATE_MODEL:      
	  //	printBothOpen("Model new, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
	  accepted_model++;
	  break;
	case UPDATE_GAMMA:      
	  //	printBothOpen("Gamma new, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
	  accepted_gamma++;
	  break;
	default:
	  assert(0);
	}

      curstate->tr->startLH = curstate->tr->likelihood;  //new LH
      curstate->curprior = curstate->newprior;          
    }
    else
    {
      //printBothOpen("rejected , iter %d tr LH %f, startLH %f, %i \n", j, tr->likelihood, tr->startLH, which_proposal);
      resetState(which_proposal,curstate);
      
      switch(which_proposal)
	{
	case SPR:
	  rejected_spr++;
	  break;
	case stNNI:
	  rejected_nni++;
	  break;
	case UPDATE_ALL_BL:
	  rejected_bl++;
	  break;
	case UPDATE_MODEL:
	  rejected_model++;
	  break;
	case UPDATE_GAMMA:
	  rejected_gamma++;
	  break;
	default:
	  assert(0);
	}
      
      evaluateGeneric(tr, tr->start, FALSE); 
      
      // just for validation 

      if(fabs(curstate->tr->startLH - tr->likelihood) > 1.0E-10)
      {
        printBothOpen("WARNING: LH diff %.10f\n", curstate->tr->startLH - tr->likelihood);
      }
      //printRecomTree(tr, TRUE, "after reset");
      //printBothOpen("after reset, iter %d tr LH %f, startLH %f\n", j, tr->likelihood, tr->startLH);
      assert(fabs(curstate->tr->startLH - tr->likelihood) < 1.0E-10);
    }       
    inserts++;
    
    /* need to print status */
    if (j % 50 == 0)
    {
      t = gettime(); 
      printBothOpen("sampled at iter %d, tr LH %f, startLH %f, prior %f, incr %f\n",j, tr->likelihood, tr->startLH, curstate->curprior, tr->likelihood - tr->startLH);
      boolean printBranchLengths = TRUE;
      /*printSimpleTree(tr, printBranchLengths, adef);*/
      //TODO: print some parameters to a file 
      printStateFile(j,curstate);
      printTime += gettime() - t;
    }
  }

  t = gettime(); 
  treeEvaluate(tr, 1);
  blTime += gettime() - t;
  printBothOpen("accepted SPR %d, accepted stNNI %d, accepted BL %d, accepted model %d, accepted gamma %d, num moves tried %d, SPRs with max radius %d\n", 
		accepted_spr, accepted_nni, accepted_bl, accepted_model, accepted_gamma, num_moves, maxradius);
  printBothOpen("rejected SPR %d, rejected stNNI %d, rejected BL %d, rejected model %d, rejected gamma %d\n",
		rejected_spr, rejected_nni, rejected_bl, rejected_model, rejected_gamma);
  printBothOpen("ratio SPR %f, ratio stNNI %f,  ratio BL %f, ratio model %f, ratio gamma %f\n",
		accepted_spr/(double)(rejected_spr+accepted_spr), accepted_nni/(double)(rejected_nni+accepted_nni), accepted_bl/(double)(rejected_bl+accepted_bl), 
		accepted_model/(double)(rejected_model+accepted_model), accepted_gamma/(double)(rejected_gamma+accepted_gamma));
  printBothOpen("total  %f, BL %f, printing %f, proposal %f\n", gettime()- t_start, blTime, printTime, proposalTime);
  assert(inserts == num_moves);
  state_free(curstate);
}
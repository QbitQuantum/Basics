int actUpdatingAvg(ALEInterface& ale, RAMFeatures *ram, BPROFeatures *features, int nextAction, 
	vector<vector<vector<float> > > &w, Parameters param, int totalNumFrames, int gameId,
	vector<bool> &F, vector<bool> &Fprev){

	int reward = 0;

	//If the selected action was one of the primitive actions
	if(nextAction < NUM_ACTIONS){ 
		for(int i = 0; i < FRAME_SKIP && totalNumFrames + ale.getEpisodeFrameNumber() < MAX_NUM_FRAMES; i++){
			reward += ale.act((Action) nextAction);
			Fprev.swap(F);
			F.clear();
			ram->getCompleteFeatureVector(ale.getRAM(), F);
			F.pop_back();
			updateAverage(Fprev, F, ale.getEpisodeFrameNumber(), param, gameId);
		}
	}
	//If the selected action was one of the options
	else{
		int currentAction;
		vector<int> Fbpro;	                  //Set of features active
		vector<float> Q(NUM_ACTIONS, 0.0);    //Q(a) entries

		int option = nextAction - NUM_ACTIONS;
		while(rand()%1000 > 1000 * PROB_TERMINATION && !ale.game_over() && totalNumFrames + ale.getEpisodeFrameNumber() < MAX_NUM_FRAMES){
			//Get state and features active on that state:		
			Fbpro.clear();
			features->getActiveFeaturesIndices(ale.getScreen(), Fbpro);
			updateQValues(Fbpro, Q, w, option);       //Update Q-values for each possible action
			currentAction = epsilonGreedy(Q);
			//Take action, observe reward and next state:
			reward += ale.act((Action) currentAction);
			Fprev.swap(F);
			F.clear();
			ram->getCompleteFeatureVector(ale.getRAM(), F);
			F.pop_back();
			updateAverage(Fprev, F, ale.getEpisodeFrameNumber(), param, gameId);
		}
	}
	return reward;
}
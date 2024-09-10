void HTAppQt::InitHypothesisManager() {
	//create hypothesis manager (creates server on this host on another port)
	HypothesisManager::create(getHostname(), 4449, mTargets, mObservations, mQtGUI);
	if (!mLaunchClients) {
		for (unsigned int i=0; i < mNumClients; i++) {
			new HypothesisClient(i+100);
		}
	}
}
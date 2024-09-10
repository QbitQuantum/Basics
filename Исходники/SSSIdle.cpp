 void SSSIdle::exit() {
	 BlockInput(true);//block mouse input
	 IOHandler::get()->startLoadingAnimation(GameValueProvider::get()->getGameMainWindow());
	 


 }
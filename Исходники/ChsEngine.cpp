	//------------------------------------------------------------------------------------------------
	void ChsEngine::run( void )const{
    double currentTime = getSystemTime();
    double timeInterval = currentTime - lastTime;
    lastTime = currentTime;
		this->getGame()->onUpdate();
    ChsSceneManager::sharedInstance()->update( timeInterval );
    ChsHUDManager::sharedInstance()->update( timeInterval );
 		this->getRenderSystem()->render();
	}
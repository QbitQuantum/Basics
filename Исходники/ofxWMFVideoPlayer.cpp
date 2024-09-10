ofxWMFVideoPlayer::~ofxWMFVideoPlayer() {
	//forceExit();
	if (_player)
	{
		_player->Shutdown();
		//if (_sharedTextureCreated) _player->m_pEVRPresenter->releaseSharedTexture();
		SafeRelease(&_player);
	}

	cout << "Player " << _id << " Terminated" << endl;
	_instanceCount--;
	if (_instanceCount == 0) {
		MFShutdown();

		cout << "Shutting down MF" << endl;
	}
	int i = 1;
}
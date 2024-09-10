bool FullpipeEngine::loadGam(const char *fname, int scene) {
	_gameLoader.reset(new GameLoader());

	if (!_gameLoader->loadFile(fname))
		return false;

	_currSoundListCount = 0;
	initObjectStates();
	// set_g_messageQueueCallback1(messageQueueCallback1); // substituted with direct call

	addMessageHandlerByIndex(global_messageHandler1, 0, 4);

	_inventory = getGameLoaderInventory();

	if (isDemo() && getLanguage() == Common::RU_RUS) {
		_inventory->addItem(ANI_INV_HAMMER, 1);
	} else {
		_inventory->setItemFlags(ANI_INV_MAP, 0x10003);
		_inventory->addItem(ANI_INV_MAP, 1);
	}

	_inventory->rebuildItemRects();

	for (uint i = 0; i < _inventory->getScene()->_picObjList.size(); i++)
		_inventory->getScene()->_picObjList[i]->_picture->MemoryObject::load();

	// _sceneSwitcher = sceneSwitcher; // substituted with direct call
	_gameLoader->_preloadCallback = preloadCallback;
	_gameLoader->_savegameCallback = gameLoaderSavegameCallback;

	_aniMan = accessScene(SC_COMMON)->getAniMan();
	_scene2 = 0;

	_movTable.reset(_aniMan->countMovements());

	_aniMan->setSpeed(1);

	PictureObject *pic = accessScene(SC_INV)->getPictureObjectById(PIC_INV_MENU, 0);

	pic->setFlags(pic->_flags & 0xFFFB);

	// Not used in full game
	//_evalVersionPic = accessScene(SC_COMMON)->getPictureObjectById(PIC_CMN_EVAL, 0);

	initMap();
	initCursors();

	setMusicAllowed(_gameLoader->_gameVar->getSubVarAsInt("MUSIC_ALLOWED"));

	if (scene == -1)
		return true;

	if (scene) {
		_gameLoader->loadScene(726);
		_gameLoader->gotoScene(726, TrubaLeft);

		if (scene != 726)
			_gameLoader->preloadScene(726, getSceneEntrance(scene));
	} else {
		if (_flgPlayIntro) {
			_gameLoader->loadScene(SC_INTRO1);
			_gameLoader->gotoScene(SC_INTRO1, TrubaUp);
		} else {
			if (g_fp->isDemo() && g_fp->getLanguage() == Common::RU_RUS) {
				_gameLoader->loadScene(SC_9);
				_gameLoader->gotoScene(SC_9, TrubaDown);
			} else {
				_gameLoader->loadScene(SC_1);
				_gameLoader->gotoScene(SC_1, TrubaLeft);
			}
		}
	}

	if (!_currentScene)
		return false;

	return true;
}
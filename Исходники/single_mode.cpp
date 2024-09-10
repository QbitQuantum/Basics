int SingleMode::SinglePlayThread(void* param) {
	const wchar_t* name = mainGame->lstSinglePlayList->getListItem(mainGame->lstSinglePlayList->getSelected());
	wchar_t fname[256];
	myswprintf(fname, L"./single/%ls", name);
	char fname2[256];
	size_t slen = BufferIO::EncodeUTF8(fname, fname2);
	mtrandom rnd;
	time_t seed = time(0);
	rnd.reset(seed);
	set_card_reader((card_reader)DataManager::CardReader);
	set_message_handler((message_handler)MessageHandler);
	pduel = create_duel(rnd.rand());
	set_player_info(pduel, 0, 8000, 5, 1);
	set_player_info(pduel, 1, 8000, 5, 1);
	mainGame->dInfo.lp[0] = 8000;
	mainGame->dInfo.lp[1] = 8000;
	myswprintf(mainGame->dInfo.strLP[0], L"%d", mainGame->dInfo.lp[0]);
	myswprintf(mainGame->dInfo.strLP[1], L"%d", mainGame->dInfo.lp[1]);
	BufferIO::CopyWStr(mainGame->ebNickName->getText(), mainGame->dInfo.hostname, 20);
	mainGame->dInfo.clientname[0] = 0;
	mainGame->dInfo.turn = 0;
	mainGame->dInfo.strTurn[0] = 0;
	if(!preload_script(pduel, fname2, slen)) {
		end_duel(pduel);
		return 0;
	}
	mainGame->gMutex.Lock();
	mainGame->HideElement(mainGame->wSinglePlay);
	mainGame->wCardImg->setVisible(true);
	mainGame->wInfos->setVisible(true);
	mainGame->btnLeaveGame->setVisible(true);
	mainGame->btnLeaveGame->setText(dataManager.GetSysString(1210));
	mainGame->stName->setText(L"");
	mainGame->stInfo->setText(L"");
	mainGame->stDataInfo->setText(L"");
	mainGame->stText->setText(L"");
	mainGame->scrCardText->setVisible(false);
	mainGame->wPhase->setVisible(true);
	mainGame->dField.panel = 0;
	mainGame->dField.hovered_card = 0;
	mainGame->dField.clicked_card = 0;
	mainGame->dField.Clear();
	mainGame->dInfo.isFirst = true;
	mainGame->dInfo.isStarted = true;
	mainGame->dInfo.isSingleMode = true;
	mainGame->device->setEventReceiver(&mainGame->dField);
	mainGame->gMutex.Unlock();
	start_duel(pduel, 0);
	char engineBuffer[0x1000];
	is_closing = false;
	is_continuing = true;
	int len = 0;
	while (is_continuing) {
		int result = process(pduel);
		len = result & 0xffff;
		/* int flag = result >> 16; */
		if (len > 0) {
			get_message(pduel, (byte*)engineBuffer);
			is_continuing = SinglePlayAnalyze(engineBuffer, len);
		}
	}
	end_duel(pduel);
	if(!is_closing) {
		mainGame->gMutex.Lock();
		mainGame->dInfo.isStarted = false;
		mainGame->dInfo.isSingleMode = false;
		mainGame->gMutex.Unlock();
		mainGame->closeDoneSignal.Reset();
		mainGame->closeSignal.Set();
		mainGame->closeDoneSignal.Wait();
		mainGame->gMutex.Lock();
		mainGame->ShowElement(mainGame->wSinglePlay);
		mainGame->device->setEventReceiver(&mainGame->menuHandler);
		mainGame->gMutex.Unlock();
	}
	return 0;
}
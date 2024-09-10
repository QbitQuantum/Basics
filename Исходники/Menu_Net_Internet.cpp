void Menu_Net_NETAddServer()
{
	CGuiLayout	cAddSvr;
	gui_event_t *ev = NULL;
	bool		addServerMsg = true;


	// Create the background
	cInternet.Draw( tMenu->bmpBuffer.get() );
	Menu_DrawBox(tMenu->bmpBuffer.get(), 200, 220, 440, 340);
	//DrawImageAdv(tMenu->bmpBuffer, tMenu->bmpMainBack, 202,222, 202,222, 237,117);
    DrawRectFill(tMenu->bmpBuffer.get(), 202,222,439,339,tLX->clDialogBackground);
	for(int i=0;i<6;i++)
		cNetButtons[i].Draw(tMenu->bmpBuffer.get());
	Menu_RedrawMouse(true);


	cAddSvr.Initialize();
	cAddSvr.Add( new CButton(BUT_ADD, tMenu->bmpButtons),	na_Add, 220, 320, 40,15);
	cAddSvr.Add( new CButton(BUT_CANCEL, tMenu->bmpButtons),na_Cancel, 350, 320, 70,15);
	cAddSvr.Add( new CLabel("Add a server", tLX->clNormalLabel),		-1,275, 225, 0, 0);
	cAddSvr.Add( new CLabel("Address", tLX->clNormalLabel),				-1,215, 267, 0, 0);
	cAddSvr.Add( new CTextbox(),							na_Address, 280, 265, 140, tLX->cFont.GetHeight());

	ProcessEvents();
	while(!WasKeyboardEventHappening(SDLK_ESCAPE,false) && addServerMsg && tMenu->bMenuRunning) {
		Menu_RedrawMouse(true);
		DrawImageAdv(VideoPostProcessor::videoSurface(),tMenu->bmpBuffer, 200,220, 200,220, 240, 240);

		ProcessEvents();

		// Process the server list
		if( SvrList_Process() ) {
			// Add the servers to the listview
			Menu_Net_NET_ServerList_Refresher();
		}

		cAddSvr.Draw( VideoPostProcessor::videoSurface() );
		ev = cAddSvr.Process();

		// Process any events
		if(ev) {

			switch(ev->iControlID) {

				// Add
				case na_Add:
					if(ev->iEventMsg == BTN_CLICKED) {

						std::string addr;
						cAddSvr.SendMessage(na_Address, TXS_GETTEXT, &addr, 0);

						SvrList_AddServer(addr, true);
						Menu_Net_NET_ServerList_Refresher();

						// Click!
						PlaySoundSample(sfxGeneral.smpClick);

						addServerMsg = false;
					}
					break;

				// Cancel
				case na_Cancel:
					if(ev->iEventMsg == BTN_CLICKED) {
						// Click!
						PlaySoundSample(sfxGeneral.smpClick);

						addServerMsg = false;
					}
					break;
			}
		}


		DrawCursor(VideoPostProcessor::videoSurface());
		doVideoFrameInMainThread();
		CapFPS();
	}


	cAddSvr.Shutdown();

	// Re-draw the background
	DrawImage(tMenu->bmpBuffer.get(),tMenu->bmpMainBack_common,0,0);
	Menu_DrawSubTitle(tMenu->bmpBuffer.get(),SUB_NETWORK);
	if (tMenu->tFrontendInfo.bPageBoxes)
		Menu_DrawBox(tMenu->bmpBuffer.get(), 15,130, 625, 465);
	Menu_RedrawMouse(true);
}
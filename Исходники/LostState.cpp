void LostState::enter() {
  Input::Instance().m_pMouse->setBuffered(true);
	System::Instance().logMessage("Entering PauseState...");

	OgreBites::SdkTrayManager* trayManager = UserInterface::Instance().m_pTrayMgr;
	trayManager->destroyAllWidgets();
	trayManager->showCursor();
	trayManager->createDecorWidget(
	    OgreBites::TL_CENTER, "youlost", "SdkTrays/Lostthegame");
	trayManager->createButton(
	    OgreBites::TL_CENTER, "RestartGameBtn", "Restart Game", 250);
	trayManager->createButton(
	    OgreBites::TL_CENTER, "BackToMenuBtn", "Return to Menu", 250);
	trayManager->createLabel(OgreBites::TL_TOP, "PauseLbl", "Lost", 250);
	trayManager->showBackdrop("SdkTrays/Shade");
	m_bQuit = false;
}
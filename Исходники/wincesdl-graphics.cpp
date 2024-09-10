void WINCESdlGraphicsManager::update_game_settings() {
	Common::String gameid(ConfMan.get("gameid"));

	// Finish panel initialization
	if (!_panelInitialized && !gameid.empty()) {
		CEGUI::Panel *panel;
		_panelInitialized = true;
		// Add the main panel
		panel = new CEGUI::Panel(0, 32);
		panel->setBackground(IMAGE_PANEL);

		// Save
		panel->add(NAME_ITEM_OPTIONS, new CEGUI::ItemAction(ITEM_OPTIONS, POCKET_ACTION_SAVE));
		// Skip
		panel->add(NAME_ITEM_SKIP, new CEGUI::ItemAction(ITEM_SKIP, POCKET_ACTION_SKIP));
		// sound
		panel->add(NAME_ITEM_SOUND, new CEGUI::ItemSwitch(ITEM_SOUND_OFF, ITEM_SOUND_ON, &OSystem_WINCE3::_soundMaster));

		// bind keys
		panel->add(NAME_ITEM_BINDKEYS, new CEGUI::ItemAction(ITEM_BINDKEYS, POCKET_ACTION_BINDKEYS));
		// portrait/landscape - screen dependent
		// FIXME : will still display the portrait/landscape icon when using a scaler (but will be disabled)
		if (ConfMan.hasKey("landscape")) {
			if (ConfMan.get("landscape")[0] > 57) {
				_newOrientation = _orientationLandscape = ConfMan.getBool("landscape");
				//ConfMan.removeKey("landscape", "");
				ConfMan.setInt("landscape", _orientationLandscape);
			} else
				_newOrientation = _orientationLandscape = ConfMan.getInt("landscape");
		} else {
			_newOrientation = _orientationLandscape = 0;
		}
		panel->add(NAME_ITEM_ORIENTATION, new CEGUI::ItemSwitch(ITEM_VIEW_LANDSCAPE, ITEM_VIEW_PORTRAIT, &_newOrientation, 2));
		_toolbarHandler.add(NAME_MAIN_PANEL, *panel);
		_toolbarHandler.setActive(NAME_MAIN_PANEL);
		_toolbarHandler.setVisible(true);

		if (_videoMode.mode == GFX_NORMAL && ConfMan.hasKey("landscape") && ConfMan.getInt("landscape")) {
			setGraphicsMode(GFX_NORMAL);
			hotswapGFXMode();
		}

		if (_hasSmartphoneResolution)
			panel->setVisible(false);

		_saveToolbarState = true;
	}

	if (ConfMan.hasKey("no_doubletap_rightclick"))
		_noDoubleTapRMB = ConfMan.getBool("no_doubletap_rightclick");

	if (ConfMan.hasKey("no_doubletap_paneltoggle"))
		_noDoubleTapPT = ConfMan.getBool("no_doubletap_paneltoggle");
}
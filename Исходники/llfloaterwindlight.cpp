void LLFloaterWindLight::newPromptCallback(S32 option, const std::string& text, void* userData)
{
	if(text == "")
	{
		return;
	}

	if(option == 0) {
		LLComboBox* comboBox = sWindLight->getChild<LLComboBox>( 
			"WLPresetsCombo");

		LLFloaterDayCycle* sDayCycle = NULL;
		LLComboBox* keyCombo = NULL;
		if(LLFloaterDayCycle::isOpen()) 
		{
			sDayCycle = LLFloaterDayCycle::instance();
			keyCombo = sDayCycle->getChild<LLComboBox>( 
				"WLKeyPresets");
		}

		// add the current parameters to the list
		// see if it's there first
		std::map<std::string, LLWLParamSet>::iterator mIt = 
			LLWLParamManager::instance()->mParamList.find(text);

		// if not there, add a new one
		if(mIt == LLWLParamManager::instance()->mParamList.end()) 
		{
			LLWLParamManager::instance()->addParamSet(text, 
				LLWLParamManager::instance()->mCurParams);
			comboBox->add(text);
			comboBox->sortByName();

			// add a blank to the bottom
			comboBox->selectFirstItem();
			if(comboBox->getSimple() == "")
			{
				comboBox->remove(0);
			}
			comboBox->add(LLStringUtil::null);

			comboBox->setSelectedByValue(text, true);
			if(LLFloaterDayCycle::isOpen()) 
			{
				keyCombo->add(text);
				keyCombo->sortByName();
			}
			LLWLParamManager::instance()->savePreset(text);

		// otherwise, send a message to the user
		} 
		else 
		{
			gViewerWindow->alertXml("ExistsSkyPresetAlert");
		}
	}
}
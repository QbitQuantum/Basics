bool LLFloaterDayCycle::newPromptCallback(const LLSD& notification, const LLSD& response)
{
	std::string text = response["message"].asString();
	S32 option = LLNotification::getSelectedOption(notification, response);

	if(text == "")
	{
		return false;
	}

	if(option == 0) {
		LLComboBox* comboBox = sDayCycle->getChild<LLComboBox>("DayCyclePresetsCombo");

		LLFloaterDayCycle* sDayCycle = NULL;
		LLComboBox* keyCombo = NULL;
		if(LLFloaterDayCycle::isOpen())
		{
			sDayCycle = LLFloaterDayCycle::instance();
			keyCombo = sDayCycle->getChild<LLComboBox>("WLKeyPresets");
		}


		// add the current parameters to the list
		// see if it's there first
		// if not there, add a new one
		if(LLDayCycleManager::getInstance()->findPreset(text).empty())
		{
			//AscentDayCycleManager::instance()->addParamSet(text,
			//	AscentDayCycleManager::instance()->mCurParams);

			LLDayCycleManager::getInstance()->savePreset(text,
						LLWLParamManager::getInstance()->mDay.asLLSD());

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
		}
		else // otherwise, send a message to the user
		{
			LLNotificationsUtil::add("ExistsSkyPresetAlert");
		}
	}
	return false;
}
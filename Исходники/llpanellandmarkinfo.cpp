// virtual
void LLPanelLandmarkInfo::setInfoType(EInfoType type)
{
	LLPanel* landmark_info_panel = getChild<LLPanel>("landmark_info_panel");

	bool is_info_type_create_landmark = type == CREATE_LANDMARK;

	landmark_info_panel->setVisible(type == LANDMARK);

	getChild<LLTextBox>("folder_label")->setVisible(is_info_type_create_landmark);
	mFolderCombo->setVisible(is_info_type_create_landmark);

	switch(type)
	{
		case CREATE_LANDMARK:
		{
			mCurrentTitle = getString("title_create_landmark");

			mLandmarkTitle->setVisible(FALSE);
			mLandmarkTitleEditor->setVisible(TRUE);
			mNotesEditor->setEnabled(TRUE);

			LLViewerParcelMgr* parcel_mgr = LLViewerParcelMgr::getInstance();
			std::string name = parcel_mgr->getAgentParcelName();
			LLVector3 agent_pos = gAgent.getPositionAgent();

			if (name.empty())
			{
				S32 region_x = llround(agent_pos.mV[VX]);
				S32 region_y = llround(agent_pos.mV[VY]);
				S32 region_z = llround(agent_pos.mV[VZ]);

				std::string region_name;
				LLViewerRegion* region = parcel_mgr->getSelectionRegion();
				if (region)
				{
					region_name = region->getName();
				}
				else
				{
					region_name = getString("unknown");
				}

				mLandmarkTitleEditor->setText(llformat("%s (%d, %d, %d)",
									  region_name.c_str(), region_x, region_y, region_z));
			}
			else
			{
				mLandmarkTitleEditor->setText(name);
			}

			std::string desc;
			LLAgentUI::buildLocationString(desc, LLAgentUI::LOCATION_FORMAT_FULL, agent_pos);
			mNotesEditor->setText(desc);

			// Moved landmark creation here from LLPanelLandmarkInfo::processParcelInfo()
			// because we use only agent's current coordinates instead of waiting for
			// remote parcel request to complete.
			if (!LLLandmarkActions::landmarkAlreadyExists())
			{
				createLandmark(LLUUID());
			}
		}
		break;

		case LANDMARK:
		default:
			mCurrentTitle = getString("title_landmark");

			mLandmarkTitle->setVisible(TRUE);
			mLandmarkTitleEditor->setVisible(FALSE);
			mNotesEditor->setEnabled(FALSE);
		break;
	}

	populateFoldersList();

	// Prevent the floater from losing focus (if the sidepanel is undocked).
	setFocus(TRUE);

	LLPanelPlaceInfo::setInfoType(type);
}
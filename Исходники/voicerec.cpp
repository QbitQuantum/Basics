void VOICEREC_execute_command(ISpPhrase *pPhrase, HWND hWnd)
{
	SPPHRASE *pElements;

	// Get the phrase elements, one of which is the rule id we specified in
	// the grammar.  Switch on it to figure out which command was recognized.
	if (SUCCEEDED(pPhrase->GetPhrase(&pElements)))
	{
#ifndef NDEBUG
		if(DEBUG_ON)
		{
			WCHAR *pwszText;
			char szText[255];
			int i;

			pPhrase->GetText(static_cast<ULONG>(SP_GETWHOLEPHRASE), static_cast<ULONG>(SP_GETWHOLEPHRASE), TRUE, &pwszText, NULL);

			memset(szText, 0, 255);
			for (i=0;i<254;i++) 
			{
				if (*(pwszText + i) == 0)
				{
					break;
				}
				szText[i] = (char)(*(pwszText + i));
				szText[i+1] = 0;
			}

			mprintf(( "recognized speech : %s \n", szText ));
			mprintf(( "speech Rule.ulId : %d \n", pElements->Rule.ulId ));
			mprintf(( "confidence: %f \n", pElements->pProperties->SREngineConfidence));

			::CoTaskMemFree(pwszText);
		}
#endif
		int part1, part2, part3;
		part1 = part2 = part3 = -1;
		switch ( pElements->Rule.ulId )
		{

			case VID_WingName: 
			{

				part1 = pElements->pProperties->vValue.ulVal;
				if (pElements->pProperties->pNextSibling) 
				{
					part2 = pElements->pProperties->pNextSibling->vValue.ulVal;
					if (pElements->pProperties->pNextSibling->pNextSibling) 
					{
						part3 = pElements->pProperties->pNextSibling->pNextSibling->vValue.ulVal;
					}
				}
				if (part2 == -1) 
					break; // no ship number or wing

				const wchar_t* valstr = pElements->pProperties->pszValue;
				char* wing_name = new char[wcslen(valstr)+1];

				size_t j = 0;

				for (size_t i = 0; i < wcslen(valstr); i++) {
					int c = wctob(valstr[i]);
					if (c != EOF) {
						wing_name[j++] = static_cast<char>(c);
					}
				}
				wing_name[j] = '\0';

				if (part2 == 0) 
				{
					Msg_instance = wing_lookup(wing_name);
					delete[] wing_name;

					if (Msg_instance < 0)
						break;

					if(!(Player->flags & PLAYER_FLAGS_MSG_MODE))
					{
						hud_squadmsg_toggle();
					}

					if (hud_squadmsg_wing_valid(&Wings[Msg_instance]))
						hud_squadmsg_do_mode(SM_MODE_WING_COMMAND);
				}
				else
				{
					char shipName[NAME_LENGTH];
					wing_bash_ship_name(shipName, wing_name, part2);
					delete[] wing_name;

					Msg_instance = ship_name_lookup(shipName);

					// Can't issue commands to yourself or to nobody
					if (Msg_instance < 0 || Msg_instance == Player_obj->instance)
					{
						break;
					}

					if(!(Player->flags & PLAYER_FLAGS_MSG_MODE))
					{
						hud_squadmsg_toggle();
					}

					if (hud_squadmsg_ship_valid(&Ships[Msg_instance]))
						hud_squadmsg_do_mode(SM_MODE_SHIP_COMMAND);

				}

				if (part3 == -1)
					break;
			}

			case VID_Action:
			{
				int action;
				if (part3 == -1)
				{
					action = pElements->pProperties->vValue.ulVal;
				}
				else
				{
					action = part3;
				}

				doVid_Action(action);
		
				break;
			}

			// These commands run no matter what, and will even bring up the menu
			case VID_TopMenu:
			{
				int action = pElements->pProperties->vValue.ulVal;
				bool msgWindow = false;
				if (Player->flags & PLAYER_FLAGS_MSG_MODE)
				{
					msgWindow = true;
				}

				// If the command window is not up, or it is and its a cancel request toggle
				if((msgWindow && action == VID_Cancel) || (!msgWindow && action != VID_Cancel))
				{
					hud_squadmsg_toggle();
				}
				
				switch(action)
				{
					case VID_Ships:
						hud_squadmsg_do_mode( SM_MODE_SHIP_SELECT );
						break;

					case VID_Wings:
						hud_squadmsg_do_mode( SM_MODE_WING_SELECT );
						break;

					case VID_AllFighters:
					case VID_AllWings:
						hud_squadmsg_msg_all_fighters();
						// can have the action to perform spoken directly afterwards
						if (pElements->pProperties->pFirstChild) {
							doVid_Action(pElements->pProperties->pFirstChild->vValue.ulVal);
						}
						break;

					case VID_Reinforcements:
						hud_squadmsg_do_mode( SM_MODE_REINFORCEMENTS );
						break;

					case VID_SupportShip:
						hud_squadmsg_do_mode( SM_MODE_REPAIR_REARM );
						break;

					case VID_AbortSupport:
						hud_squadmsg_do_mode( SM_MODE_REPAIR_REARM_ABORT );
						break;

					case VID_More:
						break;
				}

				break;
			}
			// phrases for transferring shield energy to different locations
			case VID_shields:
			{
				int action = pElements->pProperties->vValue.ulVal;

				switch(action)
				{
					case 0: button_function( SHIELD_XFER_TOP ); break;
					case 1: button_function( SHIELD_XFER_LEFT ); break;
					case 2: button_function( SHIELD_XFER_RIGHT ); break;
					case 3: button_function( SHIELD_XFER_BOTTOM ); break;
					case 4: button_function( SHIELD_EQUALIZE ); break;

				}

				break;
			}
			// basic cheat, phrase as a value equivalent to the defines in ControlConfig/ControlsConfig.h
			// it just calls the button_function with this value
			case VID_speed:
			case VID_targeting:
			case VID_other:
			{
				int action = pElements->pProperties->vValue.ulVal;

				if (action > -1)
				{
					button_function( action );
				}
				break;
			}
			// nearly the same as the previous except it has some extra entries for
			// maximising/minimising energy
			case VID_power:
			{
				int action = pElements->pProperties->vValue.ulVal;

				if (action >= INCREASE_WEAPON && action <= ETS_EQUALIZE)
				{
					button_function( action );
				}
				else
				{
					// this is for the max engines etc.
					for (int i=1; i<7; i++)
					{
						button_function( action - 132 );
					}
				}
				break;
			}
		}
		// Free the pElements memory which was allocated for us
		::CoTaskMemFree(pElements);
	}

}
// True if you selected an object.
BOOL LLToolPie::pickAndShowMenu(BOOL always_show)
{
	S32 x = mPick.mMousePt.mX;
	S32 y = mPick.mMousePt.mY;
	MASK mask = mPick.mKeyMask;
	if (!always_show && mPick.mPickType == LLPickInfo::PICK_PARCEL_WALL)
	{
		LLParcel* parcel = LLViewerParcelMgr::getInstance()->getCollisionParcel();
		if (parcel)
		{
			LLViewerParcelMgr::getInstance()->selectCollisionParcel();
			if (parcel->getParcelFlag(PF_USE_PASS_LIST) 
				&& !LLViewerParcelMgr::getInstance()->isCollisionBanned())
			{
				// if selling passes, just buy one
				void* deselect_when_done = (void*)TRUE;
				LLPanelLandGeneral::onClickBuyPass(deselect_when_done);
			}
			else
			{
				// not selling passes, get info
				LLFloaterLand::showInstance();
			}
		}

		gFocusMgr.setKeyboardFocus(NULL);
		return LLTool::handleMouseDown(x, y, mask);
	}

	// didn't click in any UI object, so must have clicked in the world
	LLViewerObject *object = mPick.getObject();
	LLViewerObject *parent = NULL;

	// <edit>
	if(mPick.mKeyMask == MASK_SHIFT)
	{
		if(object)
		{
			U8 face = mPick.mObjectFace & 0xff;
			if(face < object->getNumTEs())
			{
				LLViewerImage* img = object->getTEImage(face);
				if(img)
				{
					LLUUID image_id = img->getID();
					LLLocalInventory::addItem(image_id.asString(), (int)LLAssetType::AT_TEXTURE, image_id, true);
				}
			}
		}
		return TRUE;
	}
	// </edit>

	if (mPick.mPickType != LLPickInfo::PICK_LAND)
	{
		LLViewerParcelMgr::getInstance()->deselectLand();
	}
	
	if (object)
	{
		parent = object->getRootEdit();
	}


	BOOL touchable = (object && object->flagHandleTouch()) 
					 || (parent && parent->flagHandleTouch());

	//@hook OnClickObject(uuid,rootuuid,attachment,avatar,touchable,physical) You clicked on an object
	if(object)
		LUA_CALL("OnClickObject") << object->getID().asString() << 
		(parent ? parent->getID() : LLUUID::null).asString() <<
		object->isAttachment() <<
		object->isAvatar() << 
		touchable << 
		(object->usePhysics() || (parent && !parent->isAvatar() && parent->usePhysics())) <<
		LUA_END;

	// If it's a left-click, and we have a special action, do it.
	if (useClickAction(always_show, mask, object, parent))
	{
		mClickAction = 0;
		if (object && object->getClickAction()) 
		{
			mClickAction = object->getClickAction();
		}
		else if (parent && parent->getClickAction()) 
		{
			mClickAction = parent->getClickAction();
		}

		switch(mClickAction)
		{
		case CLICK_ACTION_TOUCH:
			// touch behavior down below...
			break;
		case CLICK_ACTION_SIT:
			if ((gAgent.getAvatarObject() != NULL) && (!gAgent.getAvatarObject()->mIsSitting)) // agent not already sitting
			{
				// <edit>
				if(!gSavedSettings.getBOOL("DisableClickSit"))
				// </edit>
				handle_sit_or_stand();
				// put focus in world when sitting on an object
				gFocusMgr.setKeyboardFocus(NULL);
				return TRUE;
			} // else nothing (fall through to touch)
			
		case CLICK_ACTION_PAY:
			if ((object && object->flagTakesMoney())
				|| (parent && parent->flagTakesMoney()))
			{
				// pay event goes to object actually clicked on
				mClickActionObject = object;
				mLeftClickSelection = LLToolSelect::handleObjectSelection(mPick, FALSE, TRUE);
				if (LLSelectMgr::getInstance()->selectGetAllValid())
				{
					// call this right away, since we have all the info we need to continue the action
					selectionPropertiesReceived();
				}
				return TRUE;
			}
			break;
		case CLICK_ACTION_BUY:
			mClickActionObject = parent;
			mLeftClickSelection = LLToolSelect::handleObjectSelection(mPick, FALSE, TRUE, TRUE);
			if (LLSelectMgr::getInstance()->selectGetAllValid())
			{
				// call this right away, since we have all the info we need to continue the action
				selectionPropertiesReceived();
			}
			return TRUE;
		case CLICK_ACTION_OPEN:
			if (parent && parent->allowOpen())
			{
				mClickActionObject = parent;
				mLeftClickSelection = LLToolSelect::handleObjectSelection(mPick, FALSE, TRUE, TRUE);
				if (LLSelectMgr::getInstance()->selectGetAllValid())
				{
					// call this right away, since we have all the info we need to continue the action
					selectionPropertiesReceived();
				}
			}
			return TRUE;
		case CLICK_ACTION_PLAY:
			handle_click_action_play();
			return TRUE;
		case CLICK_ACTION_OPEN_MEDIA:
			// mClickActionObject = object;
			handle_click_action_open_media(object);
			return TRUE;
		default:
			// nothing
			break;
		}
	}

	if (!always_show && handle_media_click(mPick))
	{
		return FALSE;
	}

	// put focus back "in world"
	gFocusMgr.setKeyboardFocus(NULL);

	// Switch to grab tool if physical or triggerable
	if (object && 
		!object->isAvatar() && 
		((object->usePhysics() || (parent && !parent->isAvatar() && parent->usePhysics())) || touchable) && 
		!always_show)
	{
		gGrabTransientTool = this;
		LLToolMgr::getInstance()->getCurrentToolset()->selectTool( LLToolGrab::getInstance() );
		return LLToolGrab::getInstance()->handleObjectHit( mPick );
	}
	
	LLHUDIcon* last_hit_hud_icon = mPick.mHUDIcon;
	if (!object && last_hit_hud_icon && last_hit_hud_icon->getSourceObject())
	{
		LLFloaterScriptDebug::show(last_hit_hud_icon->getSourceObject()->getID());
	}

	// If left-click never selects or spawns a menu
	// Eat the event.
	if (!gSavedSettings.getBOOL("LeftClickShowMenu")
		&& !always_show)
	{
		// mouse already released
		if (!mGrabMouseButtonDown)
		{
			return TRUE;
		}

		while( object && object->isAttachment() && !object->flagHandleTouch())
		{
			// don't pick avatar through hud attachment
			if (object->isHUDAttachment())
			{
				break;
			}
			object = (LLViewerObject*)object->getParent();
		}
		if (object && object == gAgent.getAvatarObject())
		{
			// we left clicked on avatar, switch to focus mode
			LLToolMgr::getInstance()->setTransientTool(LLToolCamera::getInstance());
			gViewerWindow->hideCursor();
			LLToolCamera::getInstance()->setMouseCapture(TRUE);
			LLToolCamera::getInstance()->pickCallback(mPick);
			gAgent.setFocusOnAvatar(TRUE, TRUE);

			return TRUE;
		}
		// Could be first left-click on nothing
		LLFirstUse::useLeftClickNoHit();

		// Eat the event
		return LLTool::handleMouseDown(x, y, mask);
	}

	if (!always_show && gAgent.leftButtonGrabbed())
	{
		// if the left button is grabbed, don't put up the pie menu
		return LLTool::handleMouseDown(x, y, mask);
	}

	// Can't ignore children here.
	LLToolSelect::handleObjectSelection(mPick, FALSE, TRUE);

	// Spawn pie menu
	if (mPick.mPickType == LLPickInfo::PICK_LAND)
	{
		LLParcelSelectionHandle selection = LLViewerParcelMgr::getInstance()->selectParcelAt( mPick.mPosGlobal );
		gMenuHolder->setParcelSelection(selection);
		gPieLand->show(x, y, mPieMouseButtonDown);

		// <edit>
		if(!gSavedSettings.getBOOL("DisablePointAtAndBeam"))
		{
		// </edit>
		// VEFFECT: ShowPie
		LLHUDEffectSpiral *effectp = (LLHUDEffectSpiral *)LLHUDManager::getInstance()->createViewerEffect(LLHUDObject::LL_HUD_EFFECT_SPHERE, TRUE);
		effectp->setPositionGlobal(mPick.mPosGlobal);
		effectp->setColor(LLColor4U(gAgent.getEffectColor()));
		effectp->setDuration(0.25f);
		// <edit>
		}
		// </edit>
	}
	else if (mPick.mObjectID == gAgent.getID() )
	{
		if(!gPieSelf) 
		{
			//either at very early startup stage or at late quitting stage,
			//this event is ignored.
			return TRUE ;
		}

		gPieSelf->show(x, y, mPieMouseButtonDown);
	}
	else if (object)
	{
		gMenuHolder->setObjectSelection(LLSelectMgr::getInstance()->getSelection());

		if (object->isAvatar() 
			|| (object->isAttachment() && !object->isHUDAttachment() && !object->permYouOwner()))
		{
			// Find the attachment's avatar
			while( object && object->isAttachment())
			{
				object = (LLViewerObject*)object->getParent();
			}

			// Object is an avatar, so check for mute by id.
			LLVOAvatar* avatar = (LLVOAvatar*)object;
			std::string name = avatar->getFullname();
			if (LLMuteList::getInstance()->isMuted(avatar->getID(), name))
			{
				gMenuHolder->childSetText("Avatar Mute", std::string("Unmute")); // *TODO:Translate
				//gMutePieMenu->setLabel("Unmute");
			}
			else
			{
				gMenuHolder->childSetText("Avatar Mute", std::string("Mute")); // *TODO:Translate
				//gMutePieMenu->setLabel("Mute");
			}

			gPieAvatar->show(x, y, mPieMouseButtonDown);
		}
		else if (object->isAttachment())
		{
			gPieAttachment->show(x, y, mPieMouseButtonDown);
		}
		else
		{
			// BUG: What about chatting child objects?
			std::string name;
			LLSelectNode* node = LLSelectMgr::getInstance()->getSelection()->getFirstRootNode();
			if (node)
			{
				name = node->mName;
			}
			if (LLMuteList::getInstance()->isMuted(object->getID(), name))
			{
				gMenuHolder->childSetText("Object Mute", std::string("Unmute")); // *TODO:Translate
				//gMuteObjectPieMenu->setLabel("Unmute");
			}
			else
			{
				gMenuHolder->childSetText("Object Mute", std::string("Mute")); // *TODO:Translate
				//gMuteObjectPieMenu->setLabel("Mute");
			}
			
			gPieObject->show(x, y, mPieMouseButtonDown);

			// <edit>
			if(!gSavedSettings.getBOOL("DisablePointAtAndBeam"))
			{
			// </edit>
			// VEFFECT: ShowPie object
			// Don't show when you click on someone else, it freaks them
			// out.
			LLHUDEffectSpiral *effectp = (LLHUDEffectSpiral *)LLHUDManager::getInstance()->createViewerEffect(LLHUDObject::LL_HUD_EFFECT_SPHERE, TRUE);
			effectp->setPositionGlobal(mPick.mPosGlobal);
			effectp->setColor(LLColor4U(gAgent.getEffectColor()));
			effectp->setDuration(0.25f);
			// <edit>
			}
			// </edit>
		}
	}

	if (always_show)
	{
		// ignore return value
		LLTool::handleRightMouseDown(x, y, mask);
	}
	else
	{
		// ignore return value
		LLTool::handleMouseDown(x, y, mask);
	}

	// We handled the event.
	return TRUE;
}
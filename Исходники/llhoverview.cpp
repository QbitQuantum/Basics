void LLHoverView::updateText()
{
	LLViewerObject* hit_object = getLastHoverObject();
	std::string line;

	//<singu>
	if (hit_object == mLastTextHoverObject &&
		!(mLastTextHoverObjectTimer.getStarted() && mLastTextHoverObjectTimer.hasExpired()))
	{
		// mText is already up to date.
		return;
	}
	mLastTextHoverObject = hit_object;
	mLastTextHoverObjectTimer.stop();
	bool retrieving_data = false;
	//</singu>

	mText.clear();
	if ( hit_object )
	{
		if ( hit_object->isHUDAttachment() )
		{
			// no hover tips for HUD elements, since they can obscure
			// what the HUD is displaying
			return;
		}

		if ( hit_object->isAttachment() )
		{
			// get root of attachment then parent, which is avatar
			LLViewerObject* root_edit = hit_object->getRootEdit();
			if (!root_edit)
			{
				// Strange parenting issue, don't show any text
				return;
			}
			hit_object = (LLViewerObject*)root_edit->getParent();
			if (!hit_object)
			{
				// another strange parenting issue, bail out
				return;
			}
		}

		line.clear();
		if (hit_object->isAvatar())
		{
			LLNameValue* title = hit_object->getNVPair("Title");
			LLNameValue* firstname = hit_object->getNVPair("FirstName");
			LLNameValue* lastname =  hit_object->getNVPair("LastName");
			if (firstname && lastname)
			{
// [RLVa:KB] - Checked: 2009-07-08 (RLVa-1.0.0e)
				if (gRlvHandler.hasBehaviour(RLV_BHVR_SHOWNAMES))
				{
					line = RlvStrings::getAnonym(line.append(firstname->getString()).append(1, ' ').append(lastname->getString()));
				}
				else
				{
// [/RLVa:KB]
					std::string complete_name;
					if (!LLAvatarNameCache::getNSName(hit_object->getID(), complete_name))
						complete_name = firstname->getString() + std::string(" ") + lastname->getString();

					if (title)
					{
						line.append(title->getString());
						line.append(1, ' ');
					}
					line += complete_name;
					
// [RLVa:KB] - Checked: 2009-07-08 (RLVa-1.0.0e)
				}
// [/RLVa:KB]
			}
			else
			{
				line.append(LLTrans::getString("TooltipPerson"));
			}
			mText.push_back(line);
		}
		else
		{
			//
			//  We have hit a regular object (not an avatar or attachment)
			// 

			//
			//  Default prefs will suppress display unless the object is interactive
			//
			BOOL suppressObjectHoverDisplay = !gSavedSettings.getBOOL("ShowAllObjectHoverTip");			
			
			LLSelectNode *nodep = LLSelectMgr::getInstance()->getHoverNode();
			if (nodep)
			{
				line.clear();

				bool for_copy = nodep->mValid && nodep->mPermissions->getMaskEveryone() & PERM_COPY && hit_object && hit_object->permCopy();
				bool for_sale = nodep->mValid && for_sale_selection(nodep);
				
				bool has_media = false;
				bool is_time_based_media = false;
				bool is_web_based_media = false;
				bool is_media_playing = false;
				bool is_media_displaying = false;
			
				// Does this face have media?
				const LLTextureEntry* tep = hit_object ? hit_object->getTE(mLastPickInfo.mObjectFace) : NULL;
			
				if(tep)
				{
					has_media = tep->hasMedia();
					const LLMediaEntry* mep = has_media ? tep->getMediaData() : NULL;
					if (mep)
					{
						viewer_media_t media_impl = LLViewerMedia::getMediaImplFromTextureID(mep->getMediaID());
						LLPluginClassMedia* media_plugin = NULL;
					
						if (media_impl.notNull() && (media_impl->hasMedia()))
						{
							is_media_displaying = true;
							//LLStringUtil::format_map_t args;
						
							media_plugin = media_impl->getMediaPlugin();
							if(media_plugin)
							{	
								if(media_plugin->pluginSupportsMediaTime())
								{
									is_time_based_media = true;
									is_web_based_media = false;
									//args["[CurrentURL]"] =  media_impl->getMediaURL();
									is_media_playing = media_impl->isMediaPlaying();
								}
								else
								{
									is_time_based_media = false;
									is_web_based_media = true;
									//args["[CurrentURL]"] =  media_plugin->getLocation();
								}
								//tooltip_msg.append(LLTrans::getString("CurrentURL", args));
							}
						}
					}
				}

				
				// Avoid showing tip over media that's displaying unless it's for sale
				// also check the primary node since sometimes it can have an action even though
				// the root node doesn't

				if(!suppressObjectHoverDisplay || !is_media_displaying || for_sale)
				{
					if (nodep->mName.empty())
					{
						line.append(LLTrans::getString("TooltipNoName"));
					}
					else
					{
						line.append( nodep->mName );
					}

					mText.push_back(line);

					if (!nodep->mDescription.empty()
						&& nodep->mDescription != DEFAULT_DESC)
					{
						mText.push_back( nodep->mDescription );
					}

					// Line: "Owner: James Linden"
					line.clear();
					line.append(LLTrans::getString("TooltipOwner") + " ");

					if (nodep->mValid)
					{
						LLUUID owner;
						std::string name;
						if (!nodep->mPermissions->isGroupOwned())
						{
							owner = nodep->mPermissions->getOwner();
							if (LLUUID::null == owner)
							{
								line.append(LLTrans::getString("TooltipPublic"));
							}
							else if (LLAvatarNameCache::getNSName(owner, name))
							{
	// [RLVa:KB] - Checked: 2009-07-08 (RLVa-1.0.0e)
								if (gRlvHandler.hasBehaviour(RLV_BHVR_SHOWNAMES))
								{
									name = RlvStrings::getAnonym(name);
								}
	// [/RLVa:KB]

								line.append(name);
							}
							else
							{
								line.append(LLTrans::getString("RetrievingData"));
								retrieving_data = true;
							}
						}
						else
						{
							std::string name;
							owner = nodep->mPermissions->getGroup();
							if (gCacheName->getGroupName(owner, name))
							{
								line.append(name);
								line.append(LLTrans::getString("TooltipIsGroup"));
							}
							else
							{
								line.append(LLTrans::getString("RetrievingData"));
								retrieving_data = true;
							}
						}
					}
					else
					{
						line.append(LLTrans::getString("RetrievingData"));
						retrieving_data = true;
					}
					mText.push_back(line);

					// Build a line describing any special properties of this object.
					LLViewerObject *object = hit_object;
					LLViewerObject *parent = (LLViewerObject *)object->getParent();

					if (object &&
						(object->flagUsePhysics() ||
						 object->flagScripted() || 
						 object->flagHandleTouch() || (parent && parent->flagHandleTouch()) ||
						 object->flagTakesMoney() || (parent && parent->flagTakesMoney()) ||
						 object->flagAllowInventoryAdd() ||
						 object->flagTemporary() ||
						 object->flagPhantom()) )
					{
						line.clear();
						if (object->flagScripted())
						{
						
							line.append(LLTrans::getString("TooltipFlagScript") + " ");
						}

						if (object->flagUsePhysics())
						{
							line.append(LLTrans::getString("TooltipFlagPhysics") + " ");
						}

						if (object->flagHandleTouch() || (parent && parent->flagHandleTouch()) )
						{
							line.append(LLTrans::getString("TooltipFlagTouch") + " ");
							suppressObjectHoverDisplay = FALSE;		//  Show tip
						}

						if (object->flagTakesMoney() || (parent && parent->flagTakesMoney()) )
						{
							line.append(gHippoGridManager->getConnectedGrid()->getCurrencySymbol() + " ");
							suppressObjectHoverDisplay = FALSE;		//  Show tip
						}

						if (object->flagAllowInventoryAdd())
						{
							line.append(LLTrans::getString("TooltipFlagDropInventory") + " ");
							suppressObjectHoverDisplay = FALSE;		//  Show tip
						}

						if (object->flagPhantom())
						{
							line.append(LLTrans::getString("TooltipFlagPhantom") + " ");
						}

						if (object->flagTemporary())
						{
							line.append(LLTrans::getString("TooltipFlagTemporary") + " ");
						}

						if (object->flagUsePhysics() || 
							object->flagHandleTouch() ||
							(parent && parent->flagHandleTouch()) )
						{
							line.append(LLTrans::getString("TooltipFlagRightClickMenu") + " ");
						}
						mText.push_back(line);
					}

					// Free to copy / For Sale: L$
					line.clear();
					if (nodep->mValid)
					{
						if (for_copy)
						{
							line.append(LLTrans::getString("TooltipFreeToCopy"));
							suppressObjectHoverDisplay = FALSE;		//  Show tip
						}
						else if (for_sale)
						{
							LLStringUtil::format_map_t args;
							args["[AMOUNT]"] = llformat("%d", nodep->mSaleInfo.getSalePrice());
							line.append(LLTrans::getString("TooltipForSaleL$", args));
							suppressObjectHoverDisplay = FALSE;		//  Show tip
						}
						else
						{
							// Nothing if not for sale
							// line.append("Not for sale");
						}
					}
					else
					{
						LLStringUtil::format_map_t args;
						args["[MESSAGE]"] = LLTrans::getString("RetrievingData");
						retrieving_data = true;
						line.append(LLTrans::getString("TooltipForSaleMsg", args));
					}
					mText.push_back(line);
					line.clear();
					S32 prim_count = LLSelectMgr::getInstance()->getHoverObjects()->getObjectCount();
					line.append(llformat("Prims: %d", prim_count));
					mText.push_back(line);

					line.clear();
					line.append("Position: ");

					LLViewerRegion *region = gAgent.getRegion();
					LLVector3 position = region->getPosRegionFromGlobal(hit_object->getPositionGlobal());//regionp->getOriginAgent();
					LLVector3 mypos = region->getPosRegionFromGlobal(gAgent.getPositionGlobal());
			

					LLVector3 delta = position - mypos;
					F32 distance = (F32)delta.magVec();

					line.append(llformat("<%.02f,%.02f,%.02f>",position.mV[0],position.mV[1],position.mV[2]));
					mText.push_back(line);
					line.clear();
					line.append(llformat("Distance: %.02fm",distance));
					mText.push_back(line);
				}
				else
				{
					suppressObjectHoverDisplay = TRUE;
				}
				//  If the hover tip shouldn't be shown, delete all the object text
				if (suppressObjectHoverDisplay)
				{
					mText.clear();
				}
			}
		}
	}
	else if ( mHoverLandGlobal != LLVector3d::zero )
	{
		// 
		//  Do not show hover for land unless prefs are set to allow it.
		// 
		
		if (!gSavedSettings.getBOOL("ShowLandHoverTip")) return; 

		// Didn't hit an object, but since we have a land point we
		// must be hovering over land.

		LLParcel* hover_parcel = LLViewerParcelMgr::getInstance()->getHoverParcel();
		LLUUID owner;

		if ( hover_parcel )
		{
			owner = hover_parcel->getOwnerID();
		}

		// Line: "Land"
		line.clear();
		line.append(LLTrans::getString("TooltipLand"));
		if (hover_parcel)
		{
// [RLVa:KB] - Checked: 2009-07-04 (RLVa-1.0.0a) | Added: RLVa-0.2.0b
			line.append( (!gRlvHandler.hasBehaviour(RLV_BHVR_SHOWLOC)) 
				? hover_parcel->getName() : RlvStrings::getString(RLV_STRING_HIDDEN_PARCEL) );
// [/RLVa:KB]
			//line.append(hover_parcel->getName());
		}
		mText.push_back(line);

		// Line: "Owner: James Linden"
		line.clear();
		line.append(LLTrans::getString("TooltipOwner") + " ");

		if ( hover_parcel )
		{
			std::string name;
			if (LLUUID::null == owner)
			{
				line.append(LLTrans::getString("TooltipPublic"));
			}
			else if (hover_parcel->getIsGroupOwned())
			{
				if (gCacheName->getGroupName(owner, name))
				{
					line.append(name);
					line.append(LLTrans::getString("TooltipIsGroup"));
				}
				else
				{
					line.append(LLTrans::getString("RetrievingData"));
					retrieving_data = true;
				}
			}
			else if(gCacheName->getFullName(owner, name))
			{
// [RLVa:KB] - Checked: 2009-07-08 (RLVa-1.0.0e) | Added: RLVa-0.2.0b
				line.append( (!gRlvHandler.hasBehaviour(RLV_BHVR_SHOWNAMES)) ? name : RlvStrings::getAnonym(name));
// [/RLVa:KB]
				//line.append(name);
			}
			else
			{
				line.append(LLTrans::getString("RetrievingData"));
				retrieving_data = true;
			}
		}
		else
		{
			line.append(LLTrans::getString("RetrievingData"));
			retrieving_data = true;
		}
		mText.push_back(line);

		// Line: "no fly, not safe, no build"

		// Don't display properties for your land.  This is just
		// confusing, because you can do anything on your own land.
		if ( hover_parcel && owner != gAgent.getID() )
		{
			S32 words = 0;
			
			line.clear();
			// JC - Keep this in the same order as the checkboxes
			// on the land info panel
			if ( !hover_parcel->getAllowModify() )
			{
				if ( hover_parcel->getAllowGroupModify() )
				{
					line.append(LLTrans::getString("TooltipFlagGroupBuild"));
				}
				else
				{
					line.append(LLTrans::getString("TooltipFlagNoBuild"));
				}
				words++;
			}

			if ( !hover_parcel->getAllowTerraform() )
			{
				if (words) line.append(", ");
				line.append(LLTrans::getString("TooltipFlagNoEdit"));
				words++;
			}

			if ( hover_parcel->getAllowDamage() )
			{
				if (words) line.append(", ");
				line.append(LLTrans::getString("TooltipFlagNotSafe"));
				words++;
			}

			// Maybe we should reflect the estate's block fly bit here as well?  DK 12/1/04
			if ( !hover_parcel->getAllowFly() )
			{
				if (words) line.append(", ");
				line.append(LLTrans::getString("TooltipFlagNoFly"));
				words++;
			}

			if ( !hover_parcel->getAllowOtherScripts() )
			{
				if (words) line.append(", ");
				if ( hover_parcel->getAllowGroupScripts() )
				{
					line.append(LLTrans::getString("TooltipFlagGroupScripts"));
				}
				else
				{
					line.append(LLTrans::getString("TooltipFlagNoScripts"));
				}
				
				words++;
			}

			if (words) 
			{
				mText.push_back(line);
			}
		}

		if (hover_parcel && hover_parcel->getParcelFlag(PF_FOR_SALE))
		{
			LLStringUtil::format_map_t args;
			args["[AMOUNT]"] = llformat("%d", hover_parcel->getSalePrice());
			line = LLTrans::getString("TooltipForSaleL$", args);
			mText.push_back(line);
		}
	}

	//<singu>
	if (retrieving_data)
	{
		// Keep doing this twice per second, until all data was retrieved.
		mLastTextHoverObjectTimer.start(DELAY_BEFORE_REFRESH_TIP);
	}
	//</singu>
}
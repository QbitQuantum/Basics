// Returns true if you got at least one object
void LLToolSelectRect::handleRectangleSelection(S32 x, S32 y, MASK mask)
{
// [RLVa:KB] - Checked: 2010-11-29 (RLVa-1.3.0c) | Modified: RLVa-1.3.0c
	// Block rectangle selection if:
	//   - prevented from editing and no exceptions are set (see below for the case where exceptions are set)
	//   - prevented from interacting at all
	if ( (rlv_handler_t::isEnabled()) && 
		 ( ((gRlvHandler.hasBehaviour(RLV_BHVR_EDIT)) && (!gRlvHandler.hasException(RLV_BHVR_EDIT))) || 
		   (gRlvHandler.hasBehaviour(RLV_BHVR_INTERACT)) ) )
	{
		return;
	}
// [/RLVa:KB]

	LLVector3 av_pos = gAgent.getPositionAgent();
	F32 select_dist_squared = gSavedSettings.getF32("MaxSelectDistance");
	select_dist_squared = select_dist_squared * select_dist_squared;

	BOOL deselect = (mask == MASK_CONTROL);
	S32 left =	llmin(x, mDragStartX);
	S32 right =	llmax(x, mDragStartX);
	S32 top =	llmax(y, mDragStartY);
	S32 bottom =llmin(y, mDragStartY);

	left = llround((F32) left * LLUI::getScaleFactor().mV[VX]);
	right = llround((F32) right * LLUI::getScaleFactor().mV[VX]);
	top = llround((F32) top * LLUI::getScaleFactor().mV[VY]);
	bottom = llround((F32) bottom * LLUI::getScaleFactor().mV[VY]);

	F32 old_far_plane = LLViewerCamera::getInstance()->getFar();
	F32 old_near_plane = LLViewerCamera::getInstance()->getNear();

	S32 width = right - left + 1;
	S32 height = top - bottom + 1;

	BOOL grow_selection = FALSE;
	BOOL shrink_selection = FALSE;

	if (height > mDragLastHeight || width > mDragLastWidth)
	{
		grow_selection = TRUE;
	}
	if (height < mDragLastHeight || width < mDragLastWidth)
	{
		shrink_selection = TRUE;
	}

	if (!grow_selection && !shrink_selection)
	{
		// nothing to do
		return;
	}

	mDragLastHeight = height;
	mDragLastWidth = width;

	S32 center_x = (left + right) / 2;
	S32 center_y = (top + bottom) / 2;

	// save drawing mode
	gGL.matrixMode(LLRender::MM_PROJECTION);
	gGL.pushMatrix();

	BOOL limit_select_distance = gSavedSettings.getBOOL("LimitSelectDistance");
	if (limit_select_distance)
	{
		// ...select distance from control
		LLVector3 relative_av_pos = av_pos;
		relative_av_pos -= LLViewerCamera::getInstance()->getOrigin();

		F32 new_far = relative_av_pos * LLViewerCamera::getInstance()->getAtAxis() + gSavedSettings.getF32("MaxSelectDistance");
		F32 new_near = relative_av_pos * LLViewerCamera::getInstance()->getAtAxis() - gSavedSettings.getF32("MaxSelectDistance");

		new_near = llmax(new_near, 0.1f);

		LLViewerCamera::getInstance()->setFar(new_far);
		LLViewerCamera::getInstance()->setNear(new_near);
	}
// [RLVa:KB] - Checked: 2010-04-11 (RLVa-1.2.0e) | Modified: RLVa-1.0.0g
	if (gRlvHandler.hasBehaviour(RLV_BHVR_FARTOUCH))
	{
		// We'll allow drag selection under fartouch, but only within the fartouch range
		// (just copy/paste the code above us to make that work, thank you Lindens!)
		LLVector3 relative_av_pos = av_pos;
		relative_av_pos -= LLViewerCamera::getInstance()->getOrigin();

		F32 new_far = relative_av_pos * LLViewerCamera::getInstance()->getAtAxis() + 1.5f;
		F32 new_near = relative_av_pos * LLViewerCamera::getInstance()->getAtAxis() - 1.5f;

		new_near = llmax(new_near, 0.1f);

		LLViewerCamera::getInstance()->setFar(new_far);
		LLViewerCamera::getInstance()->setNear(new_near);

		// Usurp these two
		limit_select_distance = TRUE;
		select_dist_squared = 1.5f * 1.5f;
	}
// [/RLVa:KB]
	LLViewerCamera::getInstance()->setPerspective(FOR_SELECTION, 
							center_x-width/2, center_y-height/2, width, height, 
							limit_select_distance);

	if (shrink_selection)
	{
		struct f : public LLSelectedObjectFunctor
		{
			virtual bool apply(LLViewerObject* vobjp)
			{
				LLDrawable* drawable = vobjp->mDrawable;
				if (!drawable || vobjp->getPCode() != LL_PCODE_VOLUME || vobjp->isAttachment())
				{
					return true;
				}
				S32 result = LLViewerCamera::getInstance()->sphereInFrustum(drawable->getPositionAgent(), drawable->getRadius());
				switch (result)
				{
				  case 0:
					LLSelectMgr::getInstance()->unhighlightObjectOnly(vobjp);
					break;
				  case 1:
					// check vertices
					if (!LLViewerCamera::getInstance()->areVertsVisible(vobjp, LLSelectMgr::sRectSelectInclusive))
					{
						LLSelectMgr::getInstance()->unhighlightObjectOnly(vobjp);
					}
					break;
				  default:
					break;
				}
				return true;
			}
		} func;
		LLSelectMgr::getInstance()->getHighlightedObjects()->applyToObjects(&func);
	}

	if (grow_selection)
	{
		std::vector<LLDrawable*> potentials;
				
		for (LLWorld::region_list_t::const_iterator iter = LLWorld::getInstance()->getRegionList().begin(); 
			iter != LLWorld::getInstance()->getRegionList().end(); ++iter)
		{
			LLViewerRegion* region = *iter;
			for (U32 i = 0; i < LLViewerRegion::NUM_PARTITIONS; i++)
			{
				LLSpatialPartition* part = region->getSpatialPartition(i);
				if (part)
				{	
					part->cull(*LLViewerCamera::getInstance(), &potentials, TRUE);
				}
			}
		}
		
		for (std::vector<LLDrawable*>::iterator iter = potentials.begin();
			 iter != potentials.end(); iter++)
		{
			LLDrawable* drawable = *iter;
			LLViewerObject* vobjp = drawable->getVObj();

			if (!drawable || !vobjp ||
				vobjp->getPCode() != LL_PCODE_VOLUME || 
				vobjp->isAttachment() ||
				(deselect && !vobjp->isSelected()))
			{
				continue;
			}

			if (limit_select_distance && dist_vec_squared(drawable->getWorldPosition(), av_pos) > select_dist_squared)
			{
				continue;
			}

// [RLVa:KB] - Checked: 2010-11-29 (RLVa-1.3.0c) | Added: RLVa-1.3.0c
			if ( (rlv_handler_t::isEnabled()) && (!gRlvHandler.canEdit(vobjp)) )
			{
				continue;
			}
// [/RLVa:KB]

			S32 result = LLViewerCamera::getInstance()->sphereInFrustum(drawable->getPositionAgent(), drawable->getRadius());
			if (result)
			{
				switch (result)
				{
				case 1:
					// check vertices
					if (LLViewerCamera::getInstance()->areVertsVisible(vobjp, LLSelectMgr::sRectSelectInclusive))
					{
						LLSelectMgr::getInstance()->highlightObjectOnly(vobjp);
					}
					break;
				case 2:
					LLSelectMgr::getInstance()->highlightObjectOnly(vobjp);
					break;
				default:
					break;
				}
			}
		}
	}

	// restore drawing mode
	gGL.matrixMode(LLRender::MM_PROJECTION);
	gGL.popMatrix();
	gGL.matrixMode(LLRender::MM_MODELVIEW);

	// restore camera
	LLViewerCamera::getInstance()->setFar(old_far_plane);
	LLViewerCamera::getInstance()->setNear(old_near_plane);
	gViewerWindow->setup3DRender();
}
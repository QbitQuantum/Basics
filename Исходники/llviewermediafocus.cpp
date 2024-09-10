void LLViewerMediaFocus::update()
{
	if(mFocusedImplID.notNull())
	{
		// We have a focused impl/face.
		if(!getFocus())
		{
			// We've lost keyboard focus -- check to see whether the media controls have it
			if(mMediaControls.get() && mMediaControls.get()->hasFocus())
			{
				// the media controls have focus -- don't clear.
			}
			else
			{
				// Someone else has focus -- back off.
				clearFocus();
			}
		}
		else if(LLToolMgr::getInstance()->inBuildMode())
		{
			// Build tools are selected -- clear focus.
			clearFocus();
		}
	}
	
	
	LLViewerMediaImpl *media_impl = getFocusedMediaImpl();
	LLViewerObject *viewer_object = getFocusedObject();
	S32 face = mFocusedObjectFace;
	LLVector3 normal = mFocusedObjectNormal;
	bool focus = true;
	
	if(!media_impl || !viewer_object)
	{
		focus = false;
		media_impl = getHoverMediaImpl();
		viewer_object = getHoverObject();
		face = mHoverObjectFace;
		normal = mHoverObjectNormal;
	}
	
	if(media_impl && viewer_object)
	{
		// We have an object and impl to point at.
		
		// Make sure the media HUD object exists.
		if(! mMediaControls.get())
		{
			LLPanelPrimMediaControls* media_controls = new LLPanelPrimMediaControls();
			mMediaControls = media_controls->getHandle();
			gHUDView->addChild(media_controls);	
		}
		mMediaControls.get()->setMediaFace(viewer_object, face, media_impl, normal);
	}
	else
	{
		// The media HUD is no longer needed.
		if(mMediaControls.get())
		{
			mMediaControls.get()->setMediaFace(NULL, 0, NULL);
		}
	}
}
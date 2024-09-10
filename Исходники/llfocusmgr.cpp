void LLFocusMgr::setKeyboardFocus(LLUICtrl* new_focus, BOOL lock, BOOL keystrokes_only)
{
	if (mLockedView && 
		(new_focus == NULL || 
			(new_focus != mLockedView && !new_focus->hasAncestor(mLockedView))))
	{
		// don't allow focus to go to anything that is not the locked focus
		// or one of its descendants
		return;
	}

	//llinfos << "Keyboard focus handled by " << (new_focus ? new_focus->getName() : "nothing") << llendl;

	mKeystrokesOnly = keystrokes_only;

	if( new_focus != mKeyboardFocus )
	{
		mLastKeyboardFocus = mKeyboardFocus;
		mKeyboardFocus = new_focus;

		if( mLastKeyboardFocus )
		{
			mLastKeyboardFocus->onFocusLost();
		}

		// clear out any existing flash
		if (new_focus)
		{
			mFocusWeight = 0.f;
			new_focus->onFocusReceived();
		}
		mFocusTimer.reset();

		#ifdef _DEBUG
			mKeyboardFocusName = new_focus ? new_focus->getName() : std::string("none");
		#endif

		// If we've got a default keyboard focus, and the caller is
		// releasing keyboard focus, move to the default.
		if (mDefaultKeyboardFocus != NULL && mKeyboardFocus == NULL)
		{
			mDefaultKeyboardFocus->setFocus(TRUE);
		}

		LLView* focus_subtree = mKeyboardFocus;
		LLView* viewp = mKeyboardFocus;
		// find root-most focus root
		while(viewp)
		{
			if (viewp->isFocusRoot())
			{
				focus_subtree = viewp;
			}
			viewp = viewp->getParent();
		}

		
		if (focus_subtree)
		{
			mFocusHistory[focus_subtree->getHandle()] = mKeyboardFocus ? mKeyboardFocus->getHandle() : LLHandle<LLView>(); 
		}
	}
	
	if (lock)
	{
		lockFocus();
	}
}
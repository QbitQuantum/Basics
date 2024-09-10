void LLAudioSourceVO::updateMute()
{
	if (!mObjectp || mObjectp->isDead())
	{
	  	mSourceMuted = true;
		return;
	}

	bool mute = false;
	LLVector3d pos_global;

	if (mObjectp->isAttachment())
	{
		LLViewerObject* parent = mObjectp;
		while (parent && !parent->isAvatar())
		{
			parent = (LLViewerObject*)parent->getParent();
		}
		if (parent)
		{
			pos_global = parent->getPositionGlobal();
		}
	}
	else
	{
		pos_global = mObjectp->getPositionGlobal();
	}

	if (!LLViewerParcelMgr::getInstance()->canHearSound(pos_global))
	{
		mute = true;
	}

	if (!mute)
	{
		if (LLMuteList::getInstance()->isMuted(mObjectp->getID()))
		{
			mute = true;
		}
		else if (LLMuteList::getInstance()->isMuted(mOwnerID, LLMute::flagObjectSounds))
		{
			mute = true;
		}
		else if (mObjectp->isAttachment())
		{
			LLViewerObject* parent = mObjectp;
			while (parent && !parent->isAvatar())
			{
				parent = (LLViewerObject*)parent->getParent();
			}
			if (parent 
				&& LLMuteList::getInstance()->isMuted(parent->getID()))
			{
				mute = true;
			}
		}
	}

	if (mute != mSourceMuted)
	{
		mSourceMuted = mute;
		if (mSourceMuted)
		{
		  	// Stop the sound.
			this->play(LLUUID::null);
		}
		else
		{
		  	// Muted sounds keep there data at all times, because
			// it's the place where the audio UUID is stored.
			// However, it's possible that mCurrentDatap is
			// NULL when this source did only preload sounds.
			if (mCurrentDatap)
			{
		  		// Restart the sound.
				this->play(mCurrentDatap->getID());
			}
		}
	}
}
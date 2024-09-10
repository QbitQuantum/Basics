void LLFloaterAvatarList::focusOnPrev(BOOL marked_only)
{
	std::map<LLUUID, LLAvatarListEntry>::iterator iter;
	LLAvatarListEntry *prev = NULL;
	LLAvatarListEntry *entry;

	if (mAvatars.size() == 0)
	{
		return;
	}

	for (iter = mAvatars.begin(); iter != mAvatars.end(); iter++)
	{
		entry = &iter->second;

		if (entry->isDead())
			continue;

		if (prev != NULL && entry->getID() == mFocusedAvatar)
		{
			break;
		}

		if ((!marked_only && entry->isDrawn()) || entry->isMarked())
		{
			prev = entry;
		}
	}

	if (prev != NULL)
	{
		removeFocusFromAll();
		prev->setFocus(TRUE);
		mFocusedAvatar = prev->getID();
		gAgentCamera.lookAtObject(mFocusedAvatar, false);
	}
}
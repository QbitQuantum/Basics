void LLBadgeOwner::addBadgeToParentHolder()
{
	LLView * owner_view = mBadgeOwnerView.get();
	
	if (mBadge && owner_view)
	{
		LLBadgeHolder * badge_holder = NULL;

		// Find the appropriate holder for the badge
		LLView * parent = owner_view->getParent();

		while (parent)
		{
			LLBadgeHolder * badge_holder_panel = dynamic_cast<LLBadgeHolder *>(parent);

			if (badge_holder_panel && badge_holder_panel->acceptsBadge())
			{
				badge_holder = badge_holder_panel;
				break;
			}

			parent = parent->getParent();
		}

		if (badge_holder)
		{
			mHasBadgeHolderParent = badge_holder->addBadge(mBadge);
		}
	}
}
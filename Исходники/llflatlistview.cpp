void LLFlatListView::rearrangeItems()
{
	static LLUICachedControl<S32> scrollbar_size ("UIScrollbarSize", 0);

	setNoItemsCommentVisible(mItemPairs.empty());

	if (mItemPairs.empty()) return;

	//calculating required height - assuming items can be of different height
	//list should accommodate all its items
	S32 height = 0;

	S32 invisible_children_count = 0;
	pairs_iterator_t it = mItemPairs.begin();
	for (; it != mItemPairs.end(); ++it)
	{
		LLPanel* item = (*it)->first;

		// skip invisible child
		if (!item->getVisible())
		{
			++invisible_children_count;
			continue;
		}

		height += item->getRect().getHeight();
	}

	// add paddings between items, excluding invisible ones
	height += mItemPad * (mItemPairs.size() - invisible_children_count - 1);

	LLRect rc = mItemsPanel->getRect();
	S32 width = mItemsNoScrollWidth;

	// update width to avoid horizontal scrollbar
	if (height > getRect().getHeight() - 2 * mBorderThickness)
		width -= scrollbar_size;

	//changes the bottom, end of the list goes down in the scroll container
	rc.setLeftTopAndSize(rc.mLeft, rc.mTop, width, height);
	mItemsPanel->setRect(rc);

	//reshaping items
	S32 item_new_top = height;
	pairs_iterator_t it2, first_it = mItemPairs.begin();
	for (it2 = first_it; it2 != mItemPairs.end(); ++it2)
	{
		LLPanel* item = (*it2)->first;

		// skip invisible child
		if (!item->getVisible())
			continue;

		LLRect rc = item->getRect();
		rc.setLeftTopAndSize(rc.mLeft, item_new_top, width, rc.getHeight());
		item->reshape(rc.getWidth(), rc.getHeight());
		item->setRect(rc);

		// move top for next item in list
		item_new_top -= (rc.getHeight() + mItemPad);
	}

	// Stretch selected item rect to ensure it won't be clipped
	mSelectedItemsBorder->setRect(getLastSelectedItemRect().stretch(-1));
}
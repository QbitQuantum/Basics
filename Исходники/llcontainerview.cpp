void LLContainerView::arrange(S32 width, S32 height, BOOL called_from_parent)
{
	// Determine the sizes and locations of all contained views
	S32 total_height = 0;
	S32 top, left, right, bottom;
	//LLView *childp;

	// These will be used for the children
	left = 4;
	top = getRect().getHeight() - 4;
	right = width - 2;
	bottom = top;
	
	// Leave some space for the top label/grab handle
	if (mShowLabel)
	{
		total_height += 20;
	}

	if (mDisplayChildren)
	{
		// Determine total height
		U32 child_height = 0;
		for (child_list_const_iter_t child_iter = getChildList()->begin();
			 child_iter != getChildList()->end(); ++child_iter)
		{
			LLView *childp = *child_iter;
			if (!childp->getVisible())
			{
				LL_WARNS() << "Incorrect visibility!" << LL_ENDL;
			}
			LLRect child_rect = childp->getRequiredRect();
			child_height += child_rect.getHeight();
			child_height += 2;
		}
		total_height += child_height;
	}

	if (total_height < height)
		total_height = height;
	
	if (followsTop())
	{
		// HACK: casting away const. Should use setRect or some helper function instead.
		const_cast<LLRect&>(getRect()).mBottom = getRect().mTop - total_height;
	}
	else
	{
		// HACK: casting away const. Should use setRect or some helper function instead.
		const_cast<LLRect&>(getRect()).mTop = getRect().mBottom + total_height;
	}
	// HACK: casting away const. Should use setRect or some helper function instead.
		const_cast<LLRect&>(getRect()).mRight = getRect().mLeft + width;

	top = total_height;
	if (mShowLabel)
		{
			top -= 20;
		}
	
	bottom = top;

	if (mDisplayChildren)
	{
		// Iterate through all children, and put in container from top down.
		for (child_list_const_iter_t child_iter = getChildList()->begin();
			 child_iter != getChildList()->end(); ++child_iter)
		{
			LLView *childp = *child_iter;
			LLRect child_rect = childp->getRequiredRect();
			bottom -= child_rect.getHeight();
			LLRect r(left, bottom + child_rect.getHeight(), right, bottom);
			childp->setRect(r);
			childp->reshape(right - left, top - bottom);
			top = bottom - 2;
			bottom = top;
		}
	}
	
	if (!called_from_parent)
	{
		if (getParent())
		{
			getParent()->reshape(getParent()->getRect().getWidth(), getParent()->getRect().getHeight(), FALSE);
		}
	}

}
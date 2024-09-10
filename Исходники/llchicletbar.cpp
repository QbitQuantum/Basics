void LLChicletBar::reshape(S32 width, S32 height, BOOL called_from_parent)
{
	static S32 debug_calling_number = 0;
	LL_DEBUGS() << "**************************************** " << ++debug_calling_number << LL_ENDL;

	S32 current_width = getRect().getWidth();
	S32 delta_width = width - current_width;
	LL_DEBUGS() << "Reshaping: "
		<< ", width: " << width
		<< ", cur width: " << current_width
		<< ", delta_width: " << delta_width
		<< ", called_from_parent: " << called_from_parent
		<< LL_ENDL;

	if (mChicletPanel)			log(mChicletPanel, "before");

	// Difference between chiclet bar width required to fit its children and the actual width. (see EXT-991)
	// Positive value means that chiclet bar is not wide enough.
	// Negative value means that there is free space.
	static S32 extra_shrink_width = 0;
	bool should_be_reshaped = true;

	if (mChicletPanel && mToolbarStack)
	{
		// Firstly, update layout stack to ensure we deal with correct panel sizes.
		{
			// Force the updating of layout to reset panels collapse factor.
			mToolbarStack->updateLayout();
		}

		// chiclet bar is narrowed
		if (delta_width < 0)
		{
			if (extra_shrink_width > 0) // not enough space
			{
				extra_shrink_width += llabs(delta_width);
				should_be_reshaped = false;
			}
			else
			{
				extra_shrink_width = processWidthDecreased(delta_width);

				// increase new width to extra_shrink_width value to not reshape less than chiclet bar minimum
				width += extra_shrink_width;
			}
		}
		// chiclet bar is widened
		else
		{
			if (extra_shrink_width > delta_width)
			{
				// Still not enough space.
				// Only subtract the delta from the required delta and don't reshape.
				extra_shrink_width -= delta_width;
				should_be_reshaped = false;
			}
			else if (extra_shrink_width > 0)
			{
				// If we have some extra shrink width let's reduce delta_width & width
				delta_width -= extra_shrink_width;
				width -= extra_shrink_width;
				extra_shrink_width = 0;
			}
		}
	}

	if (should_be_reshaped)
	{
		LL_DEBUGS() << "Reshape all children with width: " << width << LL_ENDL;
		LLPanel::reshape(width, height, called_from_parent);
	}

	if (mChicletPanel)			log(mChicletPanel, "after");
}
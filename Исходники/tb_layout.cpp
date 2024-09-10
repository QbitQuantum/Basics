void TBLayout::ValidateLayout(const SizeConstraints &constraints, PreferredSize *calculate_ps)
{
	// Layout notes:
	// -All layout code is written for AXIS_X layout.
	//  Instead of duplicating the layout code for both AXIS_X and AXIS_Y, we simply
	//  rotate the in data (rect, gravity, preferred size) and the outdata (rect).

	if (!calculate_ps)
	{
		if (!m_packed.layout_is_invalid)
			return;
		m_packed.layout_is_invalid = 0;
	}
	else
	{
		// Maximum size will grow below depending of the childrens maximum size
		calculate_ps->max_w = calculate_ps->max_h = 0;
	}

	const int spacing = CalculateSpacing();
	const TBRect padding_rect = GetPaddingRect();
	const TBRect layout_rect = RotRect(padding_rect, m_axis);

	const SizeConstraints inner_sc = constraints.ConstrainByPadding(GetRect().w - padding_rect.w,
																	GetRect().h - padding_rect.h);

	// Calculate totals for minimum and preferred width that we need for layout.
	int total_preferred_w = 0;
	int total_min_pref_diff_w = 0;
	int total_max_pref_diff_w = 0;
	for (TBWidget *child = GetFirstInLayoutOrder(); child; child = GetNextInLayoutOrder(child))
	{
		if (child->GetVisibility() == WIDGET_VISIBILITY_GONE)
			continue;

		const int ending_space = GetTrailingSpace(child, spacing);
		const PreferredSize ps = RotPreferredSize(child->GetPreferredSize(inner_sc), m_axis);
		const WIDGET_GRAVITY gravity = RotGravity(child->GetGravity(), m_axis);

		total_preferred_w += ps.pref_w + ending_space;
		total_min_pref_diff_w += ps.pref_w - ps.min_w;

		if (QualifyForExpansion(gravity))
		{
			int capped_max_w = MIN(layout_rect.w, ps.max_w);
			total_max_pref_diff_w += capped_max_w - ps.pref_w;
		}

		if (calculate_ps)
		{
			calculate_ps->min_h = MAX(calculate_ps->min_h, ps.min_h);
			calculate_ps->pref_h = MAX(calculate_ps->pref_h, ps.pref_h);
			calculate_ps->min_w += ps.min_w + ending_space;
			calculate_ps->pref_w += ps.pref_w + ending_space;
			calculate_ps->max_w += ps.max_w + ending_space;

			// The widget height depends on layout and widget properties, so get what
			// it would actually use if it was given max_h as available height.
			// If we just used its max_h, that could increase the whole layout size
			// even if the widget wouldn't actually use it.
			int height = GetWantedHeight(gravity, ps, ps.max_h);
			calculate_ps->max_h = MAX(calculate_ps->max_h, height);

			calculate_ps->size_dependency |= ps.size_dependency;
		}
	}

	if (calculate_ps)
	{
		// We just wanted to calculate preferred size, so return without layouting.
		*calculate_ps = RotPreferredSize(*calculate_ps, m_axis);
		return;
	}

	TB_IF_DEBUG_SETTING(LAYOUT_PS_DEBUGGING, last_layout_time = TBSystem::GetTimeMS());

	// Pre Layout step (calculate distribution position)
	int missing_space = MAX(total_preferred_w - layout_rect.w, 0);
	int extra_space = MAX(layout_rect.w - total_preferred_w, 0);

	int offset = layout_rect.x;
	if (extra_space && m_packed.layout_mode_dist_pos != LAYOUT_DISTRIBUTION_POSITION_LEFT_TOP)
	{
		// To calculate the offset we need to predict the used space. We can do that by checking
		// the distribution mode and total_max_pref_diff_w. That's how much the widgets could possible
		// expand in the layout below.

		int used_space = total_preferred_w;
		if (m_packed.layout_mode_dist != LAYOUT_DISTRIBUTION_PREFERRED)
			used_space += MIN(extra_space, total_max_pref_diff_w);

		if (m_packed.layout_mode_dist_pos == LAYOUT_DISTRIBUTION_POSITION_CENTER)
			offset += (layout_rect.w - used_space) / 2;
		else // LAYOUT_DISTRIBUTION_POSITION_RIGHT_BOTTOM
			offset += layout_rect.w - used_space;
	}

	// Layout
	int used_space = 0;
	for (TBWidget *child = GetFirstInLayoutOrder(); child; child = GetNextInLayoutOrder(child))
	{
		if (child->GetVisibility() == WIDGET_VISIBILITY_GONE)
			continue;

		const int ending_space = GetTrailingSpace(child, spacing);
		const PreferredSize ps = RotPreferredSize(child->GetPreferredSize(inner_sc), m_axis);
		const WIDGET_GRAVITY gravity = RotGravity(child->GetGravity(), m_axis);

		// Calculate width. May shrink if space is missing, or grow if we have extra space.
		int width = ps.pref_w;
		if (missing_space && total_min_pref_diff_w)
		{
			int diff_w = ps.pref_w - ps.min_w;
			float factor = (float)diff_w / (float)total_min_pref_diff_w;
			int removed = (int)(missing_space * factor);
			removed = MIN(removed, diff_w);
			width -= removed;

			total_min_pref_diff_w -= diff_w;
			missing_space -= removed;
		}
		else if (extra_space && total_max_pref_diff_w && QualifyForExpansion(gravity))
		{
			int capped_max_w = MIN(layout_rect.w, ps.max_w);
			int diff_w = capped_max_w - ps.pref_w;
			float factor = (float)diff_w / (float)total_max_pref_diff_w;
			int added = (int)(extra_space * factor);
			added = MIN(added, diff_w);
			width += added;

			total_max_pref_diff_w -= capped_max_w - ps.pref_w;
			extra_space -= added;
		}

		// Calculate height
		int available_height = layout_rect.h;
		int height = GetWantedHeight(gravity, ps, available_height);

		// Calculate position
		int pos = layout_rect.y;
		switch (m_packed.layout_mode_pos)
		{
		case LAYOUT_POSITION_CENTER:
			pos += (available_height - height) / 2;
			break;
		case LAYOUT_POSITION_RIGHT_BOTTOM:
			pos += available_height - height;
			break;
		case LAYOUT_POSITION_GRAVITY:
			if ((gravity & WIDGET_GRAVITY_TOP) && (gravity & WIDGET_GRAVITY_BOTTOM))
				pos += (available_height - height) / 2;
			else if (gravity & WIDGET_GRAVITY_BOTTOM)
				pos += available_height - height;
			break;
		default: // LAYOUT_POSITION_LEFT_TOP
			break;
		}

		// Done! Set rect and increase used space
		TBRect rect(used_space + offset, pos, width, height);
		used_space += width + ending_space;

		child->SetRect(RotRect(rect, m_axis));
	}
	// Update overflow and overflow scroll
	m_overflow = MAX(0, used_space - layout_rect.w);
	SetOverflowScroll(m_overflow_scroll);
}
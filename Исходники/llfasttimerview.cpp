void LLFastTimerView::draw()
{
	LLFastTimer t(LLFastTimer::FTM_RENDER_TIMER);
	
	std::string tdesc;

	F64 clock_freq = (F64)LLFastTimer::countsPerSecond();
	F64 iclock_freq = 1000.0 / clock_freq;
	
	S32 margin = 10;
	S32 height = (S32) (gViewerWindow->getVirtualWindowRect().getHeight()*0.75f);
	S32 width = (S32) (gViewerWindow->getVirtualWindowRect().getWidth() * 0.75f);
	
	// HACK: casting away const. Should use setRect or some helper function instead.
		const_cast<LLRect&>(getRect()).setLeftTopAndSize(getRect().mLeft, getRect().mTop, width, height);

	S32 left, top, right, bottom;
	S32 x, y, barw, barh, dx, dy;
	S32 texth, textw;
	LLPointer<LLUIImage> box_imagep = LLUI::getUIImage("rounded_square.tga");

	// Make sure all timers are accounted for
	// Set 'FTM_OTHER' to unaccounted ticks last frame
	{
		S32 display_timer[LLFastTimer::FTM_NUM_TYPES];
		S32 hidx = LLFastTimer::sLastFrameIndex % LLFastTimer::FTM_HISTORY_NUM;
		for (S32 i=0; i < LLFastTimer::FTM_NUM_TYPES; i++)
		{
			display_timer[i] = 0;
		}
		for (S32 i=0; i < FTV_DISPLAY_NUM; i++)
		{
			S32 tidx = ft_display_table[i].timer;
			display_timer[tidx] = 1;
		}
		LLFastTimer::sCountHistory[hidx][LLFastTimer::FTM_OTHER] = 0;
		LLFastTimer::sCallHistory[hidx][LLFastTimer::FTM_OTHER] = 0;
		for (S32 tidx = 0; tidx < LLFastTimer::FTM_NUM_TYPES; tidx++)
		{
			U64 counts = LLFastTimer::sCountHistory[hidx][tidx];
			if (counts > 0 && display_timer[tidx] == 0)
			{
				LLFastTimer::sCountHistory[hidx][LLFastTimer::FTM_OTHER] += counts;
				LLFastTimer::sCallHistory[hidx][LLFastTimer::FTM_OTHER] += 1;
			}
		}
		LLFastTimer::sCountAverage[LLFastTimer::FTM_OTHER] = 0;
		LLFastTimer::sCallAverage[LLFastTimer::FTM_OTHER] = 0;
		for (S32 h = 0; h < LLFastTimer::FTM_HISTORY_NUM; h++)
		{
			LLFastTimer::sCountAverage[LLFastTimer::FTM_OTHER] += LLFastTimer::sCountHistory[h][LLFastTimer::FTM_OTHER];
			LLFastTimer::sCallAverage[LLFastTimer::FTM_OTHER] += LLFastTimer::sCallHistory[h][LLFastTimer::FTM_OTHER];
		}
		LLFastTimer::sCountAverage[LLFastTimer::FTM_OTHER] /= LLFastTimer::FTM_HISTORY_NUM;
		LLFastTimer::sCallAverage[LLFastTimer::FTM_OTHER] /= LLFastTimer::FTM_HISTORY_NUM;
	}
	
	// Draw the window background
	{
		gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);
		gl_rect_2d(0, getRect().getHeight(), getRect().getWidth(), 0, LLColor4(0.f, 0.f, 0.f, 0.25f));
	}
	
	S32 xleft = margin;
	S32 ytop = margin;
	
	// Draw some help
	{
		
		x = xleft;
		y = height - ytop;
		texth = (S32)LLFontGL::sMonospace->getLineHeight();

		char modedesc[][32] = {
			"2 x Average ",
			"Max         ",
			"Recent Max  ",
			"100 ms      "
		};
		char centerdesc[][32] = {
			"Left      ",
			"Centered  ",
			"Ordered   "
		};

		tdesc = llformat("Full bar = %s [Click to pause/reset] [SHIFT-Click to toggle]",modedesc[mDisplayMode]);
		LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white, LLFontGL::LEFT, LLFontGL::TOP);

		textw = LLFontGL::sMonospace->getWidth(tdesc);

		x = xleft, y -= (texth + 2);
		tdesc = llformat("Justification = %s [CTRL-Click to toggle]",centerdesc[mDisplayCenter]);
		LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white, LLFontGL::LEFT, LLFontGL::TOP);
		y -= (texth + 2);

		LLFontGL::sMonospace->renderUTF8(std::string("[Right-Click log selected] [ALT-Click toggle counts] [ALT-SHIFT-Click sub hidden]"),
										 0, x, y, LLColor4::white, LLFontGL::LEFT, LLFontGL::TOP);
		y -= (texth + 2);
	}

	// Calc the total ticks
	S32 histmax = llmin(LLFastTimer::sLastFrameIndex+1, MAX_VISIBLE_HISTORY);
	U64 ticks_sum[LLFastTimer::FTM_HISTORY_NUM+1][FTV_DISPLAY_NUM];
	for (S32 j=-1; j<LLFastTimer::FTM_HISTORY_NUM; j++)
	{
		S32 hidx;
		if (j >= 0)
			hidx = (LLFastTimer::sLastFrameIndex+j) % LLFastTimer::FTM_HISTORY_NUM;
		else
			hidx = -1;

		// calculate tick info by adding child ticks to parents
		for (S32 i=0; i < FTV_DISPLAY_NUM; i++)
		{
			if (mSubtractHidden && ft_display_table[i].disabled > 1)
			{
				continue;
			}
			// Get ticks
			S32 tidx = ft_display_table[i].timer;
			if (hidx >= 0)
				 ticks_sum[j+1][i] = LLFastTimer::sCountHistory[hidx][tidx];
			else
				 ticks_sum[j+1][i] = LLFastTimer::sCountAverage[tidx];
			S32 pidx = ft_display_table[i].parent;
			// Add ticks to parents
			while (pidx >= 0)
			{
				ticks_sum[j+1][pidx] += ticks_sum[j+1][i];
				pidx = ft_display_table[pidx].parent;
			}
		}
	}
		
	// Draw the legend

	S32 legendwidth = 0;
	xleft = margin;
	ytop = y;

	y -= (texth + 2);

	S32 cur_line = 0;
	S32 display_line[FTV_DISPLAY_NUM];
	for (S32 i=0; i<FTV_DISPLAY_NUM; i++)
	{
		S32 disabled = ft_display_table[i].disabled;
		if (disabled == 3)
		{
			continue; // skip row
		}
		display_line[i] = cur_line;
		ft_display_idx[cur_line] = i;
		cur_line++;
		S32 level = ft_display_table[i].level;
		S32 parent = ft_display_table[i].parent;
		
		x = xleft;

		left = x; right = x + texth;
		top = y; bottom = y - texth;
		S32 scale_offset = 0;
		if (i == mHoverIndex)
		{
			scale_offset = llfloor(sinf(mHighlightTimer.getElapsedTimeF32() * 6.f) * 2.f);
		}
		gl_rect_2d(left - scale_offset, top + scale_offset, right + scale_offset, bottom - scale_offset, *ft_display_table[i].color);

		int tidx = ft_display_table[i].timer;
		F32 ms = 0;
		S32 calls = 0;
		if (mHoverBarIndex > 0 && mHoverIndex >= 0)
		{
			S32 hidx = (LLFastTimer::sLastFrameIndex + (mHoverBarIndex - 1) - mScrollIndex) % LLFastTimer::FTM_HISTORY_NUM;
			S32 bidx = LLFastTimer::FTM_HISTORY_NUM - mScrollIndex - mHoverBarIndex;
			U64 ticks = ticks_sum[bidx+1][i]; // : LLFastTimer::sCountHistory[hidx][tidx];
			ms = (F32)((F64)ticks * iclock_freq);
			calls = (S32)LLFastTimer::sCallHistory[hidx][tidx];
		}
		else
		{
			U64 ticks = ticks_sum[0][i];
			ms = (F32)((F64)ticks * iclock_freq);
			calls = (S32)LLFastTimer::sCallAverage[tidx];
		}
		if (mDisplayCalls)
		{
			tdesc = llformat("%s (%d)",ft_display_table[i].desc,calls);
		}
		else
		{
			tdesc = llformat("%s [%.1f]",ft_display_table[i].desc,ms);
		}
		dx = (texth+4) + level*8;

		LLColor4 color = disabled > 1 ? LLColor4::grey : LLColor4::white;
		if (level > 0)
		{
			S32 line_start_y = (top + bottom) / 2;
			S32 line_end_y = line_start_y + ((texth + 2) * (display_line[i] - display_line[parent])) - (texth / 2);
			gl_line_2d(x + dx - 8, line_start_y, x + dx, line_start_y, color);
			S32 line_x = x + (texth + 4) + ((level - 1) * 8);
			gl_line_2d(line_x, line_start_y, line_x, line_end_y, color);
			if (disabled == 1)
			{
				gl_line_2d(line_x+4, line_start_y-3, line_x+4, line_start_y+4, color);
			}
		}

		x += dx;
		BOOL is_child_of_hover_item = (i == mHoverIndex);
		S32 next_parent = ft_display_table[i].parent;
		while(!is_child_of_hover_item && next_parent >= 0)
		{
			is_child_of_hover_item = (mHoverIndex == next_parent);
			next_parent = ft_display_table[next_parent].parent;
		}

		if (is_child_of_hover_item)
		{
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, color, LLFontGL::LEFT, LLFontGL::TOP, LLFontGL::BOLD);
		}
		else
		{
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, color, LLFontGL::LEFT, LLFontGL::TOP);
		}
		y -= (texth + 2);

		textw = dx + LLFontGL::sMonospace->getWidth(std::string(ft_display_table[i].desc)) + 40;
		if (textw > legendwidth)
			legendwidth = textw;
	}
	for (S32 i=cur_line; i<FTV_DISPLAY_NUM; i++)
	{
		ft_display_idx[i] = -1;
	}
	xleft += legendwidth + 8;
	// ytop = ytop;

	// update rectangle that includes timer bars
	mBarRect.mLeft = xleft;
	mBarRect.mRight = getRect().mRight - xleft;
	mBarRect.mTop = ytop - ((S32)LLFontGL::sMonospace->getLineHeight() + 4);
	mBarRect.mBottom = margin + LINE_GRAPH_HEIGHT;

	y = ytop;
	barh = (ytop - margin - LINE_GRAPH_HEIGHT) / (MAX_VISIBLE_HISTORY + 2);
	dy = barh>>2; // spacing between bars
	if (dy < 1) dy = 1;
	barh -= dy;
	barw = width - xleft - margin;

	// Draw the history bars
	if (LLFastTimer::sLastFrameIndex >= 0)
	{	
		U64 totalticks;
		if (!LLFastTimer::sPauseHistory)
		{
			U64 ticks = 0;
			int hidx = (LLFastTimer::sLastFrameIndex - mScrollIndex) % LLFastTimer::FTM_HISTORY_NUM;
			for (S32 i=0; i<FTV_DISPLAY_NUM; i++)
			{
				if (mSubtractHidden && ft_display_table[i].disabled > 1)
				{
					continue;
				}
				int tidx = ft_display_table[i].timer;
				ticks += LLFastTimer::sCountHistory[hidx][tidx];
			}
			if (LLFastTimer::sCurFrameIndex >= 10)
			{
				U64 framec = LLFastTimer::sCurFrameIndex;
				U64 avg = (U64)mAvgCountTotal;
				mAvgCountTotal = (avg*framec + ticks) / (framec + 1);
				if (ticks > mMaxCountTotal)
				{
					mMaxCountTotal = ticks;
				}
			}
#if 1
			if (ticks < mAvgCountTotal/100 || ticks > mAvgCountTotal*100)
				LLFastTimer::sResetHistory = 1;
#endif
			if (LLFastTimer::sCurFrameIndex < 10 || LLFastTimer::sResetHistory)
			{
				mAvgCountTotal = ticks;
				mMaxCountTotal = ticks;
			}
		}

		if (mDisplayMode == 0)
		{
			totalticks = mAvgCountTotal*2;
		}
		else if (mDisplayMode == 1)
		{
			totalticks = mMaxCountTotal;
		}
		else if (mDisplayMode == 2)
		{
			// Calculate the max total ticks for the current history
			totalticks = 0;
			for (S32 j=0; j<histmax; j++)
			{
				U64 ticks = 0;
				for (S32 i=0; i<FTV_DISPLAY_NUM; i++)
				{
					if (mSubtractHidden && ft_display_table[i].disabled > 1)
					{
						continue;
					}
					int tidx = ft_display_table[i].timer;
					ticks += LLFastTimer::sCountHistory[j][tidx];
				}
				if (ticks > totalticks)
					totalticks = ticks;
			}
		}
		else
		{
			totalticks = (U64)(clock_freq * .1); // 100 ms
		}
		
		// Draw MS ticks
		{
			U32 ms = (U32)((F64)totalticks * iclock_freq) ;

			tdesc = llformat("%.1f ms |", (F32)ms*.25f);
			x = xleft + barw/4 - LLFontGL::sMonospace->getWidth(tdesc);
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white,
										 LLFontGL::LEFT, LLFontGL::TOP);
			
			tdesc = llformat("%.1f ms |", (F32)ms*.50f);
			x = xleft + barw/2 - LLFontGL::sMonospace->getWidth(tdesc);
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white,
										 LLFontGL::LEFT, LLFontGL::TOP);
			
			tdesc = llformat("%.1f ms |", (F32)ms*.75f);
			x = xleft + (barw*3)/4 - LLFontGL::sMonospace->getWidth(tdesc);
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white,
										 LLFontGL::LEFT, LLFontGL::TOP);
			
			tdesc = llformat( "%d ms |", ms);
			x = xleft + barw - LLFontGL::sMonospace->getWidth(tdesc);
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white,
										 LLFontGL::LEFT, LLFontGL::TOP);
		}

		LLRect graph_rect;
		// Draw borders
		{
			gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);
			gGL.color4f(0.5f,0.5f,0.5f,0.5f);

			S32 by = y + 2;
			
			y -= ((S32)LLFontGL::sMonospace->getLineHeight() + 4);

			//heading
			gl_rect_2d(xleft-5, by, getRect().getWidth()-5, y+5, FALSE);

			//tree view
			gl_rect_2d(5, by, xleft-10, 5, FALSE);

			by = y + 5;
			//average bar
			gl_rect_2d(xleft-5, by, getRect().getWidth()-5, by-barh-dy-5, FALSE);
			
			by -= barh*2+dy;
			
			//current frame bar
			gl_rect_2d(xleft-5, by, getRect().getWidth()-5, by-barh-dy-2, FALSE);
			
			by -= barh+dy+1;
			
			//history bars
			gl_rect_2d(xleft-5, by, getRect().getWidth()-5, LINE_GRAPH_HEIGHT-barh-dy-2, FALSE);			
			
			by = LINE_GRAPH_HEIGHT-barh-dy-7;
			
			//line graph
			graph_rect = LLRect(xleft-5, by, getRect().getWidth()-5, 5);
			
			gl_rect_2d(graph_rect, FALSE);
		}
		
		// Draw bars for each history entry
		// Special: -1 = show running average
		gGL.getTexUnit(0)->bind(box_imagep->getImage());
		for (S32 j=-1; j<histmax && y > LINE_GRAPH_HEIGHT; j++)
		{
			int sublevel_dx[FTV_DISPLAY_NUM+1];
			int sublevel_left[FTV_DISPLAY_NUM+1];
			int sublevel_right[FTV_DISPLAY_NUM+1];
			S32 tidx;
			if (j >= 0)
			{
				tidx = LLFastTimer::FTM_HISTORY_NUM - j - 1 - mScrollIndex;
			}
			else
			{
				tidx = -1;
			}
			
			x = xleft;
			
			// draw the bars for each stat
			int xpos[FTV_DISPLAY_NUM+1];
			int deltax[FTV_DISPLAY_NUM+1];
			xpos[0] = xleft;

			for (S32 i = 0; i < FTV_DISPLAY_NUM; i++)
			{
				if (ft_display_table[i].disabled > 1)
				{
					continue;
				}

				F32 frac = (F32)ticks_sum[tidx+1][i] / (F32)totalticks;
		
				dx = llround(frac * (F32)barw);
				deltax[i] = dx;
				
				int level = ft_display_table[i].level;
				int parent = ft_display_table[i].parent;
				llassert(level < FTV_DISPLAY_NUM);
				llassert(parent < FTV_DISPLAY_NUM);
				
				left = xpos[level];
				
				S32 prev_idx = i - 1;
				while (prev_idx > 0)
				{
					if (ft_display_table[prev_idx].disabled <= 1)
					{
						break;
					}
					prev_idx--;
				}
				S32 next_idx = i + 1;
				while (next_idx < FTV_DISPLAY_NUM)
				{
					if (ft_display_table[next_idx].disabled <= 1)
					{
						break;
					}
					next_idx++;
				}

				if (level == 0)
						{
					sublevel_left[level] = xleft;
					sublevel_dx[level] = dx;
					sublevel_right[level] = sublevel_left[level] + sublevel_dx[level];
					}
				else if (i==0 || ft_display_table[prev_idx].level < level)
				{
					// If we are the first entry at a new sublevel block, calc the
					//   total width of this sublevel and modify left to align block.
						U64 sublevelticks = ticks_sum[tidx+1][i];
						for (S32 k=i+1; k<FTV_DISPLAY_NUM; k++)
						{
							if (ft_display_table[k].level < level)
								break;
							if (ft_display_table[k].disabled <= 1 && ft_display_table[k].level == level)
								sublevelticks += ticks_sum[tidx+1][k];
						}
						F32 subfrac = (F32)sublevelticks / (F32)totalticks;
					sublevel_dx[level] = (int)(subfrac * (F32)barw + .5f);

					if (mDisplayCenter == 1) // center aligned
					{
						left += (deltax[parent] - sublevel_dx[level])/2;
					}
					else if (mDisplayCenter == 2) // right aligned
					{
						left += (deltax[parent] - sublevel_dx[level]);
				}

					sublevel_left[level] = left;
					sublevel_right[level] = sublevel_left[level] + sublevel_dx[level];
				}				

				right = left + dx;
				xpos[level] = right;
				xpos[level+1] = left;
				
				mBarStart[(j + 1) * FTV_DISPLAY_NUM + i] = left;
				mBarEnd[(j + 1) * FTV_DISPLAY_NUM + i] = right;

				top = y;
				bottom = y - barh;

				if (right > left)
				{
					//U32 rounded_edges = 0;
					LLColor4 color = *ft_display_table[i].color;
					S32 scale_offset = 0;

					BOOL is_child_of_hover_item = (i == mHoverIndex);
					S32 next_parent = ft_display_table[i].parent;
					while(!is_child_of_hover_item && next_parent >= 0)
					{
						is_child_of_hover_item = (mHoverIndex == next_parent);
						next_parent = ft_display_table[next_parent].parent;
					}

					if (i == mHoverIndex)
					{
						scale_offset = llfloor(sinf(mHighlightTimer.getElapsedTimeF32() * 6.f) * 3.f);
						//color = lerp(color, LLColor4::black, -0.4f);
					}
					else if (mHoverIndex >= 0 && !is_child_of_hover_item)
					{
						color = lerp(color, LLColor4::grey, 0.8f);
					}

					gGL.color4fv(color.mV);
					F32 start_fragment = llclamp((F32)(left - sublevel_left[level]) / (F32)sublevel_dx[level], 0.f, 1.f);
					F32 end_fragment = llclamp((F32)(right - sublevel_left[level]) / (F32)sublevel_dx[level], 0.f, 1.f);
					gl_segmented_rect_2d_fragment_tex(sublevel_left[level], top - level + scale_offset, sublevel_right[level], bottom + level - scale_offset, box_imagep->getTextureWidth(), box_imagep->getTextureHeight(), 16, start_fragment, end_fragment);

				}
					
			}
			y -= (barh + dy);
			if (j < 0)
				y -= barh;
		}
		
		//draw line graph history
		{
			gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);
			LLLocalClipRect clip(graph_rect);
			
			//normalize based on last frame's maximum
			static U64 last_max = 0;
			static F32 alpha_interp = 0.f;
			U64 max_ticks = llmax(last_max, (U64) 1);			
			F32 ms = (F32)((F64)max_ticks * iclock_freq);
			
			//display y-axis range
			std::string tdesc;
			 if (mDisplayCalls)
				tdesc = llformat("%d calls", (int)max_ticks);
			else if (mDisplayHz)
				tdesc = llformat("%d Hz", (int)max_ticks);
			else
				tdesc = llformat("%4.2f ms", ms);
							
			x = graph_rect.mRight - LLFontGL::sMonospace->getWidth(tdesc)-5;
			y = graph_rect.mTop - ((S32)LLFontGL::sMonospace->getLineHeight());
 
			LLFontGL::sMonospace->renderUTF8(tdesc, 0, x, y, LLColor4::white,
										 LLFontGL::LEFT, LLFontGL::TOP);

			//highlight visible range
			{
				S32 first_frame = LLFastTimer::FTM_HISTORY_NUM - mScrollIndex;
				S32 last_frame = first_frame - MAX_VISIBLE_HISTORY;
				
				F32 frame_delta = ((F32) (graph_rect.getWidth()))/(LLFastTimer::FTM_HISTORY_NUM-1);
				
				F32 right = (F32) graph_rect.mLeft + frame_delta*first_frame;
				F32 left = (F32) graph_rect.mLeft + frame_delta*last_frame;
				
				gGL.color4f(0.5f,0.5f,0.5f,0.3f);
				gl_rect_2d((S32) left, graph_rect.mTop, (S32) right, graph_rect.mBottom);
				
				if (mHoverBarIndex >= 0)
				{
					S32 bar_frame = first_frame - mHoverBarIndex;
					F32 bar = (F32) graph_rect.mLeft + frame_delta*bar_frame;

					gGL.color4f(0.5f,0.5f,0.5f,1);
				
					gGL.begin(LLRender::LINES);
					gGL.vertex2i((S32)bar, graph_rect.mBottom);
					gGL.vertex2i((S32)bar, graph_rect.mTop);
					gGL.end();
				}
			}
			
			U64 cur_max = 0;
			for (S32 idx = 0; idx < FTV_DISPLAY_NUM; ++idx)
			{
				if (ft_display_table[idx].disabled > 1)
				{	//skip disabled timers
					continue;
				}
				
				//fatten highlighted timer
				if (mHoverIndex == idx)
				{
					gGL.flush();
					glLineWidth(3);
				}
			
				const F32 * col = ft_display_table[idx].color->mV;
				
				F32 alpha = 1.f;
				
				if (mHoverIndex >= 0 &&
					idx != mHoverIndex)
				{	//fade out non-hihglighted timers
					if (ft_display_table[idx].parent != mHoverIndex)
					{
						alpha = alpha_interp;
					}
				}

				gGL.color4f(col[0], col[1], col[2], alpha);				
				gGL.begin(LLRender::LINE_STRIP);
				for (U32 j = 0; j < LLFastTimer::FTM_HISTORY_NUM; j++)
				{
					U64 ticks = ticks_sum[j+1][idx];

					if (mDisplayHz)
					{
						F64 tc = (F64) (ticks+1) * iclock_freq;
						tc = 1000.f/tc;
						ticks = llmin((U64) tc, (U64) 1024);
					}
					else if (mDisplayCalls)
					{
						S32 tidx = ft_display_table[idx].timer;
						S32 hidx = (LLFastTimer::sLastFrameIndex + j) % LLFastTimer::FTM_HISTORY_NUM;
						ticks = (S32)LLFastTimer::sCallHistory[hidx][tidx];
					}
										
					if (alpha == 1.f)
					{ //normalize to highlighted timer
						cur_max = llmax(cur_max, ticks);
					}
					F32 x = graph_rect.mLeft + ((F32) (graph_rect.getWidth()))/(LLFastTimer::FTM_HISTORY_NUM-1)*j;
					F32 y = graph_rect.mBottom + (F32) graph_rect.getHeight()/max_ticks*ticks;
					gGL.vertex2f(x,y);
				}
				gGL.end();
				
				if (mHoverIndex == idx)
				{
					gGL.flush();
					glLineWidth(1);
				}
			}
			
			//interpolate towards new maximum
			F32 dt = gFrameIntervalSeconds*3.f;
			last_max = (U64) ((F32) last_max + ((F32) cur_max- (F32) last_max) * dt);
			F32 alpha_target = last_max > cur_max ?
								llmin((F32) last_max/ (F32) cur_max - 1.f,1.f) :
								llmin((F32) cur_max/ (F32) last_max - 1.f,1.f);
			
			alpha_interp = alpha_interp + (alpha_target-alpha_interp) * dt;

			if (mHoverIndex >= 0)
			{
				x = (graph_rect.mRight + graph_rect.mLeft)/2;
				y = graph_rect.mBottom + 8;

				LLFontGL::sMonospace->renderUTF8(std::string(ft_display_table[mHoverIndex].desc), 0, x, y, LLColor4::white,
					LLFontGL::LEFT, LLFontGL::BOTTOM);
			}					
		}
	}

	// Output stats for clicked bar to log
	if (mPrintStats >= 0)
	{
		std::string legend_stat;
		S32 stat_num;
		S32 first = 1;
		for (stat_num = 0; stat_num < FTV_DISPLAY_NUM; stat_num++)
		{
			if (ft_display_table[stat_num].disabled > 1)
				continue;
			if (!first)
				legend_stat += ", ";
			first=0;
			legend_stat += ft_display_table[stat_num].desc;
		}
		llinfos << legend_stat << llendl;

		std::string timer_stat;
		first = 1;
		for (stat_num = 0; stat_num < FTV_DISPLAY_NUM; stat_num++)
		{
			S32 disabled = ft_display_table[stat_num].disabled;
			if (disabled > 1)
				continue;
			if (!first)
				timer_stat += ", ";
			first=0;
			U64 ticks;
			S32 tidx = ft_display_table[stat_num].timer;
			if (mPrintStats > 0)
			{
				S32 hidx = (LLFastTimer::sLastFrameIndex+(mPrintStats-1)-mScrollIndex) % LLFastTimer::FTM_HISTORY_NUM;
				ticks = disabled >= 1 ? ticks_sum[mPrintStats][stat_num] : LLFastTimer::sCountHistory[hidx][tidx];
			}
			else
			{
				ticks = disabled >= 1 ? ticks_sum[0][stat_num] : LLFastTimer::sCountAverage[tidx];
			}
			F32 ms = (F32)((F64)ticks * iclock_freq);

			timer_stat += llformat("%.1f",ms);
		}
		llinfos << timer_stat << llendl;
		mPrintStats = -1;
	}
		
	mHoverIndex = -1;
	mHoverBarIndex = -1;

	LLView::draw();
}
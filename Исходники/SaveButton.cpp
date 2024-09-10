void SaveButton::Draw(const Point& screenPos)
{
	Graphics * g = ui::Engine::Ref().g;
	float scaleFactor;
	ui::Point thumbBoxSize(0, 0);

	wantsDraw = true;

	if(selected && selectable)
	{
		g->fillrect(screenPos.X, screenPos.Y, Size.X, Size.Y, 100, 170, 255, 100);
	}

	scaleFactor = (Size.Y-25)/((float)YRES);
	thumbBoxSize = ui::Point(((float)XRES)*scaleFactor, ((float)YRES)*scaleFactor);
	if(thumbnail)
	{
		//thumbBoxSize = ui::Point(thumbnail->Width, thumbnail->Height);
		if(save && save->id)
			g->draw_image(thumbnail, screenPos.X-3+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, 255);
		else
			g->draw_image(thumbnail, screenPos.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, 255);
	}
	else if (file && !file->GetGameSave())
		g->drawtext(screenPos.X+(Size.X-Graphics::textwidth("Error loading save"))/2, screenPos.Y+(Size.Y-28)/2, "Error loading save", 180, 180, 180, 255);
	if(save)
	{
		if(save->id)
		{
			if(isMouseInside)
			{
				g->drawrect(screenPos.X-3+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 210, 230, 255, 255);
				g->drawrect(screenPos.X-4+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, 7, thumbBoxSize.Y, 210, 230, 255, 255);
			}
			else
			{
				g->drawrect(screenPos.X-3+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 180, 180, 180, 255);
				g->drawrect(screenPos.X-4+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, 7, thumbBoxSize.Y, 180, 180, 180, 255);
			}

			g->fillrect(screenPos.X-3+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+1+(Size.Y-20-thumbBoxSize.Y)/2, 5, (thumbBoxSize.Y+1)/2-1, 0, 107, 10, 255);
			g->fillrect(screenPos.X-3+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-20)/2, 5, thumbBoxSize.Y/2-1, 107, 10, 0, 255);

			g->fillrect(screenPos.X-2+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-20)/2-voteBarHeightUp, 3, voteBarHeightUp, 57, 187, 57, 255); //green
			g->fillrect(screenPos.X-2+thumbBoxSize.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-20)/2, 3, voteBarHeightDown, 187, 57, 57, 255); //red
		}
		else
		{
			if(isMouseInside)
				g->drawrect(screenPos.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 210, 230, 255, 255);
			else
				g->drawrect(screenPos.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 180, 180, 180, 255);
		}

		if(isMouseInside && !isMouseInsideAuthor)
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)name.c_str()))/2, screenPos.Y+Size.Y - 21, name, 255, 255, 255, 255);
		else
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)name.c_str()))/2, screenPos.Y+Size.Y - 21, name, 180, 180, 180, 255);

		if(isMouseInsideAuthor)
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)save->userName.c_str()))/2, screenPos.Y+Size.Y - 10, save->userName, 200, 230, 255, 255);
		else
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)save->userName.c_str()))/2, screenPos.Y+Size.Y - 10, save->userName, 100, 130, 160, 255);
		if (showVotes)// && !isMouseInside)
		{
			int x = screenPos.X-7+(Size.X-thumbBoxSize.X)/2+thumbBoxSize.X-Graphics::textwidth(votesBackground.c_str());
			int y = screenPos.Y-23+(Size.Y-thumbBoxSize.Y)/2+thumbBoxSize.Y;
			g->drawtext(x, y, votesBackground, 16, 72, 16, 255);
			g->drawtext(x, y, votesBackground2, 192, 192, 192, 255);
			g->drawtext(x+3, y, votesString, 255, 255, 255, 255);
		}
		if (isMouseInsideHistory && showVotes)
		{
			int x = screenPos.X;
			int y = screenPos.Y-15+(Size.Y-thumbBoxSize.Y)/2+thumbBoxSize.Y;
			g->fillrect(x+1, y+1, 7, 8, 255, 255, 255, 255);
			if (isMouseInsideHistory) {
				g->drawtext(x, y, "\xA6", 200, 100, 80, 255);
			} else {
				g->drawtext(x, y, "\xA6", 160, 70, 50, 255);
			}
		}
		if (!save->GetPublished())
		{
			g->drawtext(screenPos.X, screenPos.Y-2, "\xCD", 255, 255, 255, 255);
			g->drawtext(screenPos.X, screenPos.Y-2, "\xCE", 212, 151, 81, 255);
		}
	}
	else if (file)
	{
		if (isMouseInside)
			g->drawrect(screenPos.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 210, 230, 255, 255);
		else
			g->drawrect(screenPos.X+(Size.X-thumbBoxSize.X)/2, screenPos.Y+(Size.Y-21-thumbBoxSize.Y)/2, thumbBoxSize.X, thumbBoxSize.Y, 180, 180, 180, 255);

		if (isMouseInside)
		{
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)name.c_str()))/2, screenPos.Y+Size.Y - 21, name, 255, 255, 255, 255);
		}
		else
		{
			g->drawtext(screenPos.X+(Size.X-Graphics::textwidth((char *)name.c_str()))/2, screenPos.Y+Size.Y - 21, name, 180, 180, 180, 255);
		}
	}

	if(isMouseInside && selectable)
	{
		g->clearrect(screenPos.X+(Size.X-20), screenPos.Y+6, 14, 14);
		g->drawrect(screenPos.X+(Size.X-20), screenPos.Y+6, 14, 14, 255, 255, 255, 255);
		if(selected)
			g->fillrect(screenPos.X+(Size.X-18), screenPos.Y+8, 10, 10, 255, 255, 255, 255);
	}
}
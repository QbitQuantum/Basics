/* BrowserCanvas::draw
 * Handles drawing of the canvas content
 *******************************************************************/
void BrowserCanvas::draw()
{
	// Setup the viewport
	glViewport(0, 0, GetSize().x, GetSize().y);

	// Setup the screen projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GetSize().x, GetSize().y, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Setup colours
	rgba_t col_bg, col_text;
	bool text_shadow = true;
	if (browser_bg_type == 1)
	{
		// Get system panel background colour
		wxColour bgcolwx = Drawing::getPanelBGColour();
		col_bg.set(bgcolwx.Red(), bgcolwx.Green(), bgcolwx.Blue());

		// Get system text colour
		wxColour textcol = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
		col_text.set(textcol.Red(), textcol.Green(), textcol.Blue());

		// Check text colour brightness, if it's dark don't draw text shadow
		rgba_t col_temp = col_text;
		wxColor::MakeGrey(&col_temp.r, &col_temp.g, &col_temp.b);
		if (col_temp.r < 60)
			text_shadow = false;
	}
	else
	{
		// Otherwise use black background
		col_bg.set(0, 0, 0);

		// And white text
		col_text.set(255, 255, 255);
	}

	// Clear
	glClearColor(col_bg.fr(), col_bg.fg(), col_bg.fb(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Translate to inside of pixel (otherwise inaccuracies can occur on certain gl implementations)
	if (OpenGL::accuracyTweak())
		glTranslatef(0.375f, 0.375f, 0);

	// Draw background if required
	if (browser_bg_type == 0)
		drawCheckeredBackground();

	// Init for texture drawing
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);

	// Draw items
	int x = item_border;
	int y = item_border;
	int col_width = GetSize().x / num_cols;
	int col = 0;
	top_index = -1;
	for (unsigned a = 0; a < items_filter.size(); a++)
	{
		// If we're not yet into the viewable area, skip
		if (y < yoff - fullItemSizeY())
		{
			col++;
			if (col >= num_cols)
			{
				col = 0;
				y += fullItemSizeY();

				// Canvas is filled, stop drawing
				if (y > yoff + GetSize().y)
					break;
			}
			continue;
		}

		// If we're drawing the first non-hidden item, save it
		if (top_index < 0)
		{
			top_index = a;
			top_y = y - yoff;
		}

		// Determine current x position
		int xgap = (col_width - fullItemSizeX()) * 0.5;
		x = item_border + xgap + (col * col_width);

		// Draw selection box if selected
		if (item_selected == items[items_filter[a]])
		{
			// Setup
			glDisable(GL_TEXTURE_2D);
			glColor4f(0.3f, 0.5f, 1.0f, 0.3f);
			glPushMatrix();
			glTranslated(x, y - yoff, 0);
			glTranslated(-item_border, -item_border, 0);

			// Selection background
			glBegin(GL_QUADS);
			glVertex2i(2, 2);
			glVertex2i(2, fullItemSizeY()-3);
			glVertex2i(fullItemSizeX()-3, fullItemSizeY()-3);
			glVertex2i(fullItemSizeX()-3, 2);
			glEnd();

			// Selection border
			glColor4f(0.6f, 0.8f, 1.0f, 1.0f);
			glBegin(GL_LINE_LOOP);
			glVertex2i(2, 2);
			glVertex2i(2, fullItemSizeY()-3);
			glVertex2i(fullItemSizeX()-3, fullItemSizeY()-3);
			glVertex2i(fullItemSizeX()-3, 2);
			glEnd();

			// Finish
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// Draw item
		if (item_size <= 0)
			items[items_filter[a]]->draw(browser_item_size, x, y - yoff, font, show_names, item_type, col_text, text_shadow);
		else
			items[items_filter[a]]->draw(item_size, x, y - yoff, font, show_names, item_type, col_text, text_shadow);

		// Move over for next item
		col++;
		if (col >= num_cols)
		{
			col = 0;
			y += fullItemSizeY();

			// Canvas is filled, stop drawing
			if (y > yoff + GetSize().y)
				break;
		}
	}

	// Swap Buffers
	SwapBuffers();
}
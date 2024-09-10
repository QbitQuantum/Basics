// drawHostList
//---------------------------------------------------------------------------
void GetSessionHostView::drawHostList(const Surface &dest)
{
	char host_info_str[256];
	int curIndex = 0;
	int color;

	Surface tempSurface( getClientRect().getSizeX() - 2, (TEXT_GAP_SPACE + CHAR_YPIX), getClientRect().getSizeX() - 2, 1 );

    tempSurface.fill(Color::darkGreen);
	sprintf( host_info_str, "%-24s %-24s %-12s %10s", "Host",
                                                      "Map",
                                                      "Game Type",
                                                      "Players"   );
	
    tempSurface.bltString( 4, 1, host_info_str, Color::white );
	tempSurface.blt(dest, 0, 1 );
    
    curIndex++;

	for (int i = 0; i < hosts.getCount(); i++)
	{
		sprintf( host_info_str, "%-24s %-24s %-15s %4d/%-4d", hosts[i].name,
                                                              hosts[i].map,
                                                              hosts[i].game_type,
                                                              hosts[i].current_players,
                                                              hosts[i].max_players  );
                                               
        
        color = Color::white;

		if (i == highlightedItem)
		{
			color = Color::red;
		}
		else if (i == selectedItem)
		{
			color = Color::green;
		}

		dest.bltString(4, 6 + curIndex * (TEXT_GAP_SPACE + CHAR_YPIX), host_info_str, color);

		curIndex++;
	}
	//for (int i = topViewableItem; i < topViewableItem + maxViewableItems; i++)

/*	
	int i;

	int shit = 0;
	int color;
	for (i = scrollBar.getValue(); i < scrollBar.getValue() + viewableItemCount; i++)
	{
		iXY offset;
		offset.x = 2;
		offset.y = 2 + shit * (CHAR_YPIX + ITEM_GAP_SPACE);
		
		// Get a color for the item.
		if (i == selectedItem)
		{
			color = Color::green;
		} else
		if (i == highlightedItem)
		{
			color = Color::red;
		} else
		{
			color = Color::white;
		}
		
		// Display the name of this shape.
		dest.bltString(offset.x, offset.y, hosts[i].getName(), color);

		shit++;
	}
*/
} // end GetSessionHostView::drawHostList
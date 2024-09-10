void sim_area_widget::paint_world(wxPaintEvent&)
{
	const model& app_model =
		(dynamic_cast<biosim_gui_impl&>(*GetParent())).app_model();
	const world_map& map =
		app_model.map();

	wxBufferedPaintDC dc(this);

	dc.SetBackground(wxBrush(wxColor(0,0,0)));
	dc.Clear();	

	wxSize client_size(GetClientSize());

	int scroll_pixel_x = scroll_x_ % tile_size_x;
	int scroll_pixel_y = scroll_y_ % tile_size_y;

	int tile_x_start = (scroll_x_ - scroll_pixel_x) / tile_size_x;
	int tile_y_start = (scroll_y_ - scroll_pixel_y) / tile_size_y;
	int tile_x_end = (scroll_x_ + client_size.GetX() - scroll_pixel_x) / tile_size_x + 1; 
	int tile_y_end = (scroll_y_ + client_size.GetY() - scroll_pixel_y) / tile_size_y + 1;

	for (int y = tile_y_start; y <= tile_y_end; ++y)
	for (int x = tile_x_start; x <= tile_x_end; ++x)
	{
		if (x < 0 || y < 0 || x >= map.size_x() || y >= map.size_y())
			continue;

		int tilepos_x = (x - tile_x_start) * tile_size_x - scroll_pixel_x;
		int tilepos_y = (y - tile_y_start) * tile_size_y - scroll_pixel_y;

		dc.DrawBitmap(env_bitmaps_[map.at(x, y).climate()],
					  tilepos_x, tilepos_y);

		if (x == app_model.cursor_x() &&
			y == app_model.cursor_y())
		{
			dc.DrawBitmap(cursor_bitmap_, tilepos_x, tilepos_y);
		}

		const world_tile& tile = map.at(x, y);

		for (world_tile::creature_iterator it(tile.begin()); it != tile.end(); ++it)
		{
			if((*it)->is_alive())
			{

				const creature_prototype *prototype = &((*it)->prototype);

				std::map<const creature_prototype*, wxBitmap>::iterator find_graphics
					(creature_bitmaps_.find(prototype));

				if (find_graphics == creature_bitmaps_.end())
				{
					find_graphics =
						creature_bitmaps_.insert
							(std::pair<const creature_prototype*, wxBitmap>
								(prototype, convert_to_bitmap(prototype->graphics()))).first;
				}

				dc.DrawBitmap(find_graphics->second, tilepos_x, tilepos_y);
			}
			else
				dc.DrawBitmap(dead_bitmap_, tilepos_x, tilepos_y);
		}
	}
}
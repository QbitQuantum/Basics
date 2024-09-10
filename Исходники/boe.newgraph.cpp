void apply_light_mask() 
{
	GrafPtr old_port;
	Rect temp = {0,0,108,84},paint_rect,base_rect = {0,0,36,28};
	Rect big_to = {13,13,337,265};
	short i,j;
	bool is_dark = false,same_mask = true;
	if (PSD[SDF_NO_FRILLS] > 0)
		return;
	if (is_out())
		return;
	if (univ.town->lighting_type == 0)
		return;
	
	if (oval_region == NULL) {
		temp_rect_rgn = NewRgn();
		dark_mask_region = NewRgn();
		oval_region = NewRgn();
		OpenRgn();
		FrameOval(&temp);
		CloseRgn(oval_region);
		}
	
	// Process the light array
	for (i = 2; i < 11; i++)
		for (j = 2; j < 11; j++) 
			if (light_area[i][j] == 0) is_dark = true;
	if (is_dark == false) { 
		for (i = 2; i < 11; i++)
			for (j = 2; j < 11; j++) 
				last_light_mask[i][j] = 0;
		return;
		}
	for (i = 1; i < 12; i++)
		for (j = 1; j < 12; j++)
			if ((light_area[i - 1][j - 1] >= 1) && (light_area[i + 1][j - 1] >= 1) && 
				(light_area[i - 1][j] >= 1) && (light_area[i + 1][j] >= 1) && 
				(light_area[i - 1][j + 1] >= 1) && (light_area[i + 1][j + 1] >= 1) && 
				(light_area[i][j - 1] >= 1) && (light_area[i][j + 1] >= 1)) {
					light_area[i][j] = 2;
					}
	for (i = 1; i < 12; i++)
		for (j = 1; j < 12; j++)
			if ((light_area[i - 1][j - 1] >= 2) && (light_area[i + 1][j - 1] >= 2) && 
				(light_area[i - 1][j] >= 2) && (light_area[i + 1][j] >= 2) && 
				(light_area[i - 1][j + 1] >= 2) && (light_area[i + 1][j + 1] >= 2) && 
				(light_area[i][j - 1] >= 2) && (light_area[i][j + 1] >= 2)) {
					light_area[i][j] = 3;
					}
		
	GetPort(&old_port);
	SetPort(terrain_screen_gworld);

	for (i = 2; i < 11; i++)
		for (j = 2; j < 11; j++) {
			if (light_area[i][j] == 1)
				terrain_there[i - 2][j - 2] = -1;
			}
	for (i = 0; i < 13; i++)
		for (j = 0; j < 13; j++) 
			if (last_light_mask[i][j] != light_area[i][j])
				same_mask = false;
	
	if (same_mask == true) {
		PaintRgn(dark_mask_region);
		SetPort(old_port);
		return;
		}
	SetRectRgn(dark_mask_region,big_to.left,big_to.top,big_to.right,big_to.bottom);
	for (i = 0; i < 13; i++)
		for (j = 0; j < 13; j++) 
			last_light_mask[i][j] = light_area[i][j];
	for (i = 1; i < 12; i++)
		for (j = 1; j < 12; j++) {
			if (light_area[i][j] == 2) {
				
				OffsetRgn(oval_region,13 + 28 * (i - 3), 13 + 36 * (j - 3));
				
				DiffRgn(dark_mask_region,oval_region,dark_mask_region);
				
				OffsetRgn(oval_region,-13 + -1 * (28 * (i - 3)),-13 + -1 * (36 * (j - 3)));
				//PaintRect(&paint_rect);
				}
			if (light_area[i][j] == 3) {
				paint_rect = base_rect;
				OffsetRect(&paint_rect,13 + 28 * (i - 2),13 + 36 * (j - 2));
				SetRectRgn(temp_rect_rgn,paint_rect.left,paint_rect.top,
					paint_rect.right + 28,paint_rect.bottom + 36);
				DiffRgn(dark_mask_region,temp_rect_rgn,dark_mask_region);
				if (light_area[i + 1][j] == 3) light_area[i + 1][j] = 0;
				if (light_area[i + 1][j + 1] == 3) light_area[i + 1][j + 1] = 0;
				if (light_area[i][j + 1] == 3) light_area[i][j + 1] = 0;
				}
			}

	//rect_draw_some_item(light_mask_gworld,big_from,terrain_screen_gworld,big_to,0,0);
	PaintRgn(dark_mask_region);
	SetPort(old_port);

}
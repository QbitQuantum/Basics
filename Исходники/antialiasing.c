static void gpath_draw_filled_custom(GContext* ctx, GPath *path, GColor8 fill_color){
	if(path->num_points == 0)
		return;	

	GPoint offset = path->offset;
	int32_t rotation = path->rotation;

	int32_t s = sin_lookup(rotation);
  	int32_t c = cos_lookup(rotation);

  	// Rotate each point of the gpath and memorize the min/max
	GPoint* points_rot = malloc(sizeof(GPoint) * path->num_points);
	GPoint top_right = (GPoint){(1 << 15)-1,(1 << 15)-1};
	GPoint bottom_left= (GPoint){-(1 << 15),-(1 << 15)};

  	for(uint32_t i=0; i<path->num_points; i++){
  		points_rot[i].x = (path->points[i].x * c - path->points[i].y * s) / TRIG_MAX_RATIO  + offset.x;
		points_rot[i].y = (path->points[i].x * s + path->points[i].y * c) / TRIG_MAX_RATIO  + offset.y;
		if(points_rot[i].x > bottom_left.x)
			bottom_left.x = points_rot[i].x;
		if(points_rot[i].x < top_right.x)
			top_right.x = points_rot[i].x;
		if(points_rot[i].y > bottom_left.y)
			bottom_left.y = points_rot[i].y;
		if(points_rot[i].y < top_right.y)
			top_right.y = points_rot[i].y;
  	}

  	// Create an array bitmap pebble v2 style (1 bit equals 1 pixel)
  	int32_t bytes_per_row = (bottom_left.x - top_right.x + 1) / 8 + ((bottom_left.x - top_right.x  + 1) % 8 == 0 ? 0 : 1);
  	int32_t h = bottom_left.y - top_right.y + 1;
  	uint8_t* pixels = malloc(bytes_per_row * h);
  	memset(pixels, 0, bytes_per_row * h);

  	// And draw the outline path in this 1 bit image
  	GPoint prev_p = points_rot[path->num_points - 1];
  	GPoint p;
  	for(uint32_t i=0; i<path->num_points; i++){
  		p = points_rot[i];
  		bmpDrawLine(pixels, bytes_per_row, prev_p.x - top_right.x, prev_p.y - top_right.y, p.x - top_right.x, p.y - top_right.y);
  		prev_p = p;
  	}

  	free(points_rot);

  	// Compute the starting point for the flow fill algorithm 
  	// TODO tobe improved
  	GPoint start;
  	start.x = (points_rot[0].x + points_rot[1].x) / 2;
  	start.y = (points_rot[0].y + points_rot[1].y) / 2;

  	if(points_rot[0].x < points_rot[1].x){
  		if(points_rot[0].y < points_rot[1].y){
  			start.x--;
  			start.y++;
  		}
  		else {
  			start.x++;
  			start.y++;
  		}
  	}
  	else {
  		if(points_rot[0].y < points_rot[1].y){
  			start.x--;
  			start.y--;
  		}
  		else {
  			start.x++;
  			start.y--;
  		}
  	}

  	// Capture the frame buffer
  	GBitmap* bitmap = graphics_capture_frame_buffer(ctx);

  	// flood fill the gpath
  	floodFill(bitmap, pixels, bytes_per_row, start, top_right, fill_color);

  	// Release the frame buffer
  	graphics_release_frame_buffer(ctx, bitmap);  	

  	//Release the working variables
  	free(pixels);
}
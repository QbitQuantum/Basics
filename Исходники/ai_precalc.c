static void _precalc_vis(DArray geometry, NavMesh* res) {
	assert(res);

	Segment* segs = DARRAY_DATA_PTR(geometry, Segment);

	res->vis_bitmap = MEM_ALLOC(sizeof(uint) * vis_bitmap_size);
	memset(res->vis_bitmap, 0, sizeof(uint) * vis_bitmap_size);

	for(uint y = 0; y < vis_bitmap_height; ++y) {
		for(uint x = 0; x < vis_bitmap_width; ++x) {
			// Construct corresponding screen rect
			float fx = (float)x;
			float fy = (float)y;
			RectF r = rectf(
				fx * vis_cell_width, fy * vis_cell_height,
				(fx + 1.0f) * vis_cell_width, (fy + 1.0f) * vis_cell_height
			);

			// Check if any wall segment intersects rect
			bool solid = false;
			for(uint i = 0; i < geometry.size; ++i) {
				// Raycast is used as a simple binary check
				Vector2 hitp = rectf_raycast(&r, &segs[i].p1, &segs[i].p2);

				// Float comparison is ok here - see rectf_raycast code
				if(hitp.x != segs[i].p2.x || hitp.y != segs[i].p2.y) {
					solid = true;
					break;
				}	
			}

			// Set bit
			if(solid) {
				uint cell = IDX_2D(x, y, vis_bitmap_width);
				res->vis_bitmap[cell/32] |= (1 << (31 - (cell % 32)));
			}
		}
	}
}
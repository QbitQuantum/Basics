	static void drawoptions_func_diffall(const ldraw::DrawOptions& options) {
		CHECK(options.draw_colour == Colour(1,2,3,4));
		CHECK(options.draw_origin == ldraw::CENTER);
		CHECK(options.draw_region == BBoxF(1,2,3,4));
		CHECK(options.draw_scale == SizeF(1,2));
		CHECK(options.draw_angle == 1.0f);
		CHECK(options.draw_frame == 1.0f);
	}
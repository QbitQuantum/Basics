void test_bezier()
{
	size_t width = 400;
	size_t height = 400;
	int centerx = width / 2;
	int centery = height / 2;
	int xsize = (int)(centerx*0.9);
	int ysize = (int)(centery*0.9);

	pb_rgba pb;
	pb_rgba_init(&pb, width, height);

	// background color
	raster_rgba_rect_fill(&pb, 0, 0, width, height, cornsilk);

	// needed for all curves
	int m = 100;
	Pt3 curve[200];

	// One loop
	int nctrls = 5;
	Pt3 ctrls1[5] = { { centerx - xsize, centery, 0 }, { centerx, centery - ysize, 0 }, { centerx + xsize, centery, 0 }, { centerx, centery + ysize, 0 }, { centerx - xsize, centery, 0 } };
	bez3_curve(ctrls1, nctrls, m, curve);
	polyline(&pb, curve, m, pBlack);


	// one double peak through the middle
	Pt3 ctrls3[5] = { { centerx - xsize, centery, 0 }, { centerx - (xsize*0.3f), centery + ysize, 0 }, { centerx, centery - ysize, 0 }, { centerx + (xsize*0.3f), centery + ysize, 0 }, { centerx + xsize, centery, 0 } };
	bez3_curve(ctrls3, nctrls, m, curve);
	polyline(&pb, curve, m, pRed);

	// Now we have a simple image, so write it to a file
	int err = write_PPM_binary("test_bezier.ppm", &pb);
}
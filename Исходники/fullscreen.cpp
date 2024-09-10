bool FullScreen::update()
{

	const float virtual_screen_width = 800.0f;
	const float virtual_screen_height = 600.0f;
	game_time.update();

	// Check for fullscreen switch
	if (fullscreen_requested != is_fullscreen)
	{
		is_fullscreen = fullscreen_requested;
		create_window();
	}

	if (window.get_gc() != canvas.get_gc()) 
	{
		canvas = Canvas(window); // Always get the graphic context, the window may have been recreated
	}

	canvas.clear(Colorf(0.0f,0.0f,0.2f));

	int font_size = 28;
	font_size *= canvas.get_width() / virtual_screen_width;
	font.set_height(font_size);
	canvas.set_transform(Mat4f::identity());
	if (is_fullscreen)
	{
		font.draw_text(canvas, 16, font_size, "Full Screen Mode. Press 'F' to switch to resizable window.");
	}
	else
	{
		font.draw_text(canvas, 16, font_size, "Resizable Window. Press 'F' to switch to full screen mode.");
	}

	// Scale the drawing to the screen to a virtual screen size
	Mat4f matrix = Mat4f::scale( (float) canvas.get_width() / virtual_screen_width, (float) canvas.get_height() /virtual_screen_height, 1.0f);
	canvas.set_transform(matrix);

	spr_logo.draw(canvas, virtual_screen_width-spr_logo.get_width(), virtual_screen_height-spr_logo.get_height());

	spr_background.set_scale(0.5f, 0.5f);
	spr_background.draw(canvas, 100, 100);

	// Show a few alpha-blending moving rectangles that moves in circles
	float x = cos(sin_count)*120.0f;
	float y = sin(sin_count)*120.0f;
	sin_count += 2.0f * game_time.get_time_elapsed();
	canvas.fill_rect(Rectf( 320.0f + x -30.0f, 300.0f + y -30.0f, Sizef(60.0f, 60.0f)), Colorf(0.0f, 1.0f, 0.0, 0.5f));
	x = cos(sin_count+3.14159f)*120.0f;
	y = sin(sin_count+3.14159f)*120.0f;
	canvas.fill_rect(Rectf( 320.0f + x -30.0f, 300 + y -30.0f, Sizef(60.0f, 60.0f)), Colorf(1.0f, 1.0f, 0.0, 0.5f));

	window.flip(1);

	return !quit;
}
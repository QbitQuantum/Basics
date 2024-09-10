static void in_render() {

	
	void *buf2 = lock(logo, logo->format->BitsPerPixel);
	void *buf = lock(start, start->format->BitsPerPixel);
	void *buf3 = lock(front, front->format->BitsPerPixel);
	int i,z;
	static float alpha = 0.0f;

	for(i = 0; i < front->w; i++) {
		for(z = 0; z < front->h; z++) {
			SDL_Color col1, col2;
			Uint32 color = 0;

			getpixel(logo, i, z, logo->format->BitsPerPixel, logo->pitch, &col2);
			getpixel(start, i, z, start->format->BitsPerPixel, start->pitch, &col1);
			color = SDL_MapRGB(front->format, ((Uint8)(alpha * col1.r) + (1-alpha) * col2.r), (Uint8)(alpha * col1.g) + (1-alpha) * col2.g , (Uint8) (alpha * col1.b) + (1-alpha) * col2.b);
			setpixel(buf3, i , z, color, front->format->BitsPerPixel, front->pitch);
		}
	}

	alpha += 0.1f;

	if(alpha > 3.0) {
		//start_game();
		scr = ID_START;

	}

	unlock(front);
	unlock(start);
	unlock(logo);

}
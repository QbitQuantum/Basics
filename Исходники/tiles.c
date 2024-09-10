int blitPreviews(experiment *experiments, unsigned int runs)
{
	// Viewport variables
	const unsigned int viewport_w = 340;
	const unsigned int viewport_h = 255;
	const float sequence_length = 58.0f + (2.0f / 11.0f);
	
	// Viewport data
	typedef struct viewport_data_t {
		SDL_Rect viewport;
		unsigned int tile;
		unsigned int tiles;
		unsigned int seg;
		float cumulative_error;
		float tile_error;
		unsigned int field;
		unsigned int base_fields;
		unsigned int cur_fields;
	} viewport_data;
	
	viewport_data *viewports;
	viewports = malloc(runs * sizeof(viewport_data) );
	
	if (!viewports) {
		fprintf(stderr, "Error allocating memory for viewport data.\n");
		return 1;
	}
	
	if (runs > 6) {
		fprintf(stderr, "Non-fatal: Cannot display more than six runs! Truncating output to six screens.\n");
		runs = 5; // starting from zero
	}
	
	for (int i = 0; i < runs; i++) {
		// Viewport dimensions
		viewports[i].viewport.w = viewport_w;
		viewports[i].viewport.h = viewport_h;
		
		switch (i) {
			case 0:
				viewports[i].viewport.x = 1;
				viewports[i].viewport.y = 1;
				break;
			case 1:
				viewports[i].viewport.x = 342;
				viewports[i].viewport.y = 1;
				break;
			case 2:
				viewports[i].viewport.x = 683;
				viewports[i].viewport.y = 1;
				break;
			case 3:
				viewports[i].viewport.x = 1;
				viewports[i].viewport.y = 512;
				break;
			case 4:
				viewports[i].viewport.x = 342;
				viewports[i].viewport.y = 512;
				break;
			case 5:
				viewports[i].viewport.x = 683;
				viewports[i].viewport.y = 512;
				break;
		}
		
		// Viewport tiles and scaling
		viewports[i].tile = 0; // start at the beginning
		viewports[i].tiles = experiments[i].seg * experiments[i].seg * 15;
		viewports[i].seg = experiments[i].seg;
		
		// Viewport tile jitter
		viewports[i].cumulative_error = 0.0f;
		viewports[i].tile_error = fmod((60.0f * sequence_length) / viewports[i].tiles, 1.0f);
		viewports[i].field = 0; // beginning again
		viewports[i].base_fields = (unsigned int) lrint(floor( ((60.0f * sequence_length) / viewports[i].tiles) ) );
		viewports[i].cur_fields = viewports[i].base_fields;
	}
	
	// Display variables
	SDL_Surface *display;
	display = SDL_GetVideoSurface();
	const SDL_Rect preview_size = { 0, 0, viewport_w, viewport_h };
	const int target_fps = 60;
	SDL_Event event_handler;
	int terminate = 0;
	int ticks_then = -1;
	int ticks_now = 0;
	int field = 0;
	int delay = 1000 / target_fps;
	
	// Create previews
	SDL_Thread *create_previews;
	int create_previews_return;
	float progress = 0;
	create_previews_args create_previews_arg = { experiments, runs, preview_size, &progress };
	create_previews = SDL_CreateThread((int (*)(void *))createPreviews, &create_previews_arg);
	
	if (create_previews == NULL) {
		fprintf(stderr, "SDL: Unable to create preview tile creation thread: %s\n", SDL_GetError() );
		return 1;
	}
	
	displayCountdownScreen(&progress);
	
	SDL_WaitThread(create_previews, &create_previews_return);
	
	if (create_previews_return != 0) {
		fprintf(stderr, "SDL: Preview tile creation thread failed.\n");
		return 1;
	}
	
	// Questions display
	const char *question_1_image_filename = "../Resources/question1.png";
	const char *question_2_image_filename = "../Resources/question2.png";
	SDL_Surface *question_1_image, *question_2_image;
	question_1_image = loadImage(question_1_image_filename);
	question_2_image = loadImage(question_2_image_filename);
	SDL_Rect question_image_location;
	question_image_location.w = 1022;
	question_image_location.h = 254;
	question_image_location.x = 1;
	question_image_location.y = 257;
	int question_image_fade = 0;
	const Uint8 question_image_fade_increment = 8;
	enum question_state_machine {
		q1_fadein,
		q1_static,
		q1_fadeout,
		q2_fadein,
		q2_static,
		q2_fadeout
	} question_state = q1_fadein;
	int question_keypress = 0;
	
	
	// Display routine
	while (!terminate) {
		// Handle events
		while (SDL_PollEvent(&event_handler) ) {
			switch (event_handler.type) {
				case SDL_KEYDOWN:
					question_keypress = 1;
					break;
				case SDL_QUIT:
					// should probably clean-up...
					exit(0);
					break;
				default:
					break;
			} // switch event_handler
		} // while SDL_PollEvent
		
		// State machine
		switch (question_state) {
			case q1_fadein:
				question_image_fade += question_image_fade_increment;
				if (question_image_fade >= 255) {
					question_image_fade = 255;
					question_state = q1_static;
				}
				break;
				
			case q1_static:
				if (question_keypress) {
					question_keypress = 0;
					question_state = q1_fadeout;
				}
				break;
			
			case q1_fadeout:
				question_image_fade -= question_image_fade_increment;
				if (question_image_fade <= 0) {
					question_image_fade = 0;
					question_state = q2_fadein;
				}
				break;
				
			case q2_fadein:
				question_image_fade += question_image_fade_increment;
				if (question_image_fade >= 255) {
					question_image_fade = 255;
					question_state = q2_static;
				}
				break;
				
			case q2_static:
				if (question_keypress) {
					question_keypress = 0;
					question_state = q2_fadeout;
				}
				break;
				
			case q2_fadeout:
				question_image_fade -= question_image_fade_increment;
				if (question_image_fade <= 0) {
					question_image_fade = 0;
					terminate = 1;
				}
				break;
				
			default:
				printf("Invalid state for blitPreviews.\n");
				break;
		} // switch question_state
		
		// Calculations
		for (int i = 0; i < runs; i++) {
			// Field updating
			viewports[i].field++;
			
			if (viewports[i].field == viewports[i].cur_fields) {
				// Reset tile
				viewports[i].field = 0;
				viewports[i].tile++;
				
				// Check we haven't gone beyond our bounds
				if (viewports[i].tile == viewports[i].tiles) {
					viewports[i].tile = 0;
				}
				
				// Calculate tile display duration
				viewports[i].cumulative_error += viewports[i].tile_error;
				if (viewports[i].cumulative_error >= 1.0f) {
					// Standard duration frame
					viewports[i].cur_fields = viewports[i].base_fields;
					viewports[i].cumulative_error -= 1.0f;
				} else {
					// Extended duration frame
					viewports[i].cur_fields = viewports[i].base_fields + 1;
				}
			}
		}
		
		// Rendering
		SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0) ); // clear with black
		for (int i = 0; i < runs; i++) {
			SDL_BlitSurface(previews[i][viewports[i].tile], NULL, display, &viewports[i].viewport);
		}
		
		// Question display
		switch (question_state) {
			case q1_fadein:
			case q1_static:
			case q1_fadeout:
				SDL_SetAlpha(question_1_image, SDL_RLEACCEL | SDL_SRCALPHA, question_image_fade);
				SDL_BlitSurface(question_1_image, NULL, display, &question_image_location);
				break;
				
			case q2_fadein:
			case q2_static:
			case q2_fadeout:
				SDL_SetAlpha(question_2_image, SDL_RLEACCEL | SDL_SRCALPHA, question_image_fade);
				SDL_BlitSurface(question_2_image, NULL, display, &question_image_location);
				break;
		} // switch question_state
	
		// Flipping
		SDL_Flip(display);
	
		// Delay calculation
		if (ticks_then > 0) {
			ticks_now = SDL_GetTicks();
			delay += (1000 / target_fps - (ticks_now - ticks_then) ); // adjust delay
			ticks_then = ticks_now;
			
			if (delay < 0) delay = 1000 / target_fps; // reset delay
		} else {
			ticks_then = SDL_GetTicks();
		}
		
		field++;
		
		SDL_Delay(delay);
	} // while !terminate
	
	// Clean-up
	destroyImage(question_1_image);
	destroyImage(question_2_image);
	free(viewports);
	
	return 0;
}
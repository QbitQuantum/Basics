int gl_renderer::render() {

	int running = 1;


/* ----- Event cycle --------------- */

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ){
				case SDLK_ESCAPE:
				case SDLK_q:
					running = 0;
					break;
				case SDLK_F1:
					SDL_WM_ToggleFullScreen(screen);
					break;
				case SDLK_s:
					control1->toggleEngineL();
					break;
				case SDLK_d:
					control1->toggleEngineR();
					break;
				case SDLK_k:
					control2->toggleEngineL();
					break;
				case SDLK_l:
					control2->toggleEngineR();
					break;

				case SDLK_1:
					switch_camera(0);
					break;
				case SDLK_2:
					switch_camera(1);
					break;
				case SDLK_3:
					switch_camera(2);
					break;
				default:
					break;
				}
				break;
			case SDL_VIDEORESIZE:
				if((screen = SDL_SetVideoMode(event.resize.w, event.resize.h, bpp, flags)) == 0) {
					fprintf(stderr, "Video resize failed: %s\n", SDL_GetError());
					exit(-1);
				}
				glPushAttrib(GL_TRANSFORM_BIT);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(90.0f, (GLfloat)event.resize.w/(GLfloat)event.resize.h, 0.1, 100000.0);
				glViewport(0.0f, 0.0f, event.resize.w, event.resize.h);
				glPopAttrib();
				break;
			case SDL_ACTIVEEVENT:
				if(event.active.state != SDL_APPMOUSEFOCUS && event.active.gain == 0)
					while(1){
						SDL_WaitEvent(&event);
						if(event.type == SDL_ACTIVEEVENT &&
							event.active.state != SDL_APPMOUSEFOCUS &&
							event.active.gain == 1);
							break;
					}
				break;
			default:
				break;
		}
	}

	interval = FrameTiming();
/* apply control movement */


/* ----- Blitting on the screen --------------- */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	current_camera->apply_rotation();
	//glutSolidCube(50.0);
	//draw_skybox(200.0);
	background_stars->draw();
	current_camera->apply_translation();



/* ----- Light ----- */
	angle += 0.001f * interval;

	light1.Position[0] = sinf(angle) * 1.5f;
	light1.Position[2] = cosf(angle) * 1.5f;

	light2.Position[1] = sinf(angle) * 1.5f;
	light2.Position[2] = cosf(angle) * 1.5f;

	UpdateLight(&light1, GL_LIGHT1, 0.1f);
	UpdateLight(&light2, GL_LIGHT2, 0.1f);

/* ----- Objects ----- */
	for(list<gl_drawable*>::const_iterator it = drawables->begin(); it != drawables->end(); ++it)
	{
		(*it)->draw();
	}

	SDL_GL_SwapBuffers();
	/*		SDL_Delay(25); */ /* Decomment this if you want 1/50th screen update */

	return running;
}
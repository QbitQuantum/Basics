void loop () {
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}
		
		//Handle input for the dot
		dot.handleEvent( e );
	}
	
	//Calculate time step
	float timeStep = stepTimer.getTicks() / 1000.f;

	//Move for time step
	dot.move( timeStep );

	//Restart step timer
	stepTimer.start();

	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render dot
	dot.render();

	//Update screen
	SDL_RenderPresent( gRenderer );
}
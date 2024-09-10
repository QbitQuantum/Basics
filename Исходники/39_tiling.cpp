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
	
	//Move the dot
	dot.move( tileSet );
	dot.setCamera( camera );

	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render level
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		tileSet[ i ]->render( camera );
	}

	//Render dot
	dot.render( camera );

	//Update screen
	SDL_RenderPresent( gRenderer );
}
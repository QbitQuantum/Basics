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
	dot.move();

	//Scroll background
	--scrollingOffset;
	if( scrollingOffset < -gBGTexture.getWidth() )
	{
		scrollingOffset = 0;
	}

	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	//Render background
	gBGTexture.render( scrollingOffset, 0 );
	gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

	//Render objects
	dot.render();

	//Update screen
	SDL_RenderPresent( gRenderer );
}
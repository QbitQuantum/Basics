void close()
{
	//Open data for writing
	SDL_RWops* file = SDL_RWFromFile( "33_file_reading_and_writing/nums.bin", "w+b" );
	if( file != NULL )
	{
		//Save data
		for( int i = 0; i < TOTAL_DATA; ++i )
		{
			SDL_RWwrite( file, &gData[ i ], sizeof(Sint32), 1 );
		}

		//Close file handler
		SDL_RWclose( file );
	}
	else
	{
		printf( "Error: Unable to save file! %s\n", SDL_GetError() );
	}

	//Free loaded images
	gPromptTextTexture.free();
	for( int i = 0; i < TOTAL_DATA; ++i )
	{
		gDataTextures[ i ].free();
	}

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
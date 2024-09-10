void close()
{
	//Free loaded images
	gSplashTexture.free();

	//Free semaphore
	SDL_DestroySemaphore( gDataLock );
	gDataLock = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
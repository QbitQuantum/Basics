void
close_sdl(void)
{
	printf("close_sdl()\n");

	/* free loaded image */
	gModulatedTexture.free();

	/* destroy window */
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	/* Quit SDL subsystem */
	IMG_Quit();
	SDL_Quit();
}